#include <stdio.h>
#include <stdlib.h>


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

void set_hospital(SimulationMemory *memory){
    set_building(memory, CITY_ROWS / 2, CITY_COLUMNS / 2, 1);
}

void set_fire_stations(SimulationMemory *memory){
    set_building(memory, 0, CITY_COLUMNS - 1, 0);
    set_building(memory, CITY_ROWS - 1, 0, 0);
}

void set_houses(SimulationMemory *memory){
    int i = 0;
    while (i < 12){
        int rand_row = rand() % 7;
        int rand_col = rand() % 7;
        if (memory->buildings[rand_row][rand_col] == 4){
            set_building(memory, rand_row, rand_col, 2);
            i++;
        }
    }
}

void set_buildings(SimulationMemory *memory){
    for(int row = 0; row < CITY_ROWS; row++){
        for(int col = 0; col < CITY_COLUMNS; col++){
                set_building(memory, row, col, 4);
        }
    }

    set_hospital(memory);
    set_fire_stations(memory);
    set_houses(memory);

    for(int row = 0; row < CITY_ROWS; row++){
        for(int col = 0; col < CITY_COLUMNS; col++){
            if (memory->buildings[row][col] == 4){
                set_building(memory, row, col, 3);
            }
        }
    } 
}

void initialize_memory(SimulationMemory *memory){
    //set_headline(memory);
    //set_day(memory, 1);
    set_buildings(memory);
}
