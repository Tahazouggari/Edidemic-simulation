#ifndef VIEWER_H
#define VIEWER_H

#include <gtk/gtk.h>
#include <string.h>

#include "facade.h"
#include "simulation_memory.h"

#define CELL_WIDTH 184 /* 64 + 5 x 24 */
#define CELL_HEIGHT 68
#define TYPES_OF_CHARACTER 5 /* doctor, firefighter, citizen, dead citizen, burnt bodies */

enum building_e {
    FIRE_STATION, HOSPITAL, HOUSE, WASTELAND
};

typedef enum building_e Building;

/**
 * @file viewer.h
 *
 * @brief This file contains the functions and structures for the simulation
 * viewer.
 *
 * The simulation viewer allows users to interact with the simulation of a
 * pandemic. It displays the current state of the simulation in a graphical
 * interface and updates it in real-time. The viewer is implemented using GTK
 * and provides various features such as a simulation board, an information
 * board, and a newspaper area that shows the latest news of the simulation.
 * This file contains the declaration of the structures and functions used in
 * the simulation viewer. These include the Application structure, which holds
 * the GTK widgets and the simulation data, and the functions to initialize and
 * start the viewer, update the window, and handle user events.
 *
 * @author Loan Alouache
 * @author Maxence Morin
 * @author Alain Lebret
 * @version 1.3
 * @date 2023
 */

/**
 * @brief A struct representing the application.
 */
typedef struct application_s Application;

struct application_s {
    /** The main window of the application. */
    GtkWidget *window;
    /** The grid containing the city cells of the application. */
    GtkWidget *grid;
    /** An array of boxes representing the city cells. */
    GtkWidget *boxes[CITY_ROWS][CITY_COLUMNS];
    /** Images representing the type of each city cell. */
    GtkWidget *images[CITY_ROWS][CITY_COLUMNS];
    /** Images representing the citizens in each city cell. */
    GtkWidget *images_citizens[CITY_ROWS][CITY_COLUMNS][TYPES_OF_CHARACTER];
    /** Labels representing the number of firefighters in each city cell. */
    GtkWidget *labels_firefighters[CITY_ROWS][CITY_COLUMNS];
    /** Labels representing the number of regular citizens in each city cell. */
    GtkWidget *labels_citizen[CITY_ROWS][CITY_COLUMNS];
    /** Labels representing the number of doctors in each city cell. */
    GtkWidget *labels_doctors[CITY_ROWS][CITY_COLUMNS];
    /** Labels representing the number of dead citizens in each city cell. */
    GtkWidget *labels_dead_citizens[CITY_ROWS][CITY_COLUMNS];
    /** Labels representing the amount of burnt bodies in each city cell. */
    GtkWidget *labels_burnt_bodies[CITY_ROWS][CITY_COLUMNS];
    /** Labels representing the infection level in each city cell. */
    GtkWidget *labels_infection[CITY_ROWS][CITY_COLUMNS];
    /** The current headline of the newspaper board. */
    GtkWidget *label_headline;
    /** The current day on the newspaper. */
    GtkWidget *label_day;
    /** A pointer to the simulation data stored in the shared memory. */
    Facade *simulation_facade;
};

/**
 * @file viewer.h
 *
 * <pre>
 *           Simulation
 *             board
 * +---+---+---+---+---+---+---+
 * |   |   |   |   |   |   | F |
 * |---+---+---+---+---+---+---+
 * |   |   |   |   |   |   |   |
 * |---+---+---+---+---+---+---+
 * |   |   |   |   |   |   |   |
 * |---+---+---+---+---+---+---+
 * |   |   |   | H |   |   |   |
 * |---+---+---+---+---+---+---+
 * |   |   |   |   |   |   |   |
 * |---+---+---+---+---+---+---+
 * |   |   |   |   |   |   |   |
 * |---+---+---+---+---+---+---+
 * | F |   |   |   |   |   |   |
 * +---+---+---+---+---+---+---+
 * </pre>
 */

/**
 * @brief Activates the GTK application by creating the main window, loading the
 * CSS file, creating the simulation board and connecting signals to events.
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
 * @brief Creates and initializes the simulation board UI elements.
 *
 * This function generates the simulation board grid, populates it with images
 * and labels for each cell, and sets the initial state of the UI elements.
 * It also sets up the grid properties, such as row and column spacing,
 * and homogeneous sizing.
 *
 * @param app Pointer to the Application structure containing the simulation
 * data.
 * @return A GtkWidget pointer to the created simulation board grid.
 */
