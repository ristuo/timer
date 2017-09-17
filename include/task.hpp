#ifndef TIMERTASK_H
#define TIMERTASK_H
#include <string>
#include "work_interval.hpp"
#include <boost/date_time/posix_time/posix_time.hpp>
typedef std::vector<work_interval> worklist;
using namespace boost::posix_time;
class task
{
  private:
    std::string name;
    worklist intervals;
  public: 
    task(std::string);
    const std::string get_name() const { return name; };
    void add_work(ptime start, ptime end); 
    const worklist get_intervals() const;
    time_duration total_time() const;
};

std::ostream& operator<<(std::ostream&, const task&);
#endif
