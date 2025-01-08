#include "city_manager.h"
#include <stdio.h>

/**
 * Initialise la ville : capacités, niveaux de contamination initiaux, etc.
 */

city_tile_t create_tile(building_type type)
{
    city_tile_t tile;
    tile.currentOccupancy = 0;
    tile.locationType = type;
    tile.contaminationLevel = 0.0;

    switch (type)
    {
    case WASTELAND:
        tile.capacity = 16;
        break;
    case HOUSE:
        tile.capacity = 8;
        break;
    case HOSPITAL:
        tile.capacity = 12;
        break;
    case FIRESTATION:
        tile.capacity = 8;
        break;
    default:
        tile.capacity = 0;
        break;
    }
    return tile;
}

void init_city(city_t *city)
{
    int i, j, k;

    city->grid[3][3] = create_tile(HOSPITAL);
    city->grid[0][6] = create_tile(FIRESTATION);
    city->grid[6][0] = create_tile(FIRESTATION);

    for (k = 0; k < 12; k++)
    {
        do
        {
            i = rand() % CITY_WIDTH;
            j = rand() % CITY_HEIGHT;
        } while (city->grid[i][j].capacity != 0);

        city->grid[i][j] = create_tile(HOUSE);
    }

    for (i = 0; i < CITY_WIDTH; i++)
    {
        for (j = 0; j < CITY_HEIGHT; j++)
        {
            if (city->grid[i][j].capacity == 0)
            {
                city->grid[i][j] = create_tile(WASTELAND);
                if (rand() % 100 < 10)
                {
                    city->grid[i][j].contaminationLevel = 0.20 + (rand() / (double)RAND_MAX) * 0.20;
                }
            }
        }
    }
}

void add_citizen(city_t *city, int num_c, Person type)
{
    int i, j;
    do
    {
        i = rand() % CITY_WIDTH;
        j = rand() % CITY_HEIGHT;
    } while (city->grid[i][j].currentOccupancy >= city->grid[i][j].capacity);

    city->_citizens[num_c] = *create_citizen(type, i, j, num_c);
    city->grid[i][j].currentOccupancy++;
}

void create_population(city_t *city)
{
    int ppl = 0;

    city->_citizens[ppl] = *create_citizen(FIREFIGHTER, 0, 6, ppl);
    city->grid[0][6].currentOccupancy++;
    ppl++;
    city->_citizens[ppl] = *create_citizen(FIREFIGHTER, 6, 0, ppl);
    city->grid[6][0].currentOccupancy++;
    ppl++;

    while (ppl < 6)
    {
        add_citizen(city, ppl, FIREFIGHTER);
        ppl++;
    }

    city->_citizens[ppl] = *create_citizen(DOCTOR, 3, 3, ppl);
    city->grid[3][3].currentOccupancy++;
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
    if (tile->locationType == FIRESTATION)
    {
        return;
    }
    if (tile->locationType == HOSPITAL)
    {
        cont *= 0.25;
    }
    tile->contaminationLevel += cont;
    if (tile->contaminationLevel < 0)
    {
        tile->contaminationLevel = 0;
    }
    if (tile->contaminationLevel > 1)
    {
        tile->contaminationLevel = 1;
    }
}
int sickest_of_title(city_t *city, unsigned int x, unsigned int y)
{
    int ppl;
}

double average_contamination(city_t *city)
{
    double sum = 0.0;
    int i, j;

    for (i = 0; i < CITY_HEIGHT; i++)
    {
        for (j = 0; j < CITY_WIDTH; j++)
        {
            sum += city->grid[i][j].contaminationLevel;
        }
    }

    return sum / (CITY_HEIGHT * CITY_WIDTH);
}

void display_city(city_t *city)
{
    int i, j;

    printf("\n------------------------------------------\n");
    for (i = 0; i < CITY_HEIGHT; i++)
    {
        for (j = 0; j < CITY_WIDTH; j++)
        {
            printf("%d %d %.2f | ",
                   city->grid[i][j].currentOccupancy,
                   city->grid[i][j].locationType,
                   city->grid[i][j].contaminationLevel);
        }
        printf("\n------------------------------------------\n");
    }

    printf("There are %d dead and burned people\n", get_number_of_dead(city) + get_number_of_burned(city));
    printf("There are %d sick people\n", get_number_of_sick(city));
    printf("There are %d healthy people\n", get_number_of_healthy(city));
}