GtkWidget *create_simulation_board(Application *app);

/**
 * @brief Hides citizen-related labels and images on the simulation board.
 *
 * This function iterates through all the cells in the simulation board
 * and hides the citizen-related labels and images for each cell. This
 * includes images and labels for regular citizens, doctors, firefighters, dead
 * citizens, and burnt bodies.
 *
 * @param app Pointer to the Application structure containing the simulation
 * data.
 */
void clean_citizen_labels(const Application *app);

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
 * @brief Updates the simulation board by refreshing infection labels and
 * citizen counts.
 *
 * This function iterates over all cells in the simulation grid, updates the
 * infection labels for each cell, counts the citizens in each category
 * (regular citizens, doctors, firefighters, dead citizens, and burnt bodies),
 * and updates the corresponding labels and images for each category.
 *
 * @param app Pointer to the Application structure containing the simulation
 *            data.
 */
void update_simulation_board(const Application *app);

/**
 * @brief Updates the infection labels for a cell in the simulation grid.
 *
 * This function takes an Application pointer and the row and column indices of
 * a cell in the simulation grid. It updates the text and style of the
 * corresponding infection label based on the infection level of the cell. We
 * defined 5 ranges of contamination rate:
 * - "normal" (0 % to 20 %);
 * - "contamination1" (21 % to 40 %);
 * - "contamination2" (41 % to 60 %);
 * - "contamination3" (61 % to 80 %);
 * - "contamination4" (81 % to 100 %);
 *
 * @param app Pointer to the Application structure containing the simulation
 * data and GTK widgets.
 * @param row The row index of the cell in the simulation grid.
 * @param col The column index of the cell in the simulation grid.
 */
void update_infection_labels(const Application *app, int row, int col);

/**
 * @brief Counts the number of citizens, doctors, firemen, dead citizens, and
 *        burnt bodies in a cell of the simulation grid.
 *
 * This function takes an Application pointer and the row and column indices of
 * a cell in the simulation grid. It counts the number of citizens, doctors,
 * firemen, dead, and burnt in the cell, updating the corresponding integer
 * pointers.
 *
 * @param app Pointer to the Application structure containing the simulation
 * data.
 * @param row The row index of the cell in the simulation grid.
 * @param col The column index of the cell in the simulation grid.
 * @param citizens Pointer to an integer to store the number of regular
 *                 citizens.
 * @param doctors Pointer to an integer to store the number of doctors.
 * @param firefighters Pointer to an integer to store the number of firefighters.
 * @param dead_citizens Pointer to an integer to store the number of dead citizens.
 * @param burnt_bodies Pointer to an integer to store the number of burnt bodies.
 */
void count_citizens(const Application *app, int row, int col, int *citizens,
                    int *doctors, int *firefighters, int *dead_citizens,
                    int *burnt_bodies);

/**
 * @brief Updates citizen labels and images on the simulation grid.
 *
 * This function takes an Application pointer, row and column indices of a cell
 * in the simulation grid, an array of citizen counts, and arrays of label and
 * image widgets. It updates the visibility and text of the labels and images
 * for each category of citizens (regular, doctors, firefighters, dead citizens
 * and burnt bodies) based on their counts in the cell.
 *
 * @param app Pointer to the Application structure containing the simulation
 * data.
 * @param row The row index of the cell in the simulation grid.
 * @param col The column index of the cell in the simulation grid.
 * @param citizen_counts An integer array containing the counts of each category
 *                       of citizens.
 * @param labels An array of GtkWidget pointers to the label widgets.
 * @param images An array of GtkWidget pointers to the image widgets.
 */
void update_citizen_labels_and_images(const Application *app, int row, int col,
                                      const int citizen_counts[],
                                      GtkWidget *labels[], GtkWidget *images[]);

/**
 * @brief Stops the simulation and cleans up shared resources.
 *
 * This function is responsible for stopping the simulation process and
 * the gnuplot process by sending a SIGINT signal to both. It also closes
 * the shared configuration and shared simulation resources.
 *
 * @param window The parent window
 * @param data Pointer to the Application structure containing the simulation
 *             data.
 */
static void stop_simulation(GtkWidget *window, gpointer data);

#endif
