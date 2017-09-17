#include<iostream>
#include<boost/date_time/posix_time/posix_time.hpp>
#include<boost/program_options.hpp>
#include <string>
#include "task.hpp"
#include "project.hpp"
#include "persist.hpp"
namespace po = boost::program_options;

project add_project()
{
  std::cout << "Enter project name: ";
  std::string name;
  std::cin >> name;
  std::cin.ignore();
  std::string description;
  std::cout << "Enter project description: ";
  std::getline(std::cin, description);
  return project(name, description);
}

int main(int ac, char** av) 
{
  using namespace std;
  po::options_description desc("Supported options");
  desc.add_options()("add-project", "Add a new project or task");
  po::variables_map vm;
  po::store(po::parse_command_line(ac, av, desc), vm);
  po::notify(vm);

  if (vm.count("add-project"))
  {
    auto new_project = add_project();
    auto x = boost::posix_time::time_from_string("2017-09-15 15:45:20");
    auto y = boost::posix_time::time_from_string("2017-09-15 15:55:13");
    auto a = task(std::string("C++"));
    a.add_work(x, y);
    a.add_work(x, y);
    a.add_work(x, y);
    new_project.add_task(a);
    std::cout << new_project << std::endl;
  }
  tasktimer t = load("../test-data");
  cout << t << endl; 
}
