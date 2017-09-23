#ifndef TIMINGRESULT_H
#define TIMINGRESULT_H
#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>
using namespace boost::posix_time;
class timing_result {
  private:
    ptime started;
    ptime ended;
  public:
    timing_result(ptime started, ptime ended): started(started), ended(ended)
    {
    };
};

std::ostream& operator<<(std::ostream& os, const timing_result& t);
#endif
