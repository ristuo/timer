#include "work_interval.hpp"
#include <boost/date_time/posix_time/posix_time.hpp>
using namespace boost::posix_time;
work_interval::work_interval(ptime start, ptime end): start(start), end(end) 
{
}

work_interval::work_interval(std::string start, std::string end)
{
  this->start = time_from_string(start);
  this->end = time_from_string(end);
}
