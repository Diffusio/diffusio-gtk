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
    fprintf(data->save, "{\n\t\"site_title\": \"\",\n\t\"logo1\": \"\",\n\t\"title1\": \"\",\n\t\"content1\": \"\",\n\t\"logo2\": \"\",\n\t\"title2\": \"\",\n\t\"content2\": \"\",\n\t\"logo3\": \"\",\n\t\"title3\": \"\",\n\t\"content3\": \"\",\n\t\"address\": \"\",\n\t\"facebook_link\": \"\",\n\t\"facebook_id\": \"\",\n\t\"twitter_link\": \"\",\n\t\"twitter_id\": \"\",\n\t\"googleplus_link\": \"\",\n\t\"googleplus_id\": \"\",\n\t\"mail\": \"\"\n}");
    openMainWindow(data);
}

void update_template_path(struct Data *data)
{
    memset(&(data->template_path[20]), 0, 8);
    strcpy(&(data->template_path[20]), data->template_selected);
}

G_MODULE_EXPORT int update_infos(GtkWidget *widget, gpointer user_data)
{
    struct Data *data = user_data;
    if(GTK_IS_ENTRY(widget))
    {
        if(data->maindata.title1 != NULL)
            data->infos.title1 = gtk_entry_get_text(GTK_ENTRY(data->maindata.title1));
        if(data->maindata.title2 != NULL)
            data->infos.title2 = gtk_entry_get_text(GTK_ENTRY(data->maindata.title2));
        if(data->maindata.title3 != NULL)
            data->infos.title3 = gtk_entry_get_text(GTK_ENTRY(data->maindata.title3));
    }
    else if(GTK_IS_FILE_CHOOSER(widget))
    {
        if(data->infos.logo1 != NULL)
            data->infos.logo1 = gtk_file_chooser_get_uri(GTK_FILE_CHOOSER(data->maindata.logo1));
        if(data->infos.logo2 != NULL)
            data->infos.logo2 = gtk_file_chooser_get_uri(GTK_FILE_CHOOSER(data->maindata.logo2));
        if(data->infos.logo3 != NULL)
            data->infos.logo3 = gtk_file_chooser_get_uri(GTK_FILE_CHOOSER(data->maindata.logo3));
    }
    else if(GTK_IS_TEXT_VIEW(widget))
    {
        GtkTextBuffer *buffer = NULL;
        GtkTextIter start, end;
        if(data->maindata.content1 != NULL)
        {
            buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(data->maindata.content1));
            gtk_text_buffer_get_bounds(buffer, &start, &end);
            data->infos.content1 = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
        }
        if(data->maindata.content2 != NULL)
        {
            buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(data->maindata.content2));
            gtk_text_buffer_get_bounds(buffer, &start, &end);
            data->infos.content2 = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
        }
        if(data->maindata.content3 != NULL)
        {
            buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(data->maindata.content3));
            gtk_text_buffer_get_bounds(buffer, &start, &end);
            data->infos.content3 = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
        }


    }

    update_html(data);
    return FALSE;
}

