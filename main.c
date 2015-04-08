#include "main.h"

G_MODULE_EXPORT void openMainWindow(GtkMenuItem *menuitem, gpointer user_data)
{
    struct Data *maindata = (struct Data*) user_data;
    GtkWidget *MainWindow = GTK_WIDGET(gtk_builder_get_object (maindata->builder, "MainWindow"));
    gtk_widget_hide (maindata->sessiondata.SessionWindow);
    gtk_widget_show_all(GTK_WIDGET(MainWindow));
}