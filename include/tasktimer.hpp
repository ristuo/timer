#ifndef TASKTIMER_H
#define TASKTIMER_H
#include "project.hpp"
#include <iostream>
#include <experimental/optional>
typedef std::vector<project> projectlist;
class tasktimer
{
  public:
    tasktimer(void) {}
    void add_project(project p) { projects.push_back(p); }
    const projectlist get_projects() const { return projects; }
    bool has_project(std::string project_name);
    std::experimental::optional<project> get_project(std::string project_name);
  private:
    projectlist projects; 
};

std::ostream& operator<<(std::ostream& os, const tasktimer& t);
#endif
