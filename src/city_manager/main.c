#include <stdlib.h>

#include "city_manager.h"
#include "logger.h"

/*
 * Runs the City Manager process.
 */
int main() {
    // Initialiser le générateur de nombres aléatoires
    srand(time(NULL));

    // Déclaration de la ville
    city_t city;

    // Initialisation de la ville
    init_city(&city);

    // Affichage de la grille pour vérifier les résultats
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

    // Vérification des niveaux de contamination
    printf("\nNiveaux de contamination :\n");
    for (int i = 0; i < CITY_HEIGHT; i++) {
        for (int j = 0; j < CITY_WIDTH; j++) {
            if (city._grid[i][j]._contaminationLevel > 0) {
                printf("Tile [%d][%d] contamination : %.2f\n", i, j, city._grid[i][j]._contaminationLevel);
            }
        }
    }

    return 0;
}