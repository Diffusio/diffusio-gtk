#ifndef SESSION
#define SESSION

#include <gtk/gtk.h>
#include "main.h"

typedef struct
{
    GtkBuilder *builder;
    gpointer user_data;
    GtkWidget *name_entry;
    GtkWidget *new_button;
    GtkWidget *delete_button;
    GtkWidget *SessionWindow;
    GtkWidget *chooser;
    GtkWidget *l;

}   SessionData;

G_MODULE_EXPORT void openAboutWindow (GtkMenuItem *menuitem, gpointer user_data);

G_MODULE_EXPORT void cb_changed(GtkButton *button, SessionData *widget);



#endif