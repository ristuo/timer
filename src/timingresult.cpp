#include "timingresult.hpp"
#include <iostream>

std::ostream& operator<<(std::ostream& os, const timing_result& t)
{
  os << "A timing result";
  return os;
}
