/*
 * A Facade design pattern.
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "facade.h"

Facade *new_facade(const SimulationMemory *memory) {
    Facade *facade = NULL;
   
    if (memory != NULL) {
        facade = (Facade *) malloc(sizeof(Facade));

        facade->get_pid_epidemic_sim = facade_get_pid_epidemic_sim;
        facade->get_building = facade_get_building;
        facade->get_infection = facade_get_infection;
        facade->get_day = facade_get_day;
    }
    return facade;
}

int facade_get_pid_epidemic_sim(const Facade *facade) {
    return 0;
}

int facade_get_building(const Facade *facade, int row, int column) {
    printf("%d",facade->memory->City._grid[row][column]._locationType );
    printf("hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh");
    return facade->memory->City._grid[row][column]._locationType;
    
  
}

int facade_get_infection(const Facade *facade, int row, int column) {
    return 0;
}

int facade_get_day(const Facade *facade) {
    if (!facade || !facade->memory) {
        return 0;
    } else {
        return 1;
    }
}
