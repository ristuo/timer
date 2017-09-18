#ifndef TASKTIMER_PERSIST_H
#define TASKTIMER_PERSIST_H
#include "tasktimer.hpp"
#include "project.hpp"

tasktimer load(const char* folderpath);
void save(tasktimer t, const char* folderpath);
#endif
