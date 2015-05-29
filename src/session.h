#ifndef SESSION
#define SESSION

#include <gtk/gtk.h>
#include "main.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define OPEN 0
#define CANCEL 1


struct SessionData
{
    GtkWidget *SessionWindow;


    GtkEntry *name_entry;

    GtkWidget *new_button;
    GtkWidget *newtab_delete_button;
    GtkWidget *opentab_delete_button;
    GtkWidget *opentab_open_button;

    GtkFileChooser *new_chooser;
    GtkFileChooser *open_chooser;

    GtkLabel *folder_label;

};

struct MainData
{
    GtkWidget *MainWindow;
    GtkButton *addnews_button;


};

struct Data
{
    GtkBuilder *builder;
    gpointer user_data;
    struct SessionData sessiondata;
    struct MainData maindata;

};

G_MODULE_EXPORT void openAboutWindow (GtkMenuItem *menuitem, gpointer user_data);

G_MODULE_EXPORT void cb_changed(GtkButton *button, struct Data *widget);

G_MODULE_EXPORT void session_new_delete(GtkWidget *widget, struct Data *widgets);

G_MODULE_EXPORT void session_open_chooser_selection_changed_cb(GtkWidget *widget, struct Data *widgets);

G_MODULE_EXPORT void session_open_delete_button_clicked_cb(GtkWidget *widget, struct Data *widgets);
#endif
