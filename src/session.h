#ifndef SESSION
#define SESSION

#include <gtk/gtk.h>
#include "main.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "addnews.h"
#include "struct.h"

#define OPEN 0
#define CANCEL 1



void load_widgets(struct Data *data);

G_MODULE_EXPORT void change_material(GtkWidget *widget, struct Data *data);
G_MODULE_EXPORT void change_flat(GtkWidget *widget, struct Data *data);
G_MODULE_EXPORT void change_sober(GtkWidget *widget, struct Data *data);
G_MODULE_EXPORT void change_classic(GtkWidget *widget, struct Data *data);

G_MODULE_EXPORT void openAboutWindow (GtkWidget *menuitem, gpointer user_data);

G_MODULE_EXPORT void cb_changed(GtkButton *button, struct Data *widget);

G_MODULE_EXPORT void session_new_delete(GtkWidget *widget, struct Data *widgets);

G_MODULE_EXPORT void session_open_chooser_selection_changed_cb(GtkWidget *widget, struct Data *widgets);

G_MODULE_EXPORT void session_open_delete_button_clicked_cb(GtkWidget *widget, struct Data *widgets);
#endif