void update_html(struct Data *data)
{
    int i;
    char ligne[500];
    while(fgets(ligne, 500, data->maindata.index) != NULL)
        if(!(strncmp(ligne, "<!--$SITE_TITLE$-->", 18)))
        {
            fprintf(data->maindata.res, "<!--$SITE_TITLE$-->\n%s\n<!--$/SITE_TITLE$-->\n", data->infos.site_title);
            fgets(ligne, 500, data->maindata.index);
            fgets(ligne, 500, data->maindata.index);
        }
        else if(!(strncmp(ligne, "<!--$PRESENTATION_PART1_TITLE$-->", 28)))
        {
            fprintf(data->maindata.res, "<!--$PRESENTATION_PART1_TITLE$-->\n%s\n<!--$/PRESENTATION_PART1_TITLE$-->\n", data->infos.title1);
            fgets(ligne, 500, data->maindata.index);
            fgets(ligne, 500, data->maindata.index);
        }
        else if(!(strncmp(ligne, "<!--$PRESENTATION_PART2_TITLE$-->", 28)))
        {
            fprintf(data->maindata.res, "<!--$PRESENTATION_PART2_TITLE$-->\n%s\n<!--$/PRESENTATION_PART2_TITLE$-->\n", data->infos.title2);
            fgets(ligne, 500, data->maindata.index);
            fgets(ligne, 500, data->maindata.index);
        }
        else if(!(strncmp(ligne, "<!--$PRESENTATION_PART3_TITLE$-->", 28)))
        {
            fprintf(data->maindata.res, "<!--$PRESENTATION_PART3_TITLE$-->\n%s\n<!--$/PRESENTATION_PART3_TITLE$-->\n", data->infos.title3);
            fgets(ligne, 500, data->maindata.index);
            fgets(ligne, 500, data->maindata.index);
        }
        else if(!(strncmp(ligne, "<!--$PRESENTATION_PART1_CONTENT$-->", 28)))
        {
            fprintf(data->maindata.res, "<!--$PRESENTATION_PART1_CONTENT$-->\n%s\n<!--$/PRESENTATION_PART1_CONTENT$-->\n", data->infos.content1);
            fgets(ligne, 500, data->maindata.index);
            fgets(ligne, 500, data->maindata.index);
        }
        else if(!(strncmp(ligne, "<!--$PRESENTATION_PART2_CONTENT$-->", 28)))
        {
            fprintf(data->maindata.res, "<!--$PRESENTATION_PART2_CONTENT$-->\n%s\n<!--$/PRESENTATION_PART2_CONTENT$-->\n", data->infos.content2);
            fgets(ligne, 500, data->maindata.index);
            fgets(ligne, 500, data->maindata.index);
        }
        else if(!(strncmp(ligne, "<!--$PRESENTATION_PART3_CONTENT$-->", 28)))
        {
            fprintf(data->maindata.res, "<!--$PRESENTATION_PART3_CONTENT$-->\n%s\n<!--$/PRESENTATION_PART3_CONTENT$-->\n", data->infos.content3);
            fgets(ligne, 500, data->maindata.index);
            fgets(ligne, 500, data->maindata.index);
        }
        else if(!(strncmp(ligne, "<!--$ADDRESS$-->", 14)))
        {
            fprintf(data->maindata.res, "<!--$ADDRESS$-->\n%s\n<!--$/ADDRESS$-->\n", data->infos.address);
            fgets(ligne, 500, data->maindata.index);
            fgets(ligne, 500, data->maindata.index);
        }
        else if(!(strncmp(ligne, "<!--$FACEBOOK$-->", 14)))
        {
            fprintf(data->maindata.res, "<!--$FACEBOOK-->\n\n\t\t\t\t\t<a href=\"%s\">\n\t\t\t\t\t<li>\n\t\t\t\t\t\t<div class=\"icon_rounder\" id=\"ic_fb\"><img id=\"fb_img\" src=\"images/facebook.png\"></div>\n\t\t\t\t\t\t<span id=\"fb_id\">%s</span>\n\t\t\t\t\t</li>\n\t\t\t\t\t</a>\n<!--$/FACEBOOK$-->", data->infos.fblink, data->infos.fbid);
            for(i = 0; i<10; i++)
                fgets(ligne, 500, data->maindata.index);
        }
        else if(!(strncmp(ligne, "<!--$TWITTER-->", 14)))
        {
            fprintf(data->maindata.res, "<!--$TWITTER-->\n<a href=\"%s\">\n<li>\n<div class=\"icon_rounder\" id=\"ic_tw\"><img id=\"tw_img\" src=\"images/twitter.png\"></div>\n<span id=\"tw_id\">\%s\n</span>\n</li>\n</a><!--$/TWITTER-->\n", data->infos.twlink, data->infos.twid);
            for(i = 0; i<10; i++)
                fgets(ligne, 500, data->maindata.index);
        }
        else if(!(strncmp(ligne, "<!--$GOOGLEPLUS-->", 15)))
        {
            fprintf(data->maindata.res, "<!--$GOOGLEPLUS-->\n<a href=\"%s\">\n<li>\n<div class=\"icon_rounder\" id=\"ic_gp\"><img id=\"gp_img\" src=\"images/googleplus.png\"></div>\n<span id=\"gp_id\">\n%s\n</span>\n</li>\n</a>\n<!--$/GOOGLEPLUS-->\n", data->infos.gplink, data->infos.gpid);
            for(i = 0; i<10; i++)
                fgets(ligne, 500, data->maindata.index);
        }
        else if(!(strncmp(ligne, "<!--$MAIL$-->", 14)))
        {
            fprintf(data->maindata.res, "<!--$MAIL-->\n<a href=\"mailto:%s\">\n<li>\n<div class=\"icon_rounder\" id=\"ic_m\"><img id=\"m_img\" src=\"images/mail.png\"></div>\n<span id=\"m_id\">\n%s/n</span>\n</li>\n</a>\n<!--$/MAIL-->\n", data->infos.mail, data->infos.mail);
            for(i = 0; i<10; i++)
                fgets(ligne, 500, data->maindata.index);
        }
        else
            fputs(ligne, data->maindata.res);

}

G_MODULE_EXPORT void change_template(GtkWidget *widget, struct Data *data)
{
    memset(data->template_selected, 0, 8);
    if(widget == data->maindata.template_button[MATERIAL])
    {
        gtk_label_set_text(data->maindata.current_template, "Template currently selected : Material");
        strcpy(data->template_selected, "material");
        update_template_path(data);
    }
    else if(widget == data->maindata.template_button[FLAT])
    {
        gtk_label_set_text(data->maindata.current_template, "Template currently selected : Flat");
        strcpy(data->template_selected, "flat");
        update_template_path(data);
    }
    else if(widget == data->maindata.template_button[SOBER])
    {
        gtk_label_set_text(data->maindata.current_template, "Template currently selected : Sober");
        strcpy(data->template_selected, "sober");
        update_template_path(data);
    }
    else if(widget == data->maindata.template_button[CLASSIC])
    {
        gtk_label_set_text(data->maindata.current_template, "Template currently selected : Classic");
        strcpy(data->template_selected, "classic");
        update_template_path(data);
    }

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
    int i;
    fclose(data->save);
    if(data->infos.logo1 != NULL)
        g_free(data->infos.logo1);
    if(data->infos.logo2 != NULL)
        g_free(data->infos.logo2);
    if(data->infos.logo3 != NULL)
        g_free(data->infos.logo3);
    if(data->infos.content1 != NULL)
        g_free(data->infos.content1);
    if(data->infos.content2 != NULL)
        g_free(data->infos.content2);
    if(data->infos.content3 != NULL)
        g_free(data->infos.content3);

    fclose(data->maindata.index);
    fclose(data->maindata.res);


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
