#include "main.h"

G_MODULE_EXPORT void openMainWindow(GtkMenuItem *menuitem, gpointer user_data)
{
    SessionData *sessiondata = (SessionData*) user_data;
    GtkWidget *MainWindow = GTK_WIDGET(gtk_builder_get_object (sessiondata->builder, "MainWindow"));
    gtk_widget_hide (sessiondata->SessionWindow);
    gtk_widget_show_all(GTK_WIDGET(MainWindow));
}