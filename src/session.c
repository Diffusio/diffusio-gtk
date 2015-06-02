#include "session.h"


int main(int argc, char *argv [])
{
    struct Data data;

    GError *error = NULL;
    gchar *filename = NULL;

    gtk_init(&argc, &argv);

    data.builder = gtk_builder_new();

    filename =  g_build_filename ("../../src/diffusio.glade", NULL);

    if(!gtk_builder_add_from_file(data.builder, filename, &error))
    {
      gint code = error->code;
      g_printerr("%s\n", error->message);
      g_error_free (error);
      getchar();
      return code;
    }

    data.sessiondata.splash_window = GTK_WIDGET(gtk_builder_get_object(data.builder, "splash_screen"));

    gtk_builder_connect_signals(data.builder, &data);
    gtk_widget_show_all(data.sessiondata.splash_window);
    jsmn_init(&(data.p));

    data.news.id = 0;
    g_free (filename);

    load_widgets(&data);

    g_timeout_add(2000, close_splash, &data);
    gtk_main();


    return 0;
}

gboolean close_splash(struct Data *data)
{
    gtk_widget_hide(data->sessiondata.splash_window);
    gtk_widget_show_all(data->sessiondata.SessionWindow);
    return(FALSE);
}


void load_widgets(struct Data *data)
{
    data->sessiondata.SessionWindow = GTK_WIDGET(gtk_builder_get_object(data->builder, "SessionWindow"));
    gtk_widget_set_size_request(data->sessiondata.SessionWindow, 400, 300);

    data->sessiondata.new_button = GTK_WIDGET(gtk_builder_get_object(data->builder, "session_new_new_button"));
    data->sessiondata.newtab_delete_button = GTK_WIDGET(gtk_builder_get_object(data->builder, "session_new_delete_button"));
    data->sessiondata.opentab_delete_button = GTK_WIDGET(gtk_builder_get_object(data->builder, "session_open_delete_button"));
    data->sessiondata.opentab_open_button = GTK_WIDGET(gtk_builder_get_object(data->builder, "session_open_open_button"));


    data->sessiondata.name_entry = GTK_ENTRY(gtk_builder_get_object(data->builder, "session_new_name_entry"));

    data->sessiondata.new_chooser = GTK_FILE_CHOOSER(gtk_builder_get_object(data->builder, "session_new_chooser"));
    data->sessiondata.open_chooser = GTK_FILE_CHOOSER(gtk_builder_get_object(data->builder, "session_open_chooser"));

    data->sessiondata.folder_label = GTK_LABEL(gtk_builder_get_object(data->builder, "session_new_folder_label"));

    data->sessiondata.about = GTK_WIDGET (gtk_builder_get_object (data->builder, "AboutWindow"));

    data->sessiondata.dialog_fexists = GTK_WIDGET(gtk_builder_get_object(data->builder, "dialog_fexists"));


    gtk_widget_set_sensitive(data->sessiondata.newtab_delete_button, 0);
    gtk_widget_set_sensitive(data->sessiondata.new_button, 0);
    gtk_widget_set_sensitive(data->sessiondata.opentab_delete_button, 0);
    gtk_widget_set_sensitive(data->sessiondata.opentab_open_button, 0);

    data->new_content.dialog = GTK_WIDGET(gtk_builder_get_object(data->builder, "dialog1"));

    data->new_content.title = GTK_WIDGET(gtk_builder_get_object(data->builder, "title"));
    data->new_content.content = GTK_WIDGET(gtk_builder_get_object(data->builder, "content"));
    data->new_content.summary = GTK_WIDGET(gtk_builder_get_object(data->builder, "summary"));

    data->maindata.quit = GTK_WIDGET(gtk_builder_get_object(data->builder, "exit"));
    data->maindata.addnew_button = GTK_WIDGET(gtk_builder_get_object(data->builder, "add"));
    data->maindata.current_template = GTK_LABEL(gtk_builder_get_object(data->builder, "current_template_label"));

    data->maindata.template_button[MATERIAL] = GTK_WIDGET(gtk_builder_get_object(data->builder, "template_button1"));
    data->maindata.template_button[FLAT] = GTK_WIDGET(gtk_builder_get_object(data->builder, "template_button2"));
    data->maindata.template_button[SOBER] = GTK_WIDGET(gtk_builder_get_object(data->builder, "template_button3"));
    data->maindata.template_button[CLASSIC] = GTK_WIDGET(gtk_builder_get_object(data->builder, "template_button4"));

    data->maindata.title1 = GTK_ENTRY(gtk_builder_get_object(data->builder, "title1"));
    data->maindata.title2 = GTK_ENTRY(gtk_builder_get_object(data->builder, "title2"));
    data->maindata.title3 = GTK_ENTRY(gtk_builder_get_object(data->builder, "title3"));
    data->maindata.logo1 = GTK_FILE_CHOOSER(gtk_builder_get_object(data->builder, "logo1"));
    data->maindata.logo2 = GTK_FILE_CHOOSER(gtk_builder_get_object(data->builder, "logo2"));
    data->maindata.logo3 = GTK_FILE_CHOOSER(gtk_builder_get_object(data->builder, "logo3"));
    data->maindata.content1 = GTK_TEXT_VIEW(gtk_builder_get_object(data->builder, "content1"));
    data->maindata.content2 = GTK_TEXT_VIEW(gtk_builder_get_object(data->builder, "content2"));
    data->maindata.content3 = GTK_TEXT_VIEW(gtk_builder_get_object(data->builder, "content3"));

    data->maindata.address = GTK_ENTRY(gtk_builder_get_object(data->builder, "address"));
    data->maindata.mail = GTK_ENTRY(gtk_builder_get_object(data->builder, "mail"));
    data->maindata.fbname = GTK_ENTRY(gtk_builder_get_object(data->builder, "fbname"));
    data->maindata.fblink = GTK_ENTRY(gtk_builder_get_object(data->builder, "fblink"));
    data->maindata.twname = GTK_ENTRY(gtk_builder_get_object(data->builder, "twname"));
    data->maindata.twlink = GTK_ENTRY(gtk_builder_get_object(data->builder, "twlink"));
    data->maindata.gpname = GTK_ENTRY(gtk_builder_get_object(data->builder, "gpname"));
    data->maindata.gplink = GTK_ENTRY(gtk_builder_get_object(data->builder, "gplink"));

    data->infos.logo1 = NULL;
    data->infos.logo2 = NULL;
    data->infos.logo3 = NULL;
    data->infos.content1= NULL;
    data->infos.content2 = NULL;
    data->infos.content3 = NULL;

    data->maindata.site_title = GTK_ENTRY(gtk_builder_get_object(data->builder, "site_title"));

    data->infos.address = "";
    data->infos.mail = "";
    data->infos.fbname = "";
    data->infos.fblink = "";
    data->infos.twname = "";
    data->infos.twlink = "";
    data->infos.gpname  = "";
    data->infos.gplink = "";

    strcpy(data->maindata.index_path,"../../res/templates/");
    strcpy(data->maindata.res_path, "../../res/templates/");

    data->template_selected[0] = NULL;

    data->maindata.errdial = GTK_WIDGET(gtk_builder_get_object(data->builder, "no_template_dialog"));

    data->maindata.render = GTK_BUTTON(gtk_builder_get_object(data->builder, "render"));
}

