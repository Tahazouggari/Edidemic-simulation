#include <stdlib.h>

#include "citizen_manager.h"
#include "logger.h"

/*
 * Runs the Citizen Manager process.
 */
int main(int argc, const char *argv[]) {
    status_p *citizen1 = create_citizen(CITIZEN, 10, 20, 0); // Harry
    status_p *doctor1 = create_citizen(DOCTOR, 15, 25, 1);   // Ron
    status_p *firefighter1 = create_citizen(FIREFIGHTER, 5, 10, 2); // Hermione

    printf("Displaying Citizen:\n");
    display_citizen(citizen1);

    printf("Displaying Doctor:\n");
    display_citizen(doctor1);

    printf("Displaying Firefighter:\n");
    display_citizen(firefighter1);

    return 0;
}
