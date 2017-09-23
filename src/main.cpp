#include<iostream>
#include<boost/date_time/posix_time/posix_time.hpp>
#include<boost/program_options.hpp>
#include <string>
#include "task.hpp"
#include "project.hpp"
#include "persist.hpp"
#include "timer.hpp"
#include <stdlib.h>
namespace po = boost::program_options;

void add_project(tasktimer t)
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

void show(tasktimer t)
{
  for (const auto& x: t.get_projects())
  {
    std::cout << x << std::endl; 
  } 
}

typedef std::map<std::string, std::function<void(tasktimer t)>> command_map;
static const command_map cmds = {
  { 
    "show", show
  },
  {
    "add-project", add_project
  }
};

int main(int ac, char** av) 
{
  using namespace std;
  po::options_description desc("Supported options");
  desc.add_options()("command", "Run command");
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
  string cmd = vm["command"].as<string>();
  if (cmds.find(cmd) == cmds.end())
  {
    std::cout << "Unrecognized command " << cmd << endl;
    exit(78);
  }
  tasktimer t = load("../test-data");
  cmds.find(cmd)->second(t);
  //save(t, "../test-data");
}
