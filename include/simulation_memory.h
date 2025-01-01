#ifndef SIMULATION_MEMORY_H
#define SIMULATION_MEMORY_H

#include <sys/types.h>

#define SIMULATION_MEMORY_PATH "/epidemic2023"
#define CITY_ROWS    7
#define CITY_COLUMNS 7

typedef struct simulation_memory_s SimulationMemory;

struct simulation_memory_s {
    char headline_of_the_day[255];
    int day;
    pid_t pid_epidemic_sim;
    int buildings[7][7];
};


void set_headline(SimulationMemory *memory);
void set_day(SimulationMemory *memory, int day);
void set_pid_epidemic_sim(SimulationMemory *memory, pid_t pid_epidemic_sim);
void set_building(SimulationMemory *memory, int row, int col, int building_type);
void initialize_memory(SimulationMemory *memory);


#endif
