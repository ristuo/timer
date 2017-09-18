#include "persist.hpp"
#include <fstream>
#include "project.hpp"
#include "fast-cpp-csv-parser-master/csv.h"
#include <string>
#include "tasktimer.hpp"
#include "work_interval.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"
using namespace std;
std::vector<project> load_projects(const char* folderpath)
{
  io::CSVReader<2> in(string(folderpath) + "/projects.csv");
  in.read_header(io::ignore_extra_column, "name", "description");
  string name;
  string description;
  vector<project> res{};
  while(in.read_row(name, description))
  {
    res.push_back(project(name, description));
  }
  return res;
}

typedef string task_id;
typedef string project_id;
typedef map<task_id, vector<work_interval>> intervalmap;
typedef map<project_id, intervalmap> projects_intervals;
projects_intervals load_intervals(
  const char* folderpath)
{
  io::CSVReader<4> in(string(folderpath) + "/intervals.csv");
  in.read_header(io::ignore_extra_column, "project", "task", "start", "end");
  string project;
  string task;
  string start;
  string end;
  map<project_id, map<task_id, vector<work_interval>>> res{};
  while(in.read_row(project, task, start, end))
  {
    if (res.find(project) == res.end())
    {
      res[project] = intervalmap();
    }
    if (res[project].find(task) == res[project].end()) 
    {
      res[project][task] = vector<work_interval>();
    }
    res[project][task].push_back(work_interval(start, end));
  }
  return res; 
}

vector<task> intervalmap_to_tasks(intervalmap& a)
{
  vector<task> res{};
  res.reserve(a.size());
  for (auto const& name_intervals: a)
  {
    task new_task(name_intervals.first);
    for (auto const& interval: name_intervals.second)
    {
      new_task.add_work(interval);
    }
    res.push_back(new_task);
  }
  return res;
}

tasktimer load(const char* folderpath)
{
  tasktimer res;
  auto intervals = load_intervals(folderpath);
  for (auto& project: load_projects(folderpath))
  {
    if (intervals.find(project.get_name()) != intervals.end())
    {
      project.set_tasks(intervalmap_to_tasks(intervals[project.get_name()]));
    }
    res.add_project(project);
  };
  return res;
}

void save_projects(tasktimer t, const char* folderpath) 
{
  string filepath = string(folderpath) + "/projects.csv";
  ofstream outfile;
  outfile.open(filepath);
  outfile << "name,description" << endl;
  for (auto const& p: t.get_projects()) 
  {
    outfile << p.get_name() << "," << p.get_description() << endl; 
  }
  outfile.close();
}

void save_intervals(tasktimer t, const char* folderpath) 
{
  using namespace boost::posix_time;
  string filepath = string(folderpath) + "/intervals.csv";
  ofstream outfile;
  outfile.open(filepath);
  outfile << "project,task,start,end" << endl;
  for (auto const& p: t.get_projects()) 
  {
    for (auto const& t: p.get_tasks())
    {
      for (auto const& i: t.get_intervals()) 
      {
        outfile << p.get_name() << ",";
        outfile << t.get_name() << ",";
        outfile << to_iso_string(i.start) << ",";
        outfile << to_iso_string(i.end) << endl; 
      }
    }
  }
  outfile.close(); 
}

void save(tasktimer t, const char* folderpath)
{
  save_projects(t, folderpath); 
  save_intervals(t, folderpath);
}
