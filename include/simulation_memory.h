#ifndef SIMULATION_MEMORY_H
#define SIMULATION_MEMORY_H

#include <sys/types.h>
#include "citizen_manager.h"
#include "city_manager.h"
#define SIMULATION_MEMORY_PATH "/epidemic2023"
#define CITY_ROWS    7
#define CITY_COLUMNS 7

typedef struct simulation_memory_s SimulationMemory;

struct simulation_memory_s {
    
   
    city_t City;
};



void initialize_memory(SimulationMemory *memory);



#endif
