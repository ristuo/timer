#include<iostream>
#include<boost/date_time/posix_time/posix_time.hpp>
#include<boost/program_options.hpp>
#include <string>
#include "task.hpp"
#include "project.hpp"
#include "persist.hpp"
#include "timer.hpp"
#include <stdlib.h>
#include <boost/algorithm/string.hpp>
namespace po = boost::program_options;
using namespace std;

void add_project(tasktimer t, po::variables_map vm)
{
  std::cout << "Enter project name: ";
  std::string name;
  std::cin >> name;
  std::cin.ignore();
  std::string description;
  std::cout << "Enter project description: ";
  std::getline(std::cin, description);
  t.add_project(project(name, description));
}

void show(tasktimer t, po::variables_map vm)
{
  for (const auto& x: t.get_projects())
  {
    std::cout << x << std::endl; 
  } 
}

void help(tasktimer t, po::variables_map vm) 
{
  std::cout << "Available commands are:\n\
    help                          Print this help text\n\
    show                          Show projects\n\
    start PROJECT_NAME:TASK_NAME Start timing a task.\n\
    add-project                   Add a project" << std::endl;
}

void start(tasktimer ttimer, po::variables_map vm)
{
  string input = vm["command"].as<vector<string>>()[1];
  vector<string> project_task;
  boost::split(project_task, input, boost::is_any_of(":"));
  if (project_task.size() != 2) 
  {
    cout << "Incorrect project:task specification " << input << std::endl;
    exit(78);
  }
  string project_name = project_task[0];
  string task_name = project_task[1];
  auto project_option = ttimer.get_project(project_name); 
  if (!project_option)
  {
    cout << "No project " << project_name << endl;
    exit(78);
  }
  project p = project_option.value();
  auto task_option = p.get_task(task_name);
  if (!task_option)
  {
    cout << "No task " << task_name << " in project " << project_name << endl;
    exit(78);
  }
  task t = task_option.value();
  std::cout << "Implement starting!" << std::endl;
}

typedef function<void(tasktimer t, po::variables_map vm)> command_func;
typedef map<string, command_func> command_map;
static const command_map cmds = {
  { 
    "show", show
  },
  {
    "add-project", add_project
  },
  {
    "help", help
  },
  {
    "start", start
  }
};

int main(int ac, char** av) 
{
  if (ac < 2)
  {
    std::cout << "USAGE: " << av[0] << " COMMAND" << std::endl;
    exit(78);
  }
  po::options_description desc("Supported options");
  desc.add_options()("command", po::value<vector<string>>(), "Run command");
  po::positional_options_description p;
  p.add("command", -1);
  po::variables_map vm;
  po::store(
    po::command_line_parser(ac, av)
      .options(desc)
      .positional(p)
      .run(), 
    vm);
  po::notify(vm);
  string cmd = vm["command"].as<vector<string>>()[0];
  if (cmds.find(cmd) == cmds.end())
  {
    std::cout << "Unrecognized command " << cmd << endl;
    exit(78);
  }
  tasktimer t = load("../test-data");
  cmds.find(cmd)->second(t, vm);
  //save(t, "../test-data");
}
