#ifndef TASKTIMER_PERSIST_H
#define TASKTIMER_PERSIST_H
#include "tasktimer.hpp"
#include "project.hpp"

tasktimer load(const char*);

void save(tasktimer t);
#endif
