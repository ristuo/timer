#include "timer.hpp"
#include <iostream>
using namespace boost::posix_time;

std::ostream& operator<<(std::ostream& os, const timer& t)
{
  os << "A timer object";
  return os;
}

void timer::start() 
{
  this->started = second_clock::local_time(); 
}

timing_result timer::end() 
{
  this->ended = second_clock::local_time();
  timing_result res(this->started, this->ended);
  return res;
}
