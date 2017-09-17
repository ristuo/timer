#include "persist.hpp"
#include "project.hpp"
#include "fast-cpp-csv-parser-master/csv.h"
#include <string>
#include "tasktimer.hpp"
std::vector<project> load_projects(const char* folderpath)
{
  using namespace std;
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

tasktimer load(const char* folderpath)
{
  tasktimer res;
  for (auto const& project: load_projects(folderpath))
  {
    res.add_project(project);
  };
  return res;
}
