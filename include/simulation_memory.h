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
    char headline_of_the_day[255];
    int day;
    pid_t pid_epidemic_sim;
    int buildings[7][7];
    int n_of_citizens[7][7];
    int n_of_firefighters[7][7];
    int n_of_doctors[7][7];
    int n_of_dead_citizens[7][7];
    int n_of_ashes[7][7];
    status_p* citizens[25];
    city_t *City;
};


void set_headline(SimulationMemory *memory);
void set_day(SimulationMemory *memory, int day);
void set_pid_epidemic_sim(SimulationMemory *memory, pid_t pid_epidemic_sim);
void set_building(SimulationMemory *memory, int row, int col, int building_type);
void initialize_memory(SimulationMemory *memory);

void add_citizens(SimulationMemory *memory, int row, int col, int citizens_count, int id);
void add_firefighters(SimulationMemory *memory, int row, int col, int firefighters_count);
void add_doctors(SimulationMemory *memory, int row, int col, int doctors_count);
void add_dead_citizens(SimulationMemory *memory, int row, int col, int dead_citizens_count);
void add_ashes(SimulationMemory *memory, int row, int col, int ashes_count);

void init_people(SimulationMemory *memory, int number_of_citizens, int number_of_firefighters, int number_of_doctors, int number_of_dead_citizens, int number_of_ashes);

#endif
