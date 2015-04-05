#include "session.h"


int main(int argc, char *argv [])
{
    SessionData sessiondata;
    GError *error = NULL;
    gchar *filename = NULL;
    
    gtk_init(&argc, &argv);


    sessiondata.builder = gtk_builder_new();


    filename =  g_build_filename ("diffusio.glade", NULL);

    if(!gtk_builder_add_from_file(sessiondata.builder, filename, &error))
    {
      gint code = error->code;
      g_printerr("%s\n", error->message);
      g_error_free (error);
      return code;
    }
    

    g_free (filename);

    sessiondata.SessionWindow = GTK_WIDGET(gtk_builder_get_object (sessiondata.builder, "SessionWindow"));
    gtk_widget_set_size_request(sessiondata.SessionWindow, 400, 300);

    sessiondata.new_button = GTK_WIDGET(gtk_builder_get_object(sessiondata.builder, "session_new_button"));
    sessiondata.delete_button = GTK_WIDGET(gtk_builder_get_object(sessiondata.builder, "session_delete_button"));
    sessiondata.name_entry = GTK_ENTRY(gtk_builder_get_object(sessiondata.builder, "session_new_name_entry"));
    sessiondata.chooser = GTK_WIDGET(gtk_builder_get_object(sessiondata.builder, "session_new_chooser"));
    sessiondata.l = GTK_WIDGET(gtk_builder_get_object(sessiondata.builder, "label2"));

    gtk_widget_set_sensitive(sessiondata.delete_button, 0);
    gtk_widget_set_sensitive(sessiondata.new_button, 0);


    gtk_builder_connect_signals(sessiondata.builder, &sessiondata);
    gtk_widget_show_all(sessiondata.SessionWindow);

    gtk_main();

    return 0;
}


G_MODULE_EXPORT void openAboutWindow(GtkMenuItem *menuitem, gpointer user_data)
{

    SessionData *sessiondata = (SessionData*) user_data;
    GtkWidget *dialog = GTK_WIDGET (gtk_builder_get_object (sessiondata->builder, "AboutWindow"));

    gtk_dialog_run (GTK_DIALOG (dialog));


    gtk_widget_hide (dialog);
}


G_MODULE_EXPORT void session_new_changed(GtkButton *button, SessionData *widget)
{

    gchar *text = gtk_entry_get_text(widget->name_entry);
    gchar *folder = gtk_file_chooser_get_uri(widget->chooser);

    gtk_label_set_label(widget->l, folder);

    if(text[0] == '\0' && folder[0] == '\0')
    {
        gtk_widget_set_sensitive(widget->new_button, 0);
        gtk_widget_set_sensitive(widget->delete_button, 0);
    }
    else
    {
        gtk_widget_set_sensitive(widget->new_button, 1);
        gtk_widget_set_sensitive(widget->delete_button, 1);
    }
}

G_MODULE_EXPORT void cb_clicked(GtkButton *button, SessionData *widget)
{

}