#ifndef EPIDEMIC_SIM
#define EPIDEMIC_SIM

#if __linux__
#include <mqueue.h>
#elif __APPLE__
#include "macosx/mqueue.h"
#endif
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>
#include "logger.h"
#include "citizen_manager.h"
#include "city_manager.h"
#include "simulation_memory.h"
 
void end_press_agency();

/**
 * distroy the shared memory for the city
 */
void destroy_shared_memory(int, city_t *);

/**
 * write new numbers in
 */
void write_evolution(FILE *, int[4]);

/**
 * @return numbers to write in evolution.txt
 */
int *get_numbers(city_t *);
#endif
