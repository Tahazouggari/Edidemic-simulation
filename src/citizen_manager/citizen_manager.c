#include "citizen_manager.h"
#include "logger.h"

/* 
 * ----------------------------------------------------------------------------
 *                                  TO COMPLETE
 * ----------------------------------------------------------------------------
 */
status_p *create_citizen(Person e,unsigned int x, unsigned int y,int id_name){
    const char *const names[] = {"Harry", "Ron", "Hermione", "Draco", "Luna", "Neville", "Hagrid", "Dumbledore",
                             "Snape", "Voldemort", "Sirius", "Bellatrix", "Fred", "George", "Ginny", "McGonagall",
                             "Cedric", "Cho", "Fleur", "Krum", "Tonks", "Remus", "Percy", "Molly", "Arthur", "Petunia",
                             "Dudley", "Gilderoy", "Moody", "Seamus", "Dean", "Lavender", "Parvati", "Padma", "Peeves",
                             "Argus", "Sprout", "Flitwick", "Binns"};

      
    status_p *citi = (status_p *)malloc(sizeof(status_p));
   

   
    citi->positionX = x;
    citi->positionY = y;
    citi->contamination = 0;
    citi->is_sick = 0;
    citi->days_spent_in_hospital_asHealthy = 0;
    strcpy(citi->name, names[id_name]);

    if (e==DOCTOR){
        /* to complete after */
    }
    return citi;
    
}
void display_citizen( status_p *citi) {
    printf("Name: %s\n", citi->name);
    printf("Type: %d\n", citi->type);
    printf("Position: (%d, %d)\n", citi->positionX, citi->positionY);
    printf("Contamination Level: %.2f\n", citi->contamination);
    printf("Is Sick: %s\n", citi->is_sick ? "Yes" : "No");

    if (citi->type==DOCTOR ) {
        printf("Medical Pouches: %d\n", citi->care_pouch);
    } 
    printf("\n");
}

void get_sick(status_p *citizen) {
    double roll = (rand() / (RAND_MAX + 1.0));
    if (roll < citizen->contamination) {
        citizen->is_sick = 1;
    }
}
