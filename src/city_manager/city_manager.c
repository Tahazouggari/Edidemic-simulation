#include "city_manager.h"
#include <stdio.h>

/**
 * Initialise la ville : capacités, niveaux de contamination initiaux, etc.
 */

city_tile_t create_tile(building_type type)
{
    city_tile_t tile;
    tile._currentOccupancy = 0;
    tile._locationType = type;
    tile._contaminationLevel = 0.0;

    switch (type)
    {
    case WASTELAND:
        tile._capacity = 16;
        break;
    case HOUSE:
        tile._capacity = 8;
        break;
    case HOSPITAL:
        tile._capacity = 12;
        break;
    case FIRESTATION:
        tile._capacity = 8;
        break;
    default:
        break;
    }
    return tile;
}

void init_city(city_t *city)
{
    int i, j, k;

    city->_grid[3][3] = create_tile(HOSPITAL);
    printf("Hôpital placé en [3][3]\n");
    city->_grid[0][6] = create_tile(FIRESTATION);
    city->_grid[6][0] = create_tile(FIRESTATION);
     printf("Initialisation de la ville...\n");

    i= rand() % CITY_WIDTH;
    j = rand() % CITY_HEIGHT;
    for (k = 0; k < 12; k++)
    {
        if (city->_grid[i][j]._capacity != 0) {
            i = rand() % CITY_WIDTH;
            j = rand() % CITY_HEIGHT;
        }
        city->_grid[i][j] = create_tile(HOUSE);
        printf("Maison placée en [%d][%d]\n", i, j);
    }

    for (i = 0; i < CITY_WIDTH; i++)
    {
        for (j = 0; j < CITY_HEIGHT; j++)
        {
            if (city->_grid[i][j]._locationType!= 0 && city->_grid[i][j]._locationType!= 1 && city->_grid[i][j]._locationType!= 2 && city->_grid[i][j]._locationType!= 3)
            {
                city->_grid[i][j] = create_tile(WASTELAND);
                if (rand() % 100 < 10)
                {
                    
                    add_tile_contamination(&city->_grid[i][j], 0.20 + (1.0 * rand() / RAND_MAX) * 0.20);
                }
            }
            printf("Zone déserte placée en [%d][%d] avec un niveau de contamination de %.2f\n",
                       i, j, city->_grid[i][j]._contaminationLevel);
        }
    }
    printf("Initialisation terminée\n");
}

void add_citizen(city_t *city, int num_c, Person type)
{
    int i, j;
    do
    {
        i = rand() % CITY_WIDTH;
        j = rand() % CITY_HEIGHT;
    } while (city->_grid[i][j]._currentOccupancy >= city->_grid[i][j]._capacity);

    city->_citizens[num_c] = create_citizen(type, i, j, num_c);
    city->_grid[i][j]._currentOccupancy++;
}





void create_population(city_t *city)
{
    int ppl = 0;

    city->_citizens[ppl] = create_citizen(FIREFIGHTER, 0, 6, ppl);
    city->_grid[0][6]._currentOccupancy++;
    ppl++;
    city->_citizens[ppl] = create_citizen(FIREFIGHTER, 6, 0, ppl);
    city->_grid[6][0]._currentOccupancy++;
    ppl++;

    while (ppl < 6)
    {
        add_citizen(city, ppl, FIREFIGHTER);
        ppl++;
    }

    city->_citizens[ppl] = create_citizen(DOCTOR, 3, 3, ppl);
    city->_grid[3][3]._currentOccupancy++;
    ppl++;

    while (ppl < 10)
    {
        add_citizen(city, ppl, DOCTOR);
        ppl++;
    }

    while (ppl < 12)
    {
        add_citizen(city, ppl, REPORTER);
        ppl++;
    }

    while (ppl < NBR_TOTAL)
    {
        add_citizen(city, ppl, CITIZEN);
        ppl++;
    }
}

void add_tile_contamination(city_tile_t *tile, double cont)
{
    if (tile->_locationType == FIRESTATION)
    {
        return;
    }
    if (tile->_locationType == HOSPITAL)
    {
        cont *= 0.25;
    }
    tile->_contaminationLevel += cont;
    if (tile->_contaminationLevel < 0)
    {
        tile->_contaminationLevel = 0;
    }
    if (tile->_contaminationLevel > 1)
    {
        tile->_contaminationLevel = 1;
    }
}
int sickest_of_title(city_t *city, unsigned int x, unsigned int y)
{
    int ppl;
    int sickest_id = -1;
    int sickest = 0;
    for (ppl = 0; ppl < NBR_TOTAL; ppl++) {
        if (is_at_position(city->_citizens[ppl], x, y) && city->_citizens[ppl].nbr_days_sickness > sickest) {
            sickest = city->_citizens[ppl].nbr_days_sickness;
            sickest_id = ppl;
        }
    }
    return sickest_id;
    
}

double average_contamination(city_t *city)
{
    double sum = 0.0;
    int i, j;

    for (i = 0; i < CITY_HEIGHT; i++)
    {
        for (j = 0; j < CITY_WIDTH; j++)
        {
            sum += city->_grid[i][j]._contaminationLevel;
        }
    }

    return sum / (CITY_HEIGHT * CITY_WIDTH);
}

void contaminate_citizens_on_tile(city_t *city, unsigned int x, unsigned int y) {
    int ppl;
    for (ppl = 0; ppl < NBR_TOTAL; ppl++) {
        if (is_at_position(city->_citizens[ppl], x, y)) {
            add_citizen_contamination(&(city->_citizens[ppl]), city->_citizens[ppl].contamination * 0.01);
        }
    }
}

