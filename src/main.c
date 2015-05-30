#include "main.h"


G_MODULE_EXPORT void new_session(GtkButton *button, struct Data *data)
{
    struct stat buf;
    gchar *path = gtk_file_chooser_get_uri(data->sessiondata.new_chooser);
    strcpy(path, &path[8]);
    strcat(path, "/");
    strcat(path, gtk_entry_get_text(data->sessiondata.name_entry));
    strcat(path, ".diffusio");

    errno = 0;
    if (!(stat(path, &buf) != 0 && errno == ENOENT)) //si le fichier spécifié existe
    {
        if(gtk_dialog_run(GTK_DIALOG(data->sessiondata.dialog_fexists)))
        {
            gint status = remove(path);

            if( status == 0 )
                printf("%s file deleted successfully.\n",path);
            else
            {
                printf("Unable to delete the file\n");
                perror("Error");
            }
        }
    }
    gtk_widget_hide(data->sessiondata.dialog_fexists);
    data->save = fopen(path, "ab+");
    openMainWindow(data);
}



void openMainWindow(struct Data *data)
{
    data->maindata.MainWindow = GTK_WIDGET(gtk_builder_get_object (data->builder, "MainWindow"));
    data->maindata.addnew_button = GTK_WIDGET(gtk_builder_get_object(data->builder, "add"));


    gtk_widget_hide (data->sessiondata.SessionWindow);
    gtk_widget_show_all(GTK_WIDGET(data->maindata.MainWindow));
}


G_MODULE_EXPORT void quit(gpointer *osef, struct Data *data)
{
    fclose(data->save);
    gtk_main_quit();
}

G_MODULE_EXPORT void open_file(GtkMenuItem *menuitem, struct Data *data)
{
    GtkWidget *dialog_open = GTK_WIDGET(gtk_builder_get_object (data->builder, "FileChooserDialog"));

    gint response = gtk_dialog_run (GTK_DIALOG (dialog_open));

    if(response == OPEN)
    {
        char *folder;
        folder = gtk_file_chooser_get_filename(data->sessiondata.new_chooser);
        //open file
        g_free(folder);
    }
    //todo else

    gtk_widget_hide (dialog_open);

}
