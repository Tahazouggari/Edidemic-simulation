#ifndef EPIDEMIC_SIM
#define EPIDEMIC_SIM

#if __linux__
#include <mqueue.h>
#elif __APPLE__
#include "macosx/mqueue.h"
#endif

#endif
