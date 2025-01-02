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
    

    if (app->simulation_facade == NULL) {
        log_error("Impossible to interface facade with shared memory");
        free(memory);
        free(app);
        exit(EXIT_FAILURE);
    }
    /* G_APPLICATION_FLAGS_NONE is deprecated, but is always used on Ubuntu 22.04. */
    gtk_app = gtk_application_new("fr.ensicaen.ecole.viewer", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(gtk_app, "activate", G_CALLBACK(activate), app);
    status = g_application_run(G_APPLICATION(gtk_app), argc, argv);

    g_object_unref(gtk_app);
    free(memory);
    free(app->simulation_facade);
    free(app);

    return status;
}
