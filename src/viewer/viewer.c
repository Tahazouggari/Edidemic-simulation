#ifdef __APPLE__

#include <TargetConditionals.h>

#if TARGET_OS_MAC

#include <gtk/gtkx.h>

#endif
#elif __linux__
#include <gdk/gdkkeysyms.h>
#include <gtk/gtkx.h>
#endif

#include "viewer.h"

pid_t gnuplot_pid;

void activate(GtkApplication *gtk_app, gpointer data) {
    Application *app;
    GtkWidget *simulation_board;

    app = data;
    app->window = gtk_application_window_new(gtk_app);
    gtk_widget_set_name(app->window, "background");

    g_signal_connect(GTK_WINDOW(app->window), "destroy",
                     G_CALLBACK(stop_simulation), app);

    gtk_window_set_title(GTK_WINDOW(app->window), "Epidemic 2023");
    gtk_window_set_default_size(GTK_WINDOW(app->window), 0, 0);

    GtkWidget *main_layout = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    gtk_container_add(GTK_CONTAINER(app->window), main_layout);

    /* --------------------------- LOAD CSS FILE --------------------------- */
    apply_css("resources/theme.css");

    /* ------------------- KEY MANAGEMENT FOR ABOUT BOX -------------------- */

    gtk_widget_set_events(app->window, GDK_KEY_PRESS_MASK);
    g_signal_connect(app->window, "key-press-event", G_CALLBACK(on_key_press),
                     &gtk_app);

    /* -------------------------- SIMULATION BOARD ------------------------- */
    simulation_board = create_simulation_board(app);
    gtk_box_pack_start(GTK_BOX(main_layout), simulation_board, TRUE, TRUE, 0);

    /* ------------------------------- ALL ---------------------------------- */

    g_timeout_add_seconds(1, (GSourceFunc) update_window, data);
    gtk_widget_show_all(app->window);
    clean_citizen_labels(app);
    gtk_window_resize(GTK_WINDOW(app->window), 1, 1);
    gtk_window_set_resizable(GTK_WINDOW(app->window), FALSE);
}

void apply_css(const char *css_filename) {
    GtkCssProvider *cssProvider;

    cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, css_filename, NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                              GTK_STYLE_PROVIDER(cssProvider),
                                              GTK_STYLE_PROVIDER_PRIORITY_USER);
}

static gboolean on_key_press(const GtkWidget *gtk_app, const GdkEventKey *event, gpointer data) {
    Application *app = (Application *) data;

    if (event->keyval == GDK_KEY_q
        || event->keyval == GDK_KEY_Q
        || event->keyval == GDK_KEY_Escape) {
        gtk_widget_destroy(GTK_WIDGET(gtk_app));
        return TRUE;
    }
    if (event->keyval == GDK_KEY_h || event->keyval == GDK_KEY_H) {
        show_about_dialog(NULL, app);
    }

    return FALSE;
}

void show_about_dialog(const GtkWidget *gtk_app, gpointer data) {
    GtkAboutDialog *about_dialog = GTK_ABOUT_DIALOG(gtk_about_dialog_new());
    const gchar *authors[] = {"L. Alouache", "M. Morin", "A. Heslouin",
                              "A. Fave", "E. Le Mazier", "A. Lebret",
                              NULL};

    gtk_about_dialog_set_program_name(about_dialog, "Epidemic Simulation");
    gtk_about_dialog_set_version(about_dialog, "1.3");
    gtk_about_dialog_set_copyright(about_dialog, "Copyright © 2023 ENSICAEN");
    gtk_about_dialog_set_comments(
            about_dialog,
            "A pandemic simulation that models the spread of viral "
            "contamination within a population over time..");
    gtk_about_dialog_set_website(about_dialog,
            "https://gitlab.ecole.ensicaen.fr/alebret/epidemic_2023");
    gtk_about_dialog_set_authors(about_dialog, authors);
    gtk_about_dialog_set_logo_icon_name(about_dialog, "epidemic");

    gtk_dialog_run(GTK_DIALOG(about_dialog));
    gtk_widget_destroy(GTK_WIDGET(about_dialog));
}

