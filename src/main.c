#include "main.h"

G_MODULE_EXPORT void openMainWindow(GtkMenuItem *menuitem, gpointer user_data)
{
    struct Data data = (struct Data*) user_data;
    data.maindata.MainWindow = GTK_WIDGET(gtk_builder_get_object (data->builder, "MainWindow"));
    data.maindata.addnews_button = GTK_WIDGET(gtk_builder_get_object(data->builder, "add"));
    
    gtk_widget_hide (maindata->sessiondata.SessionWindow);
    gtk_widget_show_all(GTK_WIDGET(MainWindow));
}