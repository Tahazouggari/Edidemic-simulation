#ifndef CITY_MANAGER_H
#define CITY_MANAGER_H

#define CITY_SIZE 7

typedef enum {
    HOSPITAL,
    CASERNE,
    MAISON,
    TERRAIN_VAGUE
} LocationType;

/**
 * Représente une case de la grille :
 * - locationType : type de lieu (hôpital, caserne, etc.)
 * - contaminationLevel : niveau de contamination [0.0 .. 1.0]
 * - capacity : capacité maximale de la case
 * - currentOccupancy : nombre actuel de citoyens
 */
typedef struct {
    LocationType locationType;
    double contaminationLevel;
    int capacity;
    int currentOccupancy;
} city_tile_t;

/**
 * Représente la ville sous forme d'une grille 7x7
 */
typedef struct {
    city_tile_t grid[CITY_SIZE][CITY_SIZE];
} city_t;

/* Prototypes des fonctions de gestion de la ville */
void init_city(city_t *city);
void display_city(const city_t *city);

/* ... d'autres fonctions pour gérer la contamination, etc. ... */

#endif /* CITY_MANAGER_H */
