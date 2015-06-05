#ifndef SESSION
#define SESSION

#include <windows.h>
#include <gtk/gtk.h>
#include "main.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "addnews.h"
#include "struct.h"

#define OPEN 0
#define CANCEL 1



void load_widgets(struct Data*);
gboolean close_splash(struct Data*);

G_MODULE_EXPORT void openAboutWindow (GtkWidget*, struct Data*);

G_MODULE_EXPORT void cb_changed(GtkButton*, struct Data *);

G_MODULE_EXPORT void session_new_delete(GtkWidget*, struct Data *);

G_MODULE_EXPORT void session_open_chooser_selection_changed_cb(GtkWidget*, struct Data *);

G_MODULE_EXPORT void session_open_delete_button_clicked_cb(GtkWidget*, struct Data *);
#endif
