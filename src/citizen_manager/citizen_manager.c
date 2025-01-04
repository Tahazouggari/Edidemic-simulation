#include "citizen_manager.h"
#include "logger.h"

/* 
 * ----------------------------------------------------------------------------
 *                                  TO COMPLETE
 * ----------------------------------------------------------------------------
 */
status_p *create_citizen(Person e,unsigned int x, unsigned int y,int id_name){
    const char *const names[] = {"Taha", "Mohamed", "Johann", "Brida", "Foulen", "Falten", "Foulena", "Bouhal",
                             "Saad", "Omar", "Hamza", "Ahmed", "Kamel", "Aymen", "Ramy", "Ayoub",
                             "Iyadh", "Abdlaaziz", "Souhem", "Abdelwehed", "Rachid", "Zekri", "Haythem", "Ben Lbokht", "Yassine", "Tareq",
                             "Eezedine", "Oussema", "Fawzi", "Achref", "Hatem", "Hazem", "Jamel", "Anas", "Ilyess",
                             "Zitoun", "Yazid", "Zied", "Ismail"};

      
    status_p *citi = (status_p *)malloc(sizeof(status_p));
   

    
    citi->positionX = x;
    citi->positionY = y;
    citi->contamination = 0;
    citi->is_sick = 0;
    citi->days_spent_in_hospital_asHealthy = 0;
    citi->type = e;
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
