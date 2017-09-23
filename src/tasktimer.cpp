#include "tasktimer.hpp"
#include <iostream>

bool tasktimer::has_project(std::string project_name)
{
  for (auto const& p: this->projects) 
  {
    if (p.get_name() == project_name)
    {
      return true; 
    }
  }
  return false;
}

std::experimental::optional<project> tasktimer::get_project(std::string project_name)
{
  for (auto p: this->projects)
  {
    if (p.get_name() == project_name)
    {
      return p;
    }
  }
  return {};
}

std::ostream& operator<<(std::ostream& os, const tasktimer& t)
{
  int max_name_width = 0;
  int max_desc_width = 0;
  for (auto const& project: t.get_projects()) 
  {
    if (project.get_name().length() > max_name_width)
    {
      max_name_width = project.get_name().length();
    }
    if (project.get_description().length() > max_name_width)
    {
      max_desc_width = project.get_description().length();
    }
  }
  for (auto const& project: t.get_projects()) 
  {
    os << std::setw(max_name_width) << project.get_name() << " ";
    os << std::setw(max_desc_width) << project.get_description();
  }
  return os;
}
