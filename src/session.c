#include "session.h"


int main(int argc, char *argv [])
{   
    struct Data data;
    GError *error = NULL;
    gchar *filename = NULL;
    
    gtk_init(&argc, &argv);


    data.builder = gtk_builder_new();


    filename =  g_build_filename ("/usr/share/diffusio/glade/diffusio.glade", NULL);

    if(!gtk_builder_add_from_file(data.builder, filename, &error))
    {
      gint code = error->code;
      g_printerr("%s\n", error->message);
      g_error_free (error);
      return code;
    }
    g_free (filename);


    data.sessiondata.SessionWindow = GTK_WIDGET(gtk_builder_get_object(data.builder, "SessionWindow"));
    gtk_widget_set_size_request(data.sessiondata.SessionWindow, 400, 300);

    data.sessiondata.new_button = GTK_WIDGET(gtk_builder_get_object(data.builder, "session_new_new_button"));
    data.sessiondata.newtab_delete_button = GTK_WIDGET(gtk_builder_get_object(data.builder, "session_new_delete_button"));
    data.sessiondata.opentab_delete_button = GTK_WIDGET(gtk_builder_get_object(data.builder, "session_open_delete_button"));
    data.sessiondata.opentab_open_button = GTK_WIDGET(gtk_builder_get_object(data.builder, "session_open_open_button"));


    data.sessiondata.name_entry = GTK_ENTRY(gtk_builder_get_object(data.builder, "session_new_name_entry"));

    data.sessiondata.new_chooser = GTK_FILE_CHOOSER(gtk_builder_get_object(data.builder, "session_new_chooser"));
    data.sessiondata.open_chooser = GTK_FILE_CHOOSER(gtk_builder_get_object(data.builder, "session_open_chooser"));

    data.sessiondata.folder_label = GTK_LABEL(gtk_builder_get_object(data.builder, "session_new_folder_label"));


    gtk_widget_set_sensitive(data.sessiondata.newtab_delete_button, 0);
    gtk_widget_set_sensitive(data.sessiondata.new_button, 0);
    gtk_widget_set_sensitive(data.sessiondata.opentab_delete_button, 0);
    gtk_widget_set_sensitive(data.sessiondata.opentab_open_button, 0);


    gtk_label_set_label(data.sessiondata.folder_label, "");


    gtk_builder_connect_signals(data.builder, &data);
    gtk_widget_show_all(data.sessiondata.SessionWindow);

    gtk_main();

    return 0;
}


G_MODULE_EXPORT void openAboutWindow(GtkMenuItem *menuitem, gpointer user_data)
{

    struct Data *dataAboutW = (struct Data*) user_data;
    GtkWidget *dialog = GTK_WIDGET (gtk_builder_get_object (dataAboutW->builder, "AboutWindow"));

    gtk_dialog_run (GTK_DIALOG (dialog));


    gtk_widget_hide (dialog);
}


G_MODULE_EXPORT void session_new_changed(GtkWidget *widget, struct Data *widgets)
{

    const gchar *text = gtk_entry_get_text(widgets->sessiondata.name_entry);
    const gchar *folder = gtk_file_chooser_get_uri(widgets->sessiondata.new_chooser);


    if(folder != NULL)
        gtk_label_set_label(widgets->sessiondata.folder_label, &folder[7]);


    if(folder != NULL || text[0] != '\0')
        gtk_widget_set_sensitive(widgets->sessiondata.newtab_delete_button, 1);

    else 
        gtk_widget_set_sensitive(widgets->sessiondata.newtab_delete_button, 0);


    if(folder != NULL && text[0] != '\0')
        gtk_widget_set_sensitive(widgets->sessiondata.new_button, 1);

    else 
        gtk_widget_set_sensitive(widgets->sessiondata.new_button, 0);
}




G_MODULE_EXPORT void session_new_delete(GtkWidget *widget, struct Data *widgets)
{
    gtk_entry_set_text(widgets->sessiondata.name_entry, "");
    if(gtk_file_chooser_get_uri(widgets->sessiondata.new_chooser) != NULL)
        gtk_file_chooser_unselect_uri(widgets->sessiondata.new_chooser, gtk_file_chooser_get_uri(widgets->sessiondata.new_chooser));

    gtk_label_set_label(widgets->sessiondata.folder_label, "");
}





G_MODULE_EXPORT void session_open_chooser_selection_changed_cb(GtkWidget *widget, struct Data *widgets)
{
    const gchar *folder = gtk_file_chooser_get_uri(widgets->sessiondata.open_chooser);

    if(folder != NULL)
    {
        gtk_widget_set_sensitive(widgets->sessiondata.opentab_delete_button, 1);
        gtk_widget_set_sensitive(widgets->sessiondata.opentab_open_button, 1);
    }
    else
    {
        gtk_widget_set_sensitive(widgets->sessiondata.opentab_delete_button, 0);
        gtk_widget_set_sensitive(widgets->sessiondata.opentab_open_button, 0);
    }

}




//will go in main.c
G_MODULE_EXPORT void open_file(GtkMenuItem *menuitem, struct Data *widget)
{
    GtkWidget *dialog_open = GTK_WIDGET(gtk_builder_get_object (widget->builder, "FileChooserDialog"));

    gint response = gtk_dialog_run (GTK_DIALOG (dialog_open));

    if(response == OPEN)
    {
        char *folder;
        folder = gtk_file_chooser_get_filename(widget->sessiondata.new_chooser);
        //open file
        g_free(folder);
    }
    //todo else

    gtk_widget_hide (dialog_open);

}

G_MODULE_EXPORT void session_open_delete_button_clicked_cb(GtkWidget *widget, struct Data *widgets)
{
    gtk_file_chooser_unselect_uri(widgets->sessiondata.open_chooser, gtk_file_chooser_get_uri(widgets->sessiondata.open_chooser));
}