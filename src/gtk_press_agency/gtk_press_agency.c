#ifdef __APPLE__

#include <TargetConditionals.h>

#if TARGET_OS_MAC

#include <gtk/gtkx.h>

#endif
#elif __linux__
#include <gdk/gdkkeysyms.h>
#include <gtk/gtkx.h>
#endif

#include "gtk_press_agency.h"
#include "logger.h"

pid_t gnuplot_pid;

void activate(GtkApplication *gtk_app, gpointer data) {
    Application *app;
    GtkWidget *newspaper_board;

    app = data;
    app->window = gtk_application_window_new(gtk_app);
    gtk_widget_set_name(app->window, "background");

    g_signal_connect(GTK_WINDOW(app->window), "destroy", G_CALLBACK(stop_press_agency), app);

    gtk_window_set_title(GTK_WINDOW(app->window), "The City News Viewer");
    gtk_window_set_default_size(GTK_WINDOW(app->window), 0, 0);

    GtkWidget *main_layout = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    gtk_container_add(GTK_CONTAINER(app->window), main_layout);

    /* --------------------------- LOAD CSS FILE --------------------------- */
    apply_css("resources/theme.css");

    /* ------------------- KEY MANAGEMENT FOR ABOUT BOX -------------------- */
    gtk_widget_set_events(app->window, GDK_KEY_PRESS_MASK);
    g_signal_connect(app->window, "key-press-event", G_CALLBACK(on_key_press),
                     &gtk_app);

    /* ------------------------- NEWSPAPER BOARD --------------------------- */
    newspaper_board = create_newspaper_board(app);
    gtk_box_pack_start(GTK_BOX(main_layout), newspaper_board, TRUE, TRUE, 0);
    create_socket_to_gnuplot(newspaper_board);

    /* ------------------------------- ALL ---------------------------------- */
    g_timeout_add_seconds(1, (GSourceFunc) update_window, data);
    gtk_widget_show_all(app->window);
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

    gtk_about_dialog_set_program_name(about_dialog, "City news");
    gtk_about_dialog_set_version(about_dialog, "1.3");
    gtk_about_dialog_set_copyright(about_dialog, "2023 ENSICAEN");
    gtk_about_dialog_set_comments(
            about_dialog,
            "The newspaper of the press agency...");
    gtk_about_dialog_set_website(about_dialog,
                                 "https://gitlab.ecole.ensicaen.fr/alebret/epidemic_2023");
    gtk_about_dialog_set_authors(about_dialog, authors);
    gtk_about_dialog_set_logo_icon_name(about_dialog, "newspaper");

    gtk_dialog_run(GTK_DIALOG(about_dialog));
    gtk_widget_destroy(GTK_WIDGET(about_dialog));
}

GtkWidget *create_newspaper_board(Application *app) {
    GtkWidget *newspaper_board;
    GtkWidget *top_newspaper;

    newspaper_board = gtk_grid_new();
    gtk_grid_set_column_homogeneous(GTK_GRID(newspaper_board), TRUE);

    top_newspaper = gtk_fixed_new();
    gtk_fixed_put(GTK_FIXED(top_newspaper),
                  gtk_image_new_from_file("resources/newspaper_top.png"), 0, 0);

    app->label_day = gtk_label_new("d+0");
    gtk_fixed_put(GTK_FIXED(top_newspaper), app->label_day, 20, 15);
    gtk_widget_set_name(app->label_day, "custom_day");

    app->label_headline = gtk_label_new("French President said \"Pensez Printemps\"");
    gtk_widget_set_name(app->label_headline, "custom_headline");
    gtk_fixed_put(GTK_FIXED(top_newspaper), app->label_headline, 54, 90);

    gtk_grid_attach(GTK_GRID(newspaper_board), top_newspaper, 0, 0, 3, 1);
    gtk_grid_attach(
            GTK_GRID(newspaper_board),
            gtk_image_new_from_file("resources/newspaper_center_right.png"), 2,
            1, 1,
            1);
    gtk_grid_attach(GTK_GRID(newspaper_board),
                    gtk_image_new_from_file("resources/newspaper_bottom.png"),
                    0,
                    3, 3, 1);

    return newspaper_board;
}

void create_socket_to_gnuplot(const GtkWidget *newspaper_area) {
#ifdef __APPLE__
    /* Do not work on Mac OS X */
#elif _WIN32
    /* Do not work on WSL (hoping the WIN32 macro is valid) */
#elif __linux__
    GtkWidget *socket;
    unsigned long socket_id;

    socket = gtk_socket_new();
    gtk_widget_set_size_request(socket, 360, 200);
    gtk_grid_attach(GTK_GRID(newspaper_area), socket, 0, 1, 2, 1);
    gtk_widget_show(socket);
    gtk_widget_realize(socket);
    socket_id = gtk_socket_get_id(GTK_SOCKET(socket));
    create_command_file(socket_id);

    gnuplot_pid = fork();
    if (!gnuplot_pid) {
      sleep(6); /* maximum time for a new day (avoid empty file) */
      execlp("gnuplot", "gnuplot", "commands.gp", (void *)0);
    }
#endif
}

void create_command_file(unsigned long socket_id) {
    FILE *fq;

    fq = fopen("commands.gp", "r+b");

    if (fq == NULL) {
        perror("Error opening \"commands.gp\"");
        exit(EXIT_FAILURE);
    }

    fprintf(fq, "set term x11 window \"%#lx\"\n", socket_id);
    fclose(fq);
}

static gboolean update_window(gpointer data) {
    Application *app = data;
    update_newspaper_board(app);
    return TRUE;
}

void update_newspaper_board(const Application *app) {
    int day;
    char day_string[6];
    char news[MSG_LENGTH];
    int priority;
    Channel *channel;

    day = 0;

    /*
     * Just receive the first news (max priority message).
     * DO WHAT YOU NEED WITH OTHER MESSAGES
     */
    if (app->channel == NULL) {
        return;
    }
    channel = app->channel;
    channel->receive_news(channel, &day, news, sizeof(news), &priority);
    if (priority == MAX_PRIORITY) {
        sprintf(day_string, "D+%d", day);
        gtk_label_set_text(GTK_LABEL(app->label_day), day_string);
        gtk_label_set_text(GTK_LABEL(app->label_headline), news);
    }
}

static void stop_press_agency(GtkWidget *window, gpointer data) {
    Application *app = data;

    destroy_channel(CHANNEL_NAME);
    kill(gnuplot_pid, SIGINT);
}
