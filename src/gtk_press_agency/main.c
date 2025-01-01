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

#include "logger.h"
#include "gtk_press_agency.h"

/*
 * Runs the Press Agency process.
 */
int main(int argc, char **argv) {
    GtkApplication *gtk_app;
    Application *app; /* Structure that interfaces with the simulation */
    int status;

    app = (Application *)malloc(sizeof(Application));

    /* G_APPLICATION_FLAGS_NONE is deprecated, but is always used on Ubuntu 22.04. */
    gtk_app = gtk_application_new("fr.ensicaen.ecole.newspaper", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(gtk_app, "activate", G_CALLBACK(activate), app);

    app->channel = open_channel(CHANNEL_NAME);
    if (app->channel == NULL) {
        log_error("No way to open a channel to receive news.");
        /* TODO: uncomment the following instruction when the work in progress  will end */
        /* exit(EXIT_FAILURE); */
    }

    status = g_application_run(G_APPLICATION(gtk_app), argc, argv);

    g_object_unref(gtk_app);
    free(app);

    return status;
}