G_MODULE_EXPORT void openAboutWindow(GtkWidget *menuitem, struct Data *data)
{
    gtk_dialog_run (GTK_DIALOG (data->sessiondata.about));
    gtk_widget_hide (data->sessiondata.about);
}


G_MODULE_EXPORT void session_new_changed(GtkWidget *widget, struct Data *data)
{

    const gchar *text = gtk_entry_get_text(data->sessiondata.name_entry);
    const gchar *folder = gtk_file_chooser_get_uri(data->sessiondata.new_chooser);


    if(folder != NULL)
        gtk_label_set_label(data->sessiondata.folder_label, &folder[8]);


    if(folder != NULL || text[0] != '\0')
        gtk_widget_set_sensitive(data->sessiondata.newtab_delete_button, 1);

    else
        gtk_widget_set_sensitive(data->sessiondata.newtab_delete_button, 0);


    if(folder != NULL && text[0] != '\0')
        gtk_widget_set_sensitive(data->sessiondata.new_button, 1);

    else
        gtk_widget_set_sensitive(data->sessiondata.new_button, 0);

    g_free(folder);
}




G_MODULE_EXPORT void session_new_delete(GtkWidget *widget, struct Data *data)
{
    gtk_entry_set_text(data->sessiondata.name_entry, "");
    if(gtk_file_chooser_get_uri(data->sessiondata.new_chooser) != NULL)
        gtk_file_chooser_unselect_uri(data->sessiondata.new_chooser, gtk_file_chooser_get_uri(data->sessiondata.new_chooser));

    gtk_label_set_label(data->sessiondata.folder_label, "");
}





G_MODULE_EXPORT void session_open_chooser_selection_changed_cb(GtkWidget *widget, struct Data *data)
{
    const gchar *folder = gtk_file_chooser_get_uri(data->sessiondata.open_chooser);

    if(folder != NULL)
    {
        gtk_widget_set_sensitive(data->sessiondata.opentab_delete_button, 1);
        gtk_widget_set_sensitive(data->sessiondata.opentab_open_button, 1);
    }
    else
    {
        gtk_widget_set_sensitive(data->sessiondata.opentab_delete_button, 0);
        gtk_widget_set_sensitive(data->sessiondata.opentab_open_button, 0);
    }

}




G_MODULE_EXPORT void session_open_delete_button_clicked_cb(GtkWidget *widget, struct Data *data)
{
    gtk_file_chooser_unselect_uri(data->sessiondata.open_chooser, gtk_file_chooser_get_uri(data->sessiondata.open_chooser));
}
