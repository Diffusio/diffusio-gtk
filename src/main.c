#include "main.h"

G_MODULE_EXPORT void openMainWindow(GtkMenuItem *menuitem, struct Data *data)
{
    data->maindata.MainWindow = GTK_WIDGET(gtk_builder_get_object (data->builder, "MainWindow"));
    data->maindata.addnews_button = GTK_WIDGET(gtk_builder_get_object(data->builder, "add"));

    gtk_widget_hide (data->sessiondata.SessionWindow);
    gtk_widget_show_all(GTK_WIDGET(data->maindata.MainWindow));
}