GtkWidget *create_simulation_board(Application *app) {
    int width;
    int height;
    Facade *facade;

    width = CITY_COLUMNS * (CELL_WIDTH + 1);
    height = CITY_ROWS * (CELL_HEIGHT + 1);
    facade = app->simulation_facade;

    app->grid = gtk_grid_new();
    gtk_widget_set_name(app->grid, "bg-grid");
    gtk_widget_set_size_request(app->grid, width, height);
    gtk_grid_set_row_spacing(GTK_GRID(app->grid), 1);
    gtk_grid_set_column_spacing(GTK_GRID(app->grid), 1);
    gtk_grid_set_row_homogeneous(GTK_GRID(app->grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(app->grid), TRUE);

    for (int row = 0; row < CITY_ROWS; row++) {
        for (int col = 0; col < CITY_COLUMNS; col++) {
            switch (facade->get_building(facade, row, col)) {
                case FIRE_STATION:
                    app->images[row][col] =
                            gtk_image_new_from_file(
                                    "resources/firestation.png");
                    break;
                case HOSPITAL:
                    app->images[row][col] =
                            gtk_image_new_from_file("resources/hospital.png");
                    break;
                case HOUSE:
                    app->images[row][col] = gtk_image_new_from_file(
                            "resources/house.png");
                    break;
                default:
                    app->images[row][col] = gtk_image_new_from_file(
                            "resources/tree.png");
                    break;
            }

            app->labels_citizen[row][col] = gtk_label_new("0");
            app->labels_firefighters[row][col] = gtk_label_new("0");
            app->labels_doctors[row][col] = gtk_label_new("0");
            app->labels_dead_citizens[row][col] = gtk_label_new("0");
            app->labels_burnt_bodies[row][col] = gtk_label_new("0");
            app->labels_infection[row][col] = gtk_label_new("0%");

            app->images_citizens[row][col][0] =
                    gtk_image_new_from_file("resources/citizen.png");
            app->images_citizens[row][col][1] =
                    gtk_image_new_from_file("resources/firefighter.png");
            app->images_citizens[row][col][2] =
                    gtk_image_new_from_file("resources/doctor.png");
            app->images_citizens[row][col][3] =
                    gtk_image_new_from_file("resources/dead_citizen.png");
            app->images_citizens[row][col][4] =
                    gtk_image_new_from_file("resources/ashes.png");

            app->boxes[row][col] = gtk_grid_new();

            gtk_widget_set_name(app->boxes[row][col], "normal");

            gtk_grid_attach(GTK_GRID(app->boxes[row][col]),
                            app->images[row][col], 0, 0, 1, 1);
            gtk_grid_attach(GTK_GRID(app->boxes[row][col]),
                            app->images_citizens[row][col][0], 2, 0, 1, 1);
            gtk_grid_attach(GTK_GRID(app->boxes[row][col]),
                            app->images_citizens[row][col][1], 3, 0, 1, 1);
            gtk_grid_attach(GTK_GRID(app->boxes[row][col]),
                            app->images_citizens[row][col][2], 4, 0, 1, 1);
            gtk_grid_attach(GTK_GRID(app->boxes[row][col]),
                            app->images_citizens[row][col][3], 5, 0, 1, 1);
            gtk_grid_attach(GTK_GRID(app->boxes[row][col]),
                            app->images_citizens[row][col][4], 6, 0, 1, 1);

            gtk_grid_attach(GTK_GRID(app->boxes[row][col]),
                            app->labels_citizen[row][col], 2, 1, 1, 1);
            gtk_grid_attach(GTK_GRID(app->boxes[row][col]),
                            app->labels_firefighters[row][col], 3, 1, 1, 1);
            gtk_grid_attach(GTK_GRID(app->boxes[row][col]),
                            app->labels_doctors[row][col], 4, 1, 1, 1);
            gtk_grid_attach(GTK_GRID(app->boxes[row][col]),
                            app->labels_dead_citizens[row][col], 5, 1, 1, 1);
            gtk_grid_attach(GTK_GRID(app->boxes[row][col]),
                            app->labels_burnt_bodies[row][col], 6, 1, 1, 1);
            gtk_grid_attach(GTK_GRID(app->boxes[row][col]),
                            app->labels_infection[row][col], 0, 1, 1, 5);

            /* Attach the box to the grid */
            gtk_grid_attach(GTK_GRID(app->grid), app->boxes[row][col], row, col,
                            1,
                            1);
        }
    }

    return app->grid;
}

void clean_citizen_labels(const Application *app) {
    for (size_t row = 0; row < CITY_ROWS; row++) {
        for (size_t col = 0; col < CITY_COLUMNS; col++) {
            for (size_t z = 0; z < TYPES_OF_CHARACTER; ++z) {
                gtk_widget_hide(GTK_WIDGET(app->images_citizens[row][col][z]));
            }
            gtk_widget_hide(GTK_WIDGET(app->labels_burnt_bodies[row][col]));
            gtk_widget_hide(GTK_WIDGET(app->labels_doctors[row][col]));
            gtk_widget_hide(GTK_WIDGET(app->labels_firefighters[row][col]));
            gtk_widget_hide(GTK_WIDGET(app->labels_citizen[row][col]));
            gtk_widget_hide(GTK_WIDGET(app->labels_dead_citizens[row][col]));
        }
    }
}

static gboolean update_window(gpointer data) {
    Application *app = data;
    update_simulation_board(app);
    return TRUE;
}

void update_simulation_board(const Application *app) {
    int citizens;
    int doctors;
    int firefighters;
    int dead_citizens;
    int burnt_bodies;

    for (int row = 0; row < CITY_ROWS; row++) {
        for (int col = 0; col < CITY_COLUMNS; col++) {
            update_infection_labels(app, row, col);

            citizens = 0;
            doctors = 0;
            firefighters = 0;
            dead_citizens = 0;
            burnt_bodies = 0;

            count_citizens(app, row, col, &citizens, &doctors, &firefighters, &dead_citizens,
                           &burnt_bodies);

            int citizen_counts[] = {citizens, firefighters, doctors, dead_citizens, burnt_bodies};

            GtkWidget *labels[] = {GTK_WIDGET(app->labels_citizen[row][col]),
                                   GTK_WIDGET(app->labels_firefighters[row][col]),
                                   GTK_WIDGET(app->labels_doctors[row][col]),
                                   GTK_WIDGET(
                                           app->labels_dead_citizens[row][col]),
                                   GTK_WIDGET(app->labels_burnt_bodies[row][col])};

            GtkWidget *images[] = {
                    GTK_WIDGET(app->images_citizens[row][col][0]),
                    GTK_WIDGET(app->images_citizens[row][col][1]),
                    GTK_WIDGET(app->images_citizens[row][col][2]),
                    GTK_WIDGET(app->images_citizens[row][col][3]),
                    GTK_WIDGET(app->images_citizens[row][col][4])};

            update_citizen_labels_and_images(app, row, col, citizen_counts,
                                             labels,
                                             images);
        }
    }
}

void update_infection_labels(const Application *app, int row, int col) {
    char number[5];
    Facade *facade;
    int infection;

    facade = app->simulation_facade;
    infection = facade->get_infection(facade, row, col);

    sprintf(number, "%d%%", (infection * 100));
    gtk_label_set_text(GTK_LABEL(app->labels_infection[row][col]), number);

    if (infection > 0.8) {
        gtk_widget_set_name(app->labels_infection[row][col], "contamination4");
    } else if (infection > 0.6) {
        gtk_widget_set_name(app->labels_infection[row][col], "contamination3");
    } else if (infection > 0.4) {
        gtk_widget_set_name(app->labels_infection[row][col], "contamination2");
    } else if (infection > 0.2) {
        gtk_widget_set_name(app->labels_infection[row][col], "contamination1");
    } else {
        gtk_widget_set_name(app->labels_infection[row][col], "normal");
    }
}

void count_citizens(const Application *app, int row, int col, int *citizens, int *doctors, int *firefighters, int *dead_citizens, int *burnt_bodies) {
    *citizens = app->simulation_facade->memory->n_of_citizens[row][col];
    *doctors = app->simulation_facade->memory->n_of_doctors[row][col];
    *firefighters = app->simulation_facade->memory->n_of_firefighters[row][col];
    *dead_citizens = app->simulation_facade->memory->n_of_dead_citizens[row][col];
    *burnt_bodies = app->simulation_facade->memory->n_of_ashes[row][col];
}

void update_citizen_labels_and_images(const Application *app, int row, int col,
                                      const int citizen_counts[], GtkWidget *labels[],
                                      GtkWidget *images[]) {
    char count[4];

    for (int i = 0; i < TYPES_OF_CHARACTER; i++) {
        if (citizen_counts[i] == 0) {
            gtk_widget_hide(images[i]);
            gtk_widget_hide(labels[i]);
        } else {
            sprintf(count, "%d", citizen_counts[i]);
            gtk_label_set_text(GTK_LABEL(labels[i]), count);
            gtk_widget_show(images[i]);
            gtk_widget_show(labels[i]);
        }
    }
}

static void stop_simulation(GtkWidget *window, gpointer data) {
    Application *app = data;

    /* Free the images, labels and boxes of the simulation board */
    /*
    for (int row = 0; row < CITY_ROWS; row++) {
        for (int col = 0; col < CITY_COLUMNS; col++) {
            gtk_widget_destroy(app->boxes[row][col]);
            gtk_widget_destroy(app->images[row][col]);
            for (int i = 0; i < TYPES_OF_CHARACTER; i++) {
                gtk_widget_destroy(app->images_citizens[row][col][i]);
            }
            gtk_widget_destroy(app->labels_firefighters[row][col]);
            gtk_widget_destroy(app->labels_citizen[row][col]);
            gtk_widget_destroy(app->labels_doctors[row][col]);
            gtk_widget_destroy(app->labels_dead_citizens[row][col]);
            gtk_widget_destroy(app->labels_burnt_bodies[row][col]);
            gtk_widget_destroy(app->labels_infection[row][col]);
        }
    }
    */

    /* Free the widgets of the main window */
    /*
    gtk_widget_destroy(app->grid);
    gtk_widget_destroy(app->window);
    */

    /* UNCOMMENT THE FOLLOWING LINE WHEN YOUR PROCESSES WILL RUN */
    //kill(facade->get_pid_epidemic_sim(facade), SIGINT);
    sleep(1);
}
