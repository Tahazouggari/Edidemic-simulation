#include "citizen_manager.h"
#include "logger.h"
#include <stdlib.h>

/* 
 * ----------------------------------------------------------------------------
 *                                  TO COMPLETE
 * ----------------------------------------------------------------------------
 */
status_p create_citizen(Person e,unsigned int x, unsigned int y,int id_name){
    const char *const names[] = {"Taha", "Mohamed", "Johann", "Brida", "Foulen", "Falten", "Foulena", "Bouhal",
                             "Saad", "Omar", "Hamza", "Ahmed", "Kamel", "Aymen", "Ramy", "Ayoub",
                             "Iyadh", "Abdlaaziz", "Souhem", "Abdelwehed", "Rachid", "Zekri", "Haythem", "Ben Lbokht", "Yassine", "Tareq",
                             "Eezedine", "Oussema", "Fawzi", "Achref", "Hatem", "Hazem", "Jamel", "Anas", "Ilyess",
                             "Zitoun", "Yazid", "Zied", "Ismail"};

      
    status_p citi;
   

    
    citi.positionX = x;
    citi.positionY = y;
    citi.contamination = 0;
    citi.is_sick = 0;
    citi.days_spent_in_hospital_asHealthy = 0;
    citi.type = e;
    strcpy(citi.name, names[id_name]);

    if (e==DOCTOR){
        /* to complete after */
    }
    return citi;
    
}

void get_sick(status_p *citizen) {
    double roll = (rand() / (RAND_MAX + 1.0));
    if (roll < citizen->contamination) {
        citizen->is_sick = 1;
    }
}

int is_at_position(status_p citizen, unsigned int x, unsigned int y) {
    return (citizen.positionX == x && citizen.positionY == y) ? 1 : 0;
}

void add_citizen_contamination(status_p *citizen, double cont) {
    if (citizen->type == FIREFIGHTER) {
        cont = cont / 10;
    }
    citizen->contamination += cont;
    if (citizen->contamination < 0) {
        citizen->contamination = 0;
    }
    if (citizen->contamination > 1) {
        citizen->contamination = 1;
    }
}


void die(status_p *citizen, double chance) {
    int roll = (rand() % 100);
    if (roll < chance * 100) {
        citizen->type = DEAD;
    }
}

void heal(status_p *citizen) {
    citizen->is_sick = 0;
    citizen->contamination = 0;
    citizen->days_spent_in_hospital_asHealthy = 0;
}

void refill_tools(status_p *citizen, int in_hospital, int in_firestation) {
    if (citizen->type == DOCTOR && in_hospital) {
        citizen->care_pouch = 10;
    }
    if (citizen->type == FIREFIGHTER && in_firestation) {
        citizen->care_pouch = 1000;
    }
}


