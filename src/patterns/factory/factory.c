/*
 * A Factory design pattern.
 */

#include <stdio.h>
#include <stdlib.h>

#include "factory.h"
#include "logger.h"

character_factory_t *new_factory(character_t *(*factory_method)(void)) {
    character_factory_t *factory;

    factory = (character_factory_t *) malloc(sizeof(character_factory_t));
    factory->factory_method = factory_method;

    return factory;
}

character_t *new_citizen(void) {
    character_t *citizen;

    citizen = (character_t *) malloc(sizeof(character_t));
    citizen->operation = operation_citizen;

    return citizen;
}

character_t *new_doctor(void) {
    character_t *doctor;

    doctor = (character_t *) malloc(sizeof(character_t));
    doctor->operation = operation_doctor;

    return doctor;
}

character_t *new_firefighter(void) {
    character_t *firefighter;

    firefighter = (character_t *) malloc(sizeof(character_t));
    firefighter->operation = operation_firefighter;

    return firefighter;
}

character_t *new_journalist(void) {
    character_t *journalist;

    journalist = (character_t *) malloc(sizeof(character_t));
    journalist->operation =
            operation_journalist;

    return journalist;
}

void operation_citizen(character_t *citizen) {
    printf(">> Operation of a citizen...\n");
}

void operation_doctor(character_t *doctor) {
    printf(">> Operation of a doctor...\n");
}

void operation_firefighter(character_t *firefighter) {
    printf(">> Operation of a firefighter...\n");
}

void operation_journalist(
        character_t *journalist) {
    printf(">> Operation of a journalist...\n");
}
