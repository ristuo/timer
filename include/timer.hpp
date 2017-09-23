#ifndef TIMER_FOR_TASKTIMER_H
#define TIMER_FOR_TASKTIMER_H
#include "timingresult.hpp"
#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>
class timer {
  public:
    void start();
    timing_result end();
  
  private:
    boost::posix_time::ptime started;
    boost::posix_time::ptime ended;
};

std::ostream& operator<<(std::ostream& os, const timer& t);
#endif
