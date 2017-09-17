#include <iostream>
#include "project.hpp"

void project::add_task(task t)
{
  tasks.push_back(t);
}

std::ostream& operator<<(std::ostream& os, const project& p)
{
  os << "\033[1mProject: " << p.get_name() << "\033[0m" << std::endl;
  if (p.get_description() != "")
  {
    os << p.get_description() << std::endl;
  }
  for (auto const& task: p.get_tasks())
  {
    os << task;
  }
  return os;
}