/**
void contaminate_citizens_on_tiles_around(city_t *city, unsigned int x, unsigned int y) {
    unsigned int **tiles_around;
    int nbOfSquares;
    int i;
    if (rand() % 100 < 10) {
        contaminate_citizens_on_tile(city, x, y);
    }
    if (city->_grid[x][y]._locationType == WASTELAND) {
        if (rand() % 100 < 1) {
            tiles_around = get_tiles_around(&nbOfSquares, x, y);
            for (i = 0; i < nbOfSquares; i++) {
                contaminate_citizens_on_tile(city, tiles_around[i][0], tiles_around[i][1]);
            }
        }
    }
} */
void eject_healed(city_t *city) {
    int ppl;
    status_p *person;
    for (ppl = 0; ppl < NBR_TOTAL; ppl++) {
        person = &city->_citizens[ppl];
        if (!person->is_sick && city->_grid[person->positionX][person->positionY]._locationType == HOSPITAL) {
            person->days_spent_in_hospital_asHealthy = 2;
        }
    }
}

int doctor_present(city_t *city, unsigned int x, unsigned int y) {
    int ppl;
    for (ppl = 0; ppl < NBR_TOTAL; ppl++) {
        if (city->_citizens[ppl].type == DOCTOR && is_at_position(city->_citizens[ppl], x, y)) {
            return 1;
        }
    }
    return 0;
}
int hasFireFighter(city_t *city, unsigned int x, unsigned int y) {
    int ppl;
    for (ppl = 0; ppl < NBR_TOTAL; ppl++) {
        if (city->_citizens[ppl].type == FIREFIGHTER && city->_citizens[ppl].positionX == x && city->_citizens[ppl].positionY == y) {
            return 1;
        }
    }
    return 0;
}
int get_number_of_dead(city_t *city) {
    int i;
    int deadPeople = 0;
    for (i = 0; i < NBR_TOTAL; i++) {
        if (city->_citizens[i].type == DEAD) {
            deadPeople++;
        }
    }
    return deadPeople;
}
int get_number_of_healthy(city_t *city) {
    int i;
    int healthyPeople = 0;
    for (i = 0; i < NBR_TOTAL; i++) {
        if (!city->_citizens[i].is_sick && city->_citizens[i].type != DEAD && city->_citizens[i].type != BURNED) {
            healthyPeople++;
        }
    }
    return healthyPeople;
}

int get_number_of_sick(city_t *city) {
    int i;
    int sickPeople = 0;
    for (i = 0; i < NBR_TOTAL; i++) {
        if (city->_citizens[i].is_sick && city->_citizens[i].type != DEAD && city->_citizens[i].type != BURNED) {
            sickPeople++;
        }
    }
    return sickPeople;
}

void display_city(city_t *city) {
    int i, j;
    int deadPeople;

    printf("\n------------------------------------------ \n");
    for (i = 0; i < CITY_WIDTH; i++) {
        for (j = 0; j < CITY_HEIGHT; j++) {
            printf("%d  %d %f |", city->_grid[i][j]._currentOccupancy, city->_grid[i][j]._locationType,
                   city->_grid[i][j]._contaminationLevel);
        }
        printf("\n------------------------------------------ \n");
    }
    deadPeople = get_number_of_dead(city) + get_number_of_burned(city);
    printf("There are %d dead and burned people\n", deadPeople);
    printf("There are %d sick people\n", get_number_of_sick(city));
    printf("There are %d healthy people\n", get_number_of_healthy(city));

}
int get_number_citizen(city_t *city) {
    int nb = 0;
    int i, j;
    for (i = 0; i < CITY_WIDTH; i++) {
        for (j = 0; j < CITY_HEIGHT; j++) {
            nb += city->_grid[i][j]._currentOccupancy;
        }
    }
    return nb;
}

int get_number_of_burned(city_t *city) {
    int i;
    int burned = 0;
    for (i = 0; i < NBR_TOTAL; i++) {
        if (city->_citizens[i].type == BURNED) {
            burned++;
        }
    }
    return burned;
}

int get_number_citizen_on_tile(int x, int y, city_t *city) {
    int ppl;
    int on_tile = 0;
    for (ppl = 0; ppl < NBR_TOTAL; ppl++) {
        if (is_at_position(city->_citizens[ppl], x, y)) {
            on_tile++;
        }
    }
    return on_tile;
}
int *get_dead_id(city_t *city) {
    int ppl;
    int i = 0;
    static int dead[NBR_TOTAL];
    for (ppl = 0; ppl < NBR_TOTAL; ppl++) {
        if (city->_citizens[ppl].type == DEAD) {
            dead[i] = ppl;
            i++;
        }
    }
    return dead;
}
/*
void wasteland_contamination_spread(city_t *city) {
    unsigned int x, y;
    int i;
    int nb_around;
    unsigned int **tiles_around;
    double contamination_diff;
    for (x = 0; x < CITY_WIDTH; x++) {
        for (y = 0; y < CITY_HEIGHT; y++) {
            if (city->_grid[x][y]._locationType == WASTELAND) {
                tiles_around = get_tiles_around(&nb_around, x, y);
                for (i = 0; i < nb_around; i++) {
                    city_tile_t *checked_tile = &city->_grid[tiles_around[i][0]][tiles_around[i][1]];
                    contamination_diff =  city->_grid[x][y]._contaminationLevel  - checked_tile->_contaminationLevel;
                    if ( contamination_diff > 0 && checked_tile->_locationType == WASTELAND) {
                        if (rand() % 100 < 15) {
                            add_tile_contamination(checked_tile, contamination_diff * ((rand() % 20) + 1.0) / 100);
                        }
                    }
                }
            }
        }
    }
}*/