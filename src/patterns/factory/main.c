/*
 * A Factory design pattern.
 */

#include <stdio.h>
#include <stdlib.h>

#include "factory.h"
#include "logger.h"

int main(void) {
    character_factory_t *factory;
    character_t *a_citizen;
    character_t *a_doctor;
    character_t *a_firefighter;
    character_t *a_journalist;

    log_info("Create a new factory of citizens.");
    factory = new_factory(new_citizen);
    log_info("Create a new citizen.");
    a_citizen = factory->factory_method();
    log_info("Work with this citizen...");
    a_citizen->operation(a_citizen);
    free(factory);
    free(a_citizen);

    log_info("Create a new factory of doctors.");
    factory = new_factory(new_doctor);
    log_info("Create a new doctor.");
    a_doctor = factory->factory_method();
    log_info("Work with this doctor...");
    a_doctor->operation(a_doctor);
    free(factory);
    free(a_doctor);

    log_info("Create a new factory of firefighters.");
    factory = new_factory(new_firefighter);
    log_info("Create a new firefighter.");
    a_firefighter = factory->factory_method();
    log_info("Work with this firefighter...");
    a_firefighter->operation(a_firefighter);
    free(factory);
    free(a_firefighter);

    log_info("Create a new factory of journalists.");
    factory = new_factory(new_journalist);
    log_info("Create a new journalist.");
    a_journalist = factory->factory_method();
    log_info("Work with this journalist...");
    a_journalist->operation(a_journalist);
    free(factory);
    free(a_journalist);

    exit(EXIT_SUCCESS);
}
