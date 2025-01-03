/*
 * A Factory design pattern.
 */
#ifndef FACTORY_H
#define FACTORY_H

#include <stdio.h>
#include <stdlib.h>

// Maximum length for a citizen's name
#define CITIZEN_MAX_NAME_LENGTH 32

// Enumeration for different types of people
typedef enum Person {
    CITIZEN,
    DOCTOR,
    FIREFIGHTER,
    JOURNALIST,
    REPORTER,
    DEAD,
    BURNED,
} Person;

// Structure for the status of a character
typedef struct status {
    unsigned int positionX;
    unsigned int positionY;
    double contamination;
    int is_sick;
    char name[CITIZEN_MAX_NAME_LENGTH];
    unsigned int nbr_days_sickness;
    Person type;
    int days_spent_in_hospital_asHealthy;
    int days_out_hospital;
    int care_pouch; // Number of care pouches (if applicable)
    void (*operation)(struct status *);
} status_p;

// Define `character_t` as an alias for `status_p`
typedef struct status character_t;

// Function pointer for operations on a character
typedef void (*operation_fn)(character_t *);

// Factory struct
typedef struct character_factory_s {
    character_t *(*factory_method)(void);
} character_factory_t;

character_factory_t *new_factory(character_t *(*factory_method)(void));

character_t *new_citizen(void);

character_t *new_doctor(void);

character_t *new_firefighter(void);

character_t *new_journalist(void);

void operation_citizen(character_t *citizen);

void operation_doctor(character_t *doctor);

void operation_firefighter(character_t *firefighter);

void operation_journalist(
    character_t *journalist);

#endif