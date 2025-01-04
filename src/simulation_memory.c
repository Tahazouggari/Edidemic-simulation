#include <stdio.h>
#include <stdlib.h>



#include "simulation_memory.h"
#include "logger.h"
#include "citizen_manager/citizen_manager.c"
#include "city_manager/city_manager.c"

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
   init_city( memory->City);
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

void add_citizens(SimulationMemory *memory, int row, int col, int citizens_count, int id){
    memory->citizens[id] = create_citizen(CITIZEN, row, col, rand() % 32);
    display_citizen(memory->citizens[id]);
    memory->n_of_citizens[row][col] = memory->n_of_citizens[row][col] + citizens_count;
}

void add_firefighters(SimulationMemory *memory, int row, int col, int firefighters_count){
    memory->n_of_firefighters[row][col] = memory->n_of_firefighters[row][col] + firefighters_count;
}

void add_doctors(SimulationMemory *memory, int row, int col, int doctors_count){
    memory->n_of_doctors[row][col] = memory->n_of_doctors[row][col] + doctors_count;
}

void add_dead_citizens(SimulationMemory *memory, int row, int col, int dead_citizens_count){
    memory->n_of_dead_citizens[row][col] = memory->n_of_dead_citizens[row][col] + dead_citizens_count;
}

void add_ashes(SimulationMemory *memory, int row, int col, int ashes_count){
    memory->n_of_ashes[row][col] = memory->n_of_ashes[row][col] + ashes_count;
}

void init_people(SimulationMemory *memory, int number_of_citizens, int number_of_firefighters, int number_of_doctors, int number_of_dead_citizens, int number_of_ashes){
    for(int row = 0; row < CITY_ROWS; row++){
        for(int col = 0; col < CITY_COLUMNS; col++){
            memory->n_of_citizens[row][col] = 0;
            memory->n_of_firefighters[row][col] = 0;
            memory->n_of_doctors[row][col] = 0;
            memory->n_of_dead_citizens[row][col] = 0;
            memory->n_of_ashes[row][col] = 0;
        }
    }

    for(int i = 0; i < 25; i++){
        memory->citizens[i] = (status_p *)malloc(sizeof(status_p));
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
        add_citizens(memory, rand_row, rand_col, 1, citizens);
        citizens--;
    }
}


void initialize_memory(SimulationMemory *memory){
    //set_headline(memory);
    //set_day(memory, 1);
    
    
   // Inclure vos définitions nécessaires


    

    // Allouer dynamiquement la mémoire pour la ville
    memory->City = (city_t *)malloc(sizeof(city_t));
    if (!memory->City) {
        fprintf(stderr, "Error: Memory allocation failed for City.\n");
        exit(EXIT_FAILURE);
    }

    // Allouer dynamiquement la mémoire pour chaque citoyen
    for (int i = 0; i < 25; i++) {
        memory->citizens[i] = (status_p *)malloc(sizeof(status_p));
        
    }
    init_city(memory->City);

   

}

