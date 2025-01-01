#ifndef GTK_PRESS_AGENCY_H
#define GTK_PRESS_AGENCY_H

#if __linux__
#include <mqueue.h>
#elif __APPLE__
#include "macosx/mqueue.h"
#endif

#include <gtk/gtk.h>
#include <string.h>
#include <fcntl.h>

#include "channel.h"

/**
 * @file gtk_press_agency.h
 *
 * @brief This file contains the functions and structures for the press agency
 * viewer using the Gtk framework.
 *
 * The press agency viewer creates a memory queue to receive messages from
 * journalists.
 *
 * @author Alain Lebret
 * @author Loan Alouache
 * @author Maxence Morin
 * @version 1.3
 * @date 2023
 */

#define CHANNEL_NAME "/channel_from_city"

/**
 * @brief A struct representing the application.
 */
typedef struct application_s Application;

struct application_s {
    /** The main window of the application. */
    GtkWidget *window;
    /** The current headline of the newspaper board. */
    GtkWidget *label_headline;
    /** The current day on the newspaper. */
    GtkWidget *label_day;
    /** The grid containing the city cells of the application. */
    GtkWidget *grid;
    /** The channel to interact with journalists */
    Channel *channel;
};

/**
 * @brief Activates the GTK application by creating the main window, loading the
 * CSS file, creating the newspaper area, and connecting signals to events.
 *
 * This function is launched when the function g_application_run() is called.
 *
 * @param gtk_app The GtkApplication object.
 * @param data A pointer to the Application struct.
 */
void activate(GtkApplication *gtk_app, gpointer data);

/**
 * @brief Applies a CSS file to the default screen of the GTK application.
 *
 * @param css_filename The filename of the CSS file to be applied.
 */
void apply_css(const char *css_filename);

/**
 * @brief Handles key press events in the Pandemic Simulation application.
 *
 * This function listens for specific key press events and performs
 * corresponding actions. In this case, when the 'h' or 'H' key is pressed, it
 * triggers the show_about_dialog() function to display the "About" dialog for
 * the application, and when the 'q', 'Q' or 'ESC' key is pressed, it quits.
 *
 * @param widget The GtkWidget that receives the key press event.
 * @param event A GdkEventKey containing details about the key press event.
 * @param data A gpointer to any additional data needed by the function (in
 *             this case, the Application instance).
 *
 * @return FALSE, allowing other handlers to process the event as well.
 */
static gboolean on_key_press(const GtkWidget *widget, const GdkEventKey *event,
                             gpointer data);

/**
 * @brief Shows the "About" dialog for the Pandemic Simulation application by
 * pressing the 'h'/'H' key.
 *
 * This function creates and displays the "About" dialog for the application,
 * including information such as the program name, version, copyright, comments,
 * website, authors, and application icon. After the dialog is displayed, the
 * function cleans up the dialog resources upon closing.
 *
 * @param widget The GtkWidget that triggers the dialog.
 * @param data A gpointer to any additional data needed by the function (not
 *             used in this case).
 */
void show_about_dialog(const GtkWidget *widget, gpointer data);

/**
 * @brief Creates and returns a GtkWidget representing the newspaper area in the
 *        application.
 *
 * This function initializes a GtkGrid called "newspaper_area" and adds various
 * child widgets to it, such as the newspaper images and labels for the day and
 * the current headline of the newspaper. The created newspaper area is then
 * returned as a GtkWidget.
 *
 * @param app Pointer to an Application structure that contains the necessary
 *            application data.
 *
 * @return GtkWidget representing the newspaper_area grid.
 */
GtkWidget *create_newspaper_board(Application *app);

/**
 * @brief Creates a socket to communicate with Gnuplot and embed its output in
 *        the application window.
 *
 * This function creates a GtkSocket widget and attaches it to the provided
 * newspaper_area grid. It then realizes the socket, obtains its socket ID, and
 * creates a command file for Gnuplot. Finally, it forks a new process to
 * execute Gnuplot with the created command file.
 *
 * Note: This function is currently implemented only for Linux systems.
 *
 * @param newspaper_area GtkWidget pointer to the grid where the GtkSocket will
 *        be attached.
 */
void create_socket_to_gnuplot(const GtkWidget *newspaper_area);

/**
 * @brief Creates a command file for GNUPlot with a specific X11 window ID.
 *
 * This function creates or updates the "commands.gp" file with the X11 window
 * ID provided as the argument. This command file is used by GNUPlot to display
 * plots in the specified X11 window.
 *
 * @param socket_id The X11 window ID where GNUPlot should display the plot.
 */
void create_command_file(unsigned long socket_id);

/**
 * @brief Updates the window by calling functions to update the information
 * board and the simulation board.
 *
 * This function is called periodically by the main event loop to update the
 * application's window. It updates the information board and the simulation
 * board with the latest simulation data.
 *
 * @param data Pointer to the Application structure containing the simulation
 * data.
 * @return TRUE to continue calling this function periodically, or FALSE to
 * stop.
 */
static gboolean update_window(gpointer data);

/**
 * @brief Updates the information board by setting the title of the day and the
 *        current day.
 *
 * This function updates the information board's labels for the title of the day
 * and the current day number, based on the simulation's data.
 *
 * @param app Pointer to the Application structure containing the simulation data.
 */
void update_newspaper_board(const Application *app);

/**
 * @brief Stops the press agency viewer and cleans up shared resources.
 *
 * This function is responsible for stopping the press agency process and
 * the gnuplot process by sending a SIGINT signal to both. It also closes
 * the shared configuration and shared simulation resources.
 *
 * @param window The parent window
 * @param data Pointer to the Application structure containing the press agency
 *             data.
 */
static void stop_press_agency(GtkWidget *window, gpointer data);

#endif
