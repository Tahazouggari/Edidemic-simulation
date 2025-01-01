#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "simulation_memory.h"
#include "logger.h"

/* 
 * ----------------------------------------------------------------------------
 *                                  TO COMPLETE
 * ----------------------------------------------------------------------------
 */

void set_headline(SimulationMemory *memory){
    strcpy(memory->headline_of_the_day, "Good morning");
}

void set_day(SimulationMemory *memory, int day){
    memory->day = day;
}

void set_pid_epidemic_sim(SimulationMemory *memory, pid_t pid_epidemic_sim){
    memory->pid_epidemic_sim = pid_epidemic_sim;
}

void set_building(SimulationMemory *memory, int row, int col, int building_type){
    memory->buildings[row][col] = building_type;
}

void initialize_memory(SimulationMemory *memory){
    srand(time(NULL));
    set_headline(memory);
    set_day(memory, 1);
    for(int row = 0; row < CITY_ROWS; row++){
        for(int col = 0; col < CITY_COLUMNS; col++){
            set_building(memory, row, col, rand() % 4);
        }
    } 
}