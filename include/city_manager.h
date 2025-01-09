#ifndef CITY_MANAGER_H
#define CITY_MANAGER_H

#define CITY_WIDTH 7
#define CITY_HEIGHT 7
#define NBR_TOTAL 37
#include "citizen_manager.h"
#include "stdlib.h"
typedef enum building_type {
    WASTELAND, HOUSE, HOSPITAL, FIRESTATION
} building_type;


/**
 * Représente une case de la grille :
 * - locationType : type de lieu (hôpital, caserne, etc.)
 * - contaminationLevel : niveau de contamination [0.0 .. 1.0]
 * - capacity : capacité maximale de la case
 * - currentOccupancy : nombre actuel de citoyens
 */
typedef struct {
    building_type _locationType;
    double _contaminationLevel;
    int _capacity;
    int _currentOccupancy;
} city_tile_t;

/**
 * Représente la ville sous forme d'une grille 7x7
 */
typedef struct {
    city_tile_t _grid[CITY_HEIGHT][CITY_WIDTH];
    status_p _citizens[NBR_TOTAL];
} city_t;

/* Prototypes des fonctions de gestion de la ville */
city_tile_t create_tile(building_type type);
void init_city(city_t *city);
void add_citizen(city_t *city, int num_c, Person type);
void create_population(city_t *city);
void add_tile_contamination(city_tile_t *tile, double cont);
int sickest_of_title(city_t *city, unsigned int x, unsigned int y);
double average_contamination(city_t *city);
void display_city(city_t *city);



/* ... d'autres fonctions pour gérer la contamination, etc. ... */

#endif /* CITY_MANAGER_H */
