#ifndef PROJECT_H
#define PROJECT_H
#include "task.hpp"
#include <string>
#include <experimental/optional>
typedef std::vector<task> tasklist;
class project
{
  public:
    project(std::string name): name(name), description("") {}; 
    project(std::string name, std::string description): name(name), 
      description(description) {}; 
    void add_task(task);
    void set_description(std::string);
    void set_tasks(tasklist tasks) { this->tasks = tasks; } ;
    const std::string get_name() const { return name; };
    const tasklist get_tasks() const { return tasks; };
    const std::string get_description() const { return description; };
    std::experimental::optional<task> get_task(std::string task_name);
  private:
    std::string name;
    std::string description;
    tasklist tasks;
};

std::ostream& operator<<(std::ostream&, const project&);
#endif
