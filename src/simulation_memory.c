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

void add_citizens(SimulationMemory *memory, int row, int col, int citizens_count){
    memory->citizens[row][col] = memory->citizens[row][col] + citizens_count;
}

void add_firefighters(SimulationMemory *memory, int row, int col, int firefighters_count){
    memory->firefighters[row][col] = memory->firefighters[row][col] + firefighters_count;
}

void add_doctors(SimulationMemory *memory, int row, int col, int doctors_count){
    memory->doctors[row][col] = memory->doctors[row][col] + doctors_count;
}

void add_dead_citizens(SimulationMemory *memory, int row, int col, int dead_citizens_count){
    memory->dead_citizens[row][col] = memory->dead_citizens[row][col] + dead_citizens_count;
}

void add_ashes(SimulationMemory *memory, int row, int col, int ashes_count){
    memory->ashes[row][col] = memory->ashes[row][col] + ashes_count;
}

void init_people(SimulationMemory *memory, int number_of_citizens, int number_of_firefighters, int number_of_doctors, int number_of_dead_citizens, int number_of_ashes){
    for(int row = 0; row < CITY_ROWS; row++){
        for(int col = 0; col < CITY_COLUMNS; col++){
            memory->citizens[row][col] = 0;
            memory->firefighters[row][col] = 0;
            memory->doctors[row][col] = 0;
            memory->dead_citizens[row][col] = 0;
            memory->ashes[row][col] = 0;
        }
    } 


    add_doctors(memory, CITY_ROWS / 2, CITY_COLUMNS / 2, 1);
    add_firefighters(memory, 0, CITY_COLUMNS - 1, 1);
    add_firefighters(memory, CITY_ROWS - 1, 0, 1);

    int medic = number_of_doctors - 1;
    while (medic > 0){
        int rand_row = rand() % 7;
        int rand_col = rand() % 7;
        add_doctors(memory, rand_row, rand_col, 1);
        medic--;
    }

    int firefighters = number_of_firefighters - 2;
    while (firefighters > 0){
        int rand_row = rand() % 7;
        int rand_col = rand() % 7;
        add_firefighters(memory, rand_row, rand_col, 1);
        firefighters--;
    }

    int citizens = number_of_citizens - 1;
    while (citizens > 0){
        int rand_row = rand() % 7;
        int rand_col = rand() % 7;
        add_citizens(memory, rand_row, rand_col, 1);
        citizens--;
    }
}


void initialize_memory(SimulationMemory *memory){
    //set_headline(memory);
    //set_day(memory, 1);
    set_buildings(memory);
    
    init_people(memory, 25, 6, 4, 0, 0);
}