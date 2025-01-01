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
        facade->memory = (SimulationMemory *)malloc(sizeof(SimulationMemory));

        initialize_memory(facade->memory);

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
    printf("%d\n",facade->memory->buildings[row][column]);
    return facade->memory->buildings[row][column];
}

int facade_get_infection(const Facade *facade, int row, int column) {
    return 0;
}

int facade_get_day(const Facade *facade) {
    if (!facade || !facade->memory) {
        return 0;
    } else {
        return facade->memory->day;
    }
}
