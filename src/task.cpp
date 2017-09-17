#include "task.hpp"
#include <string>
#include <iostream>
#include "work_interval.hpp"
#include <boost/date_time/posix_time/posix_time.hpp>
using namespace boost::posix_time;

task::task(std::string name): name(name)
{
  this->intervals = worklist();
}

void task::add_work(ptime start, ptime end)
{
  this->intervals.push_back(work_interval(start, end));
}

void task::add_work(work_interval x)
{
  this->intervals.push_back(x);
}

const worklist task::get_intervals() const { return intervals; };

time_duration task::total_time() const
{
  time_duration res(0,0,0,0);
  for (auto const& interval: intervals)
  {
    time_duration diff = interval.end - interval.start;
    res = res + diff;
  }
  return res;
}

std::ostream& operator<<(std::ostream& os, const task& t)
{
  os << "Task: " << t.get_name() << std::endl;
  for (auto const& interval: t.get_intervals())
  {
    os << "\t" << interval.start << " - " << interval.end << std::endl;
  }
  os << "\tTotal duration: " << t.total_time() << std::endl;
  return os;
}
