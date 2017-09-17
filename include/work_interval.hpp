#ifndef WORK_INTERVAL_H
#define WORK_INTERVAL_H
#include <boost/date_time/posix_time/posix_time.hpp>
using namespace boost::posix_time;
class work_interval
{
  public:
    work_interval(ptime start, ptime end);
    work_interval(std::string start, std::string end);
    ptime start;
    ptime end;
};
#endif
