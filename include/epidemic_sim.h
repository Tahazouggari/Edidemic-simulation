#ifndef EPIDEMIC_SIM
#define EPIDEMIC_SIM

#if __linux__
#include <mqueue.h>
#elif __APPLE__
#include "macosx/mqueue.h"
#endif
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <signal.h>
#include <mqueue.h>


#define SHARED_MEM "/shm_city"

int create_shared_memory();


#endif