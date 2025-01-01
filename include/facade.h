#ifndef FACADE_H
#define FACADE_H

#include "simulation_memory.h"

/*
 * The facade pattern knows the objects to which the requests of a client are
 * addressed. The facade transmits the various requests from the client to the
 * objects, then returns their responses to the client.
 */
typedef struct facade_s Facade;

struct facade_s {
    SimulationMemory *memory;

    int (*get_pid_epidemic_sim)(const Facade *);
    int (*get_building)(const Facade *, int, int);
    int (*get_infection)(const Facade *, int, int);
    int (*get_day)(const Facade *);
    /* ADD WHAT YOU NEED */
};

Facade *new_facade(const SimulationMemory *memory);

int facade_get_pid_epidemic_sim(const Facade *facade);
int facade_get_building(const Facade *facade, int row, int column);
int facade_get_infection(const Facade *facade, int row, int column);
char *facade_get_headline_of_the_day(const Facade *facade);
int facade_get_day(const Facade *facade);

#endif
