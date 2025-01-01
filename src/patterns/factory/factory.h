/*
 * A Factory design pattern.
 */
#ifndef FACTORY_H
#define FACTORY_H

#include <stdio.h>
#include <stdlib.h>

/*
 * "character_t" defines the interface to "objects" that will be created by the
 * factory.
 */
typedef struct character_s character_t;

struct character_s {
    void (*operation)(character_t *);
};

/*
 * "character_factory_t" declares the production function that should return
 * "character_t" objects.
 */
typedef struct character_factory_s character_factory_t;

struct character_factory_s {
    character_t *(*factory_method)(void);
};

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