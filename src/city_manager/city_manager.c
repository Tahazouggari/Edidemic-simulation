#include "city_manager.h"
#include <stdio.h>

/**
 * Initialise la ville : capacités, niveaux de contamination initiaux, etc.
 */
void init_city(city_t *city) {
    for(int x = 0; x < CITY_SIZE; x++) {
        for(int y = 0; y < CITY_SIZE; y++) {
            
            city->grid[x][y].locationType= 0;   /* Ex. par défaut */
            city->grid[x][y].contaminationLevel = 0.0;
            city->grid[x][y].capacity = 16;                  /* Ex. terrain vague = 16 */
            city->grid[x][y].currentOccupancy = 0;
        }
    }
    /* Personnalisez selon vos règles (maisons, hôpitaux, etc.) */
}

void display_city(const city_t *city) {
    
    for(int x = 0; x < CITY_SIZE; x++) {
        for(int y = 0; y < CITY_SIZE; y++) {
            const city_tile_t *tile = &city->grid[x][y];
            printf("Tile(%d, %d) type=%d, cont=%.2f, occ=%d/%d\n",
                   x, y,
                   tile->locationType,
                   tile->contaminationLevel,
                   tile->currentOccupancy,
                   tile->capacity);
        }
    }
}
