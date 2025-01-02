#include <stdlib.h>

#include "citizen_manager.h"
#include "logger.h"

/*
 * Runs the Citizen Manager process.
 */
int main(int argc, const char *argv[]) {
    character_manager_t *manager = new_character_manager();
    character_factory_t *factory;
    character_t *character;

    // Create and manage a citizen
    log_info("Creating a new citizen using the manager.");
    factory = manager->get_factory(CITIZEN);
    character = factory->factory_method();
    character->operation(character);
    free(factory);
    free(character);

    // Create and manage a doctor
    log_info("Creating a new doctor using the manager.");
    factory = manager->get_factory(DOCTOR);
    character = factory->factory_method();
    character->operation(character);
    free(factory);
    free(character);

    // Create and manage a firefighter
    log_info("Creating a new firefighter using the manager.");
    factory = manager->get_factory(FIREFIGHTER);
    character = factory->factory_method();
    character->operation(character);
    free(factory);
    free(character);

    // Create and manage a journalist
    log_info("Creating a new journalist using the manager.");
    factory = manager->get_factory(JOURNALIST);
    character = factory->factory_method();
    character->operation(character);
    free(factory);
    free(character);

    free(manager);

    exit(EXIT_SUCCESS);
}
