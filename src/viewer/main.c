#ifdef __APPLE__
#include <TargetConditionals.h>
#if TARGET_OS_MAC
#include <gtk/gtkx.h>
#endif
#elif __linux__
#include <gdk/gdkkeysyms.h>
#include <gtk/gtkx.h>
#endif

#include <stdlib.h>
#include <time.h>

#include "logger.h"
#include "viewer.h"

/*
 * Runs the Simulation Viewer process.
 */
int main(int argc, char **argv) {
    srand(time(NULL));
    GtkApplication *gtk_app;
    SimulationMemory *memory;
    Application *app; /* Structure that interfaces with the simulation */
    int status;
    

    memory = (SimulationMemory *)malloc(sizeof(SimulationMemory));
    
    app = (Application *)malloc(sizeof(Application));
    
    app->simulation_facade = new_facade(memory);
    initialize_memory(app->simulation_facade->memory);
    
    
    for (int i = 0; i < CITY_HEIGHT; i++) {
        for (int j = 0; j < CITY_WIDTH; j++) {
            char type;
            switch (app->simulation_facade->memory->City._grid[i][j]._locationType) {
                case WASTELAND: type = 'W'; break;
                case HOUSE: type = 'H'; break;
                case HOSPITAL: type = 'O'; break;
                case FIRESTATION: type = 'F'; break;
                default: type = '?'; break;
            }
            printf("%c ", type);
        }
        printf("\n");
    }
    if (app->simulation_facade == NULL) {
        log_error("Impossible to interface facade with shared memory");
        free(memory);
        free(app);
        exit(EXIT_FAILURE);
    }
    
    /* G_APPLICATION_FLAGS_NONE is deprecated, but is always used on Ubuntu 22.04. */
    gtk_app = gtk_application_new("fr.ensicaen.ecole.viewer", G_APPLICATION_FLAGS_NONE);
    //g_signal_connect(gtk_app, "activate", G_CALLBACK(activate), app);
   // status = g_application_run(G_APPLICATION(gtk_app), argc, argv);

   // g_object_unref(gtk_app);
  //  free(memory);
   // free(app->simulation_facade);
   // free(app);

    return status;
}
