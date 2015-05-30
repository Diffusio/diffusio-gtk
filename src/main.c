#include "main.h"


G_MODULE_EXPORT void new_session(GtkButton *button, struct Data *data)
{
    struct stat buf;
    strcpy(data->savefile_path, gtk_file_chooser_get_uri(data->sessiondata.new_chooser));
    strcpy(data->savefile_path, &data->savefile_path[8]);
    strcat(data->savefile_path, "/");
    strcat(data->savefile_path, gtk_entry_get_text(data->sessiondata.name_entry));
    strcat(data->savefile_path, ".diffusio");

    strcpy(data->template_path, "../../res/templates/");

    errno = 0;
    if (!(stat(data->savefile_path, &buf) != 0 && errno == ENOENT)) //si le fichier spécifié existe
    {
        if(gtk_dialog_run(GTK_DIALOG(data->sessiondata.dialog_fexists)))
        {
            gint status = remove(data->savefile_path);

            if( status == 0 )
                printf("%s file deleted successfully.\n",data->savefile_path);
            else
            {
                printf("Unable to delete the file\n");
                perror("Error");
            }
        }
    }
    gtk_widget_hide(data->sessiondata.dialog_fexists);
    data->save = fopen(data->savefile_path, "ab+");
    openMainWindow(data);
}


G_MODULE_EXPORT void change_material(GtkWidget *widget, struct Data *data)
{
    gtk_label_set_text(data->maindata.current_template, "Template currently selected : Material");
    memset(data->template_selected, 0, 8);
    strcpy(data->template_selected, "material");

}

G_MODULE_EXPORT void change_flat(GtkWidget *widget, struct Data *data)
{
    gtk_label_set_label(data->maindata.current_template, "Template currently selected : Flat");
    memset(data->template_selected, 0, 8);
    strcpy(data->template_selected, "flat");
}

G_MODULE_EXPORT void change_sober(GtkWidget *widget, struct Data *data)
{
    gtk_label_set_label(data->maindata.current_template, "Template currently selected : Sober");
    memset(data->template_selected, 0, 8);
    strcpy(data->template_selected, "sober");
}

G_MODULE_EXPORT void change_classic(GtkWidget *widget, struct Data *data)
{
    gtk_label_set_label(data->maindata.current_template, "Template currently selected : Classic");
    memset(data->template_selected, 0, 8);
    strcpy(data->template_selected, "classic");
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
