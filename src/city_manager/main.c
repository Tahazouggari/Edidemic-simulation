#include <stdlib.h>

#include "city_manager.h"
#include "logger.h"

/*
 * Runs the City Manager process.
 */
int main() {
    
    srand(time(NULL));

    city_t city;

   
    init_city(&city);
    create_population(&city);

    // Affichage initial de la grille
    printf("Grille de la ville :\n");
    for (int i = 0; i < CITY_HEIGHT; i++) {
        for (int j = 0; j < CITY_WIDTH; j++) {
            char type;
            switch (city._grid[i][j]._locationType) {
                case WASTELAND: type = 'W'; break;
                case HOUSE: type = 'H'; break;
                case HOSPITAL: type = 'O'; break;
                case FIRESTATION: type = 'F'; break;
                default: type = '?'; break;
            }
            printf("%c ", type);
        }
        printf("\n");
    }

   
    printf("\nNiveaux de contamination :\n");
    for (int i = 0; i < CITY_HEIGHT; i++) {
        for (int j = 0; j < CITY_WIDTH; j++) {
            if (city._grid[i][j]._contaminationLevel > 0) {
                printf("Tile [%d][%d] contamination : %.2f\n", i, j, city._grid[i][j]._contaminationLevel);
            }
        }
    }

   
   
    for (int i = 0; i < CITY_HEIGHT; i++) {
        for (int j = 0; j < CITY_WIDTH; j++) {
            if (city._grid[i][j]._contaminationLevel > 0) {
                printf("Tile [%d][%d] contamination : %.2f\n", i, j, city._grid[i][j]._contaminationLevel);
            }
        }
    }

    
    
    printf("\nStatistiques de la ville :\n");
    printf("Nombre total de citoyens : %d\n", get_number_citizen(&city));
    printf("Nombre de citoyens malades : %d\n", get_number_of_sick(&city));
    printf("Nombre de citoyens morts : %d\n", get_number_of_dead(&city));
    printf("Nombre de citoyens brûlés : %d\n", get_number_of_burned(&city));
    printf("Niveau moyen de contamination : %.2f\n", average_contamination(&city));

    // Affichage final de la grille
    printf("\nAffichage final de la ville :\n");
    display_city(&city);

    return 0;
}