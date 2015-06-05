#include "main.h"

/*

G_MODULE_EXPORT void new_session(GtkButton *button, struct Data *data)
{
    struct stat buf;
    char savetemp[100];
    strcpy(savetemp, gtk_file_chooser_get_uri(data->sessiondata.new_chooser));
    strcpy(data->save_path, &savetemp[8]);
    strcat(data->save_path, "/");
    strcat(data->save_path, gtk_entry_get_text(data->sessiondata.name_entry));
    strcat(data->save_path, ".diffusio");



    errno = 0;
    if (!(stat(data->save_path, &buf) != 0 && errno == ENOENT)) //si le fichier spécifié existe
    {
        if(gtk_dialog_run(GTK_DIALOG(data->sessiondata.dialog_fexists)))
        {
            gint status = remove(data->save_path);

            if( status == 0 )
            {
                printf("%s file deleted successfully.\n",data->save_path);
                data->save = fopen(data->save_path, "w");
            }
            else
            {
                printf("Unable to delete the file\n");
                perror("Error");
            }

        }
        else
        {
            data->save = fopen(data->save_path, "r");
            open_file(NULL, data);
        }
    }
    gtk_widget_hide(data->sessiondata.dialog_fexists);
    openMainWindow(data);
}

static int jsoneq(const char *json, jsmntok_t *tok, const char *s)
{
	if (tok->type == JSMN_STRING && (int) strlen(s) == tok->end - tok->start &&
			strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
		return 0;
	}
	return -1;
}

G_MODULE_EXPORT int open_file(GtkWidget *widget, struct Data *data)
{
    //if(widget != NULL)
    // ouvrir une filechooserdialog et ouvrir le fichier
	int i;
	int r;
	jsmntok_t t[128];
    char JSON_STRING[] ="{\"template\": \"\",\"site_title\": \"auie\",\"title1\": \"eiua\",\"content1\": \"auie\",\"logo2\": \"\",\"title2\": \"\",	\"content2\": \"\",\"logo3\": \"\",\"title3\": \"\",\"content3\": \"\",	\"address\": \"\",\"facebook_link\": \"\",\"logo1\": \"C:/Users/kk/Documents/MEGA/diffusio-gtk/res/diffusio-logo_128.png\",	\"facebook_name\": \"\",\"twitter_link\": \"\",	\"twitter_name\": \"\",\"googleplus_link\": \"\",	\"googleplus_name\": \"\",\"mail\": \"\"}";

    char ligne[500], temp[100];
    while(fgets(ligne, 500, data->save) != NULL)
    {
        strcat(JSON_STRING, ligne);
    }


        puts(JSON_STRING);

	r = jsmn_parse(&(data->p), JSON_STRING, strlen(JSON_STRING), t, sizeof(t)/sizeof(t[0]));

	if (r < 0) {
		printf("Failed to parse JSON: %d\n", r);
		return 1;
	}
	if (r < 1 || t[0].type != JSMN_OBJECT) {
		printf("Object expected\n");
		return 1;
	}
	for (i = 1; i < r; i++)
    {
		if (jsoneq(JSON_STRING, &t[i], "site_title") == 0) {
			sprintf(temp, "%.*s\n", t[i+1].end-t[i+1].start, JSON_STRING + t[i+1].start);
			strcpy(data->infos.site_title, temp);
			i++;
		} else if (jsoneq(JSON_STRING, &t[i], "template") == 0) {
			sprintf(temp, "%.*s\n", t[i+1].end-t[i+1].start, JSON_STRING + t[i+1].start);
			strcpy(data->template_selected, temp);
			i++;
		} else if (jsoneq(JSON_STRING, &t[i], "logo1") == 0) {
			sprintf(temp, "%.*s\n", t[i+1].end-t[i+1].start, JSON_STRING + t[i+1].start);
			strcpy(data->infos.logo1, temp);
			i++;
		} else if (jsoneq(JSON_STRING, &t[i], "content1") == 0) {
			sprintf(temp, "%.*s\n", t[i+1].end-t[i+1].start, JSON_STRING + t[i+1].start);
			strcpy(data->infos.content1, temp);
			i++;
		}else if (jsoneq(JSON_STRING, &t[i], "title1") == 0) {
			sprintf(temp, "%.*s\n", t[i+1].end-t[i+1].start, JSON_STRING + t[i+1].start);
			strcpy(data->infos.title1, temp);
			i++;
		}else if (jsoneq(JSON_STRING, &t[i], "logo2") == 0) {
			sprintf(temp, "%.*s\n", t[i+1].end-t[i+1].start, JSON_STRING + t[i+1].start);
			strcpy(data->infos.logo2, temp);
			i++;
		}else if (jsoneq(JSON_STRING, &t[i], "title2") == 0) {
			sprintf(temp, "%.*s\n", t[i+1].end-t[i+1].start, JSON_STRING + t[i+1].start);
			strcpy(data->infos.title2, temp);
			i++;
		}else if (jsoneq(JSON_STRING, &t[i], "content2") == 0) {
			sprintf(temp, "%.*s\n", t[i+1].end-t[i+1].start, JSON_STRING + t[i+1].start);
			strcpy(data->infos.content2, temp);
			i++;
		}else if (jsoneq(JSON_STRING, &t[i], "logo3") == 0) {
			sprintf(temp, "%.*s\n", t[i+1].end-t[i+1].start, JSON_STRING + t[i+1].start);
			strcpy(data->infos.logo3, temp);
			i++;
		}else if (jsoneq(JSON_STRING, &t[i], "title3") == 0) {
			sprintf(temp, "%.*s\n", t[i+1].end-t[i+1].start, JSON_STRING + t[i+1].start);
			strcpy(data->infos.title3, temp);
			i++;
		}else if (jsoneq(JSON_STRING, &t[i], "content3") == 0) {
			sprintf(temp, "%.*s\n", t[i+1].end-t[i+1].start, JSON_STRING + t[i+1].start);
			strcpy(data->infos.content3, temp);
			i++;
		}else if (jsoneq(JSON_STRING, &t[i], "address") == 0) {
			sprintf(temp, "%.*s\n", t[i+1].end-t[i+1].start, JSON_STRING + t[i+1].start);
			strcpy(data->infos.address, temp);
			i++;
		}else if (jsoneq(JSON_STRING, &t[i], "facebook_link") == 0) {
			sprintf(temp, "%.*s\n", t[i+1].end-t[i+1].start, JSON_STRING + t[i+1].start);
			strcpy(data->infos.fblink, temp);
			i++;
		}else if (jsoneq(JSON_STRING, &t[i], "facebook_name") == 0) {
			sprintf(temp, "%.*s\n", t[i+1].end-t[i+1].start, JSON_STRING + t[i+1].start);
			strcpy(data->infos.fbname, temp);
			i++;
		}else if (jsoneq(JSON_STRING, &t[i], "twitter_link") == 0) {
			sprintf(temp, "%.*s\n", t[i+1].end-t[i+1].start, JSON_STRING + t[i+1].start);
			strcpy(data->infos.twlink, temp);
			i++;
		}else if (jsoneq(JSON_STRING, &t[i], "twitter_name") == 0) {
			sprintf(temp, "%.*s\n", t[i+1].end-t[i+1].start, JSON_STRING + t[i+1].start);
			strcpy(data->infos.twname, temp);
			i++;
		}else if (jsoneq(JSON_STRING, &t[i], "googleplus_link") == 0) {
			sprintf(temp, "%.*s\n", t[i+1].end-t[i+1].start, JSON_STRING + t[i+1].start);
			strcpy(data->infos.gplink, temp);
			i++;
		}else if (jsoneq(JSON_STRING, &t[i], "googleplus_name") == 0) {
			sprintf(temp, "%.*s\n", t[i+1].end-t[i+1].start, JSON_STRING + t[i+1].start);
			strcpy(data->infos.gpname, temp);
			i++;
		}else if (jsoneq(JSON_STRING, &t[i], "mail") == 0) {
			sprintf(temp, "%.*s\n", t[i+1].end-t[i+1].start, JSON_STRING + t[i+1].start);
			strcpy(data->infos.mail, temp);
			i++;
		} else {
			printf("Unexpected key: %.*s\n", t[i].end-t[i].start,
					JSON_STRING + t[i].start);
		}
	}

    update_entries(data);
}

void update_entries(struct Data *data)
{
    gtk_entry_set_text(GTK_ENTRY(data->maindata.site_title), data->infos.site_title);
    gtk_file_chooser_set_uri(GTK_FILE_CHOOSER(data->maindata.logo1), data->infos.logo1);
    gtk_entry_set_text(GTK_ENTRY(data->maindata.title1), data->infos.title1);
    gtk_entry_set_text(GTK_ENTRY(data->maindata.content1), data->infos.content1);
    gtk_file_chooser_set_uri(GTK_FILE_CHOOSER(data->maindata.logo2), data->infos.logo2);
    gtk_entry_set_text(GTK_ENTRY(data->maindata.title2), data->infos.title2);
    gtk_entry_set_text(GTK_ENTRY(data->maindata.content2), data->infos.content2);
    gtk_file_chooser_set_uri(GTK_FILE_CHOOSER(data->maindata.logo3), data->infos.logo3);
    gtk_entry_set_text(GTK_ENTRY(data->maindata.title3), data->infos.title3);
    gtk_entry_set_text(GTK_ENTRY(data->maindata.content3), data->infos.content3);
    gtk_entry_set_text(GTK_ENTRY(data->maindata.address), data->infos.address);
    gtk_entry_set_text(GTK_ENTRY(data->maindata.fblink), data->infos.fblink);
    gtk_entry_set_text(GTK_ENTRY(data->maindata.fbname), data->infos.fbname);
    gtk_entry_set_text(GTK_ENTRY(data->maindata.twlink), data->infos.twlink);
    gtk_entry_set_text(GTK_ENTRY(data->maindata.twname), data->infos.twname);
    gtk_entry_set_text(GTK_ENTRY(data->maindata.gplink), data->infos.gplink);
    gtk_entry_set_text(GTK_ENTRY(data->maindata.gpname), data->infos.gpname);
    gtk_entry_set_text(GTK_ENTRY(data->maindata.mail), data->infos.mail);

}*/


void open_error_dialog(struct Data *data, const gchar *message)
{
    GtkWidget *dialog;
    GtkDialogFlags flags;

    flags = GTK_DIALOG_DESTROY_WITH_PARENT;
    dialog = gtk_message_dialog_new(GTK_WINDOW(data->maindata.MainWindow),
                                    flags,
                                    GTK_MESSAGE_ERROR,
                                    GTK_BUTTONS_OK,
                                    message);
    gtk_window_set_resizable(GTK_WINDOW(dialog), FALSE);
    gtk_dialog_run (GTK_DIALOG(dialog));
    gtk_widget_destroy (dialog);
}

void get_infos(struct Data *data) //récupère le contenu des entries et les entres dans les variable de la sous structure infos
{

    data->infos.site_title = gtk_entry_get_text(GTK_ENTRY(data->maindata.site_title));

    data->infos.title1 = gtk_entry_get_text(GTK_ENTRY(data->maindata.title1));
    data->infos.title2 = gtk_entry_get_text(GTK_ENTRY(data->maindata.title2));
    data->infos.title3 = gtk_entry_get_text(GTK_ENTRY(data->maindata.title3));

    if(gtk_file_chooser_get_uri(GTK_FILE_CHOOSER(data->maindata.logo1)) != NULL)
        data->infos.logo1 = &(gtk_file_chooser_get_uri(GTK_FILE_CHOOSER(data->maindata.logo1))[8]);
    if(gtk_file_chooser_get_uri(GTK_FILE_CHOOSER(data->maindata.logo2)) != NULL)
        data->infos.logo2 = &(gtk_file_chooser_get_uri(GTK_FILE_CHOOSER(data->maindata.logo2))[8]);
    if(gtk_file_chooser_get_uri(GTK_FILE_CHOOSER(data->maindata.logo3)) != NULL)
        data->infos.logo3 = &(gtk_file_chooser_get_uri(GTK_FILE_CHOOSER(data->maindata.logo3))[8]);

    data->infos.address = gtk_entry_get_text(GTK_ENTRY(data->maindata.address));
    data->infos.mail = gtk_entry_get_text(GTK_ENTRY(data->maindata.mail));
    data->infos.fbname = gtk_entry_get_text(GTK_ENTRY(data->maindata.fbname));
    data->infos.fblink = gtk_entry_get_text(GTK_ENTRY(data->maindata.fblink));
    data->infos.twname = gtk_entry_get_text(GTK_ENTRY(data->maindata.twname));
    data->infos.twlink = gtk_entry_get_text(GTK_ENTRY(data->maindata.twlink));
    data->infos.gpname = gtk_entry_get_text(GTK_ENTRY(data->maindata.gpname));
    data->infos.gplink = gtk_entry_get_text(GTK_ENTRY(data->maindata.gplink));


    data->buffer = NULL;
    GtkTextIter start, end;

        data->buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(data->maindata.content1));
        gtk_text_buffer_get_bounds(data->buffer, &start, &end);
        data->infos.content1 = gtk_text_buffer_get_text(data->buffer, &start, &end, FALSE);

        data->buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(data->maindata.content2));
        gtk_text_buffer_get_bounds(data->buffer, &start, &end);
        data->infos.content2 = gtk_text_buffer_get_text(data->buffer, &start, &end, FALSE);

        data->buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(data->maindata.content3));
        gtk_text_buffer_get_bounds(data->buffer, &start, &end);
        data->infos.content3 = gtk_text_buffer_get_text(data->buffer, &start, &end, FALSE);

}

void displayRenderer(struct Data *data)
{
    char start[50];
    system("SET var=%cd%");
    sprintf(start, "start QtWeb.exe %%cd%%\\res\\templates\\%sindex.html", data->template_selected);
    printf("%s",start);
    system(start);
}


G_MODULE_EXPORT int update_infos(GtkWidget *widget, struct Data *data)
{

    if(data->template_selected[0] == 0){ //Vérifie que l'utilisateur à choisis une template
        open_error_dialog(data, "Select a template first!");
        return TRUE;
    }
    get_infos(data);

    if(verif_html_comment(data)) //vérifie que l'utilisateur n'entre pas de commentaire html dans les entries ( <!-- )
    {
        open_error_dialog(data, "Tu veux tout casser ou quoi!?");
        return TRUE;
    }

    char *temp ;
    temp = repl_str(data->infos.content1, "\n", "<br>");  //change les retour à la ligne \n en <br>
    strcpy(data->infos.content1, temp);
    temp = repl_str(data->infos.content2, "\n", "<br>");
    strcpy(data->infos.content2, temp);
    temp = repl_str(data->infos.content2, "\n", "<br>");
    strcpy(data->infos.content2, temp);

    update_html(data);
    copy_logo(data);

    displayRenderer(data);

    return FALSE;
}

void copy_logo(struct Data *data)
{
    FILE *src, *dest;
    char temp[50];

    struct stat st = {0};

    if(data->infos.logo1 != NULL)
    {
        src = fopen(data->infos.logo1, "rb");
        strcpy(temp, data->template_path);
        strcat(temp, "/images/");
        strcat(temp, "logo1.png");
        dest = fopen(temp, "wb");
        size_t n, m;
        unsigned int buff[8192];
        do {
            n = fread(buff, 1, sizeof buff, src);
            if (n) m = fwrite(buff, 1, n, dest);
            else   m = 0;
        } while ((n > 0) && (n == m));
        if (m) perror("copy");

        if (fclose(src)) perror("close output file");
        if (fclose(dest)) perror("close input file");
    }

    if(data->infos.logo2 != NULL)
    {
        src = fopen(data->infos.logo2, "rb");
        strcpy(temp, data->template_path);
        strcat(temp, "/images/");
        strcat(temp, "logo2.png");
        dest = fopen(temp, "wb");
        size_t n, m;
        unsigned int buff[8192];
        do {
            n = fread(buff, 1, sizeof buff, src);
            if (n) m = fwrite(buff, 1, n, dest);
            else   m = 0;
        } while ((n > 0) && (n == m));
        if (m) perror("copy");

        if (fclose(src)) perror("close output file");
        if (fclose(dest)) perror("close input file");
    }

    if(data->infos.logo3 != NULL)
    {
        src = fopen(data->infos.logo3, "rb");
        strcpy(temp, data->template_path);
        strcat(temp, "/images/");
        strcat(temp, "logo3.png");
        dest = fopen(temp, "wb");
        size_t n, m;
        unsigned int buff[8192];
        do {
            n = fread(buff, 1, sizeof buff, src);
            if (n) m = fwrite(buff, 1, n, dest);
            else   m = 0;
        } while ((n > 0) && (n == m));
        if (m) perror("copy");

        if (fclose(src)) perror("close output file");
        if (fclose(dest)) perror("close input file");
    }

}

int verif_html_comment(struct Data *data)
{
    if(strstr(data->infos.content1, "<!--") ||
       strstr(data->infos.content2, "<!--") ||
       strstr(data->infos.content3, "<!--") ||
       strstr(data->infos.mail, "<!--") ||
       strstr(data->infos.fblink, "<!--") ||
       strstr(data->infos.gplink, "<!--") ||
       strstr(data->infos.twlink, "<!--") ||
       strstr(data->infos.fbname, "<!--") ||
       strstr(data->infos.address, "<!--") ||
       strstr(data->infos.gpname, "<!--") ||
       strstr(data->infos.site_title, "<!--") ||
       strstr(data->infos.title1, "<!--") ||
       strstr(data->infos.title2, "<!--") ||
       strstr(data->infos.title3, "<!--"))
        return 1;
    else return 0;
}

void update_html(struct Data *data) //génère index.html en remplaçant les balises de index_var par les valeurs entrées par l'utilisateur
{

    data->maindata.index = fopen(data->maindata.index_path, "r");
    data->maindata.res = fopen(data->maindata.res_path, "w+");

    int i;
    char ligne[500];
    while(fgets(ligne, 500, data->maindata.index) != NULL)
        if(!strncmp(ligne, "        <title>", 13))
        {
            fprintf(data->maindata.res, "		<title>\n%s\n", data->infos.site_title);
            fgets(ligne, 500, data->maindata.index);
        }
        else if(!strncmp(ligne, "<!--$SITE_TITLE$-->", 18))
        {
            fprintf(data->maindata.res, "<!--$SITE_TITLE$-->\n%s\n", data->infos.site_title);
            fgets(ligne, 500, data->maindata.index);
        }
        else if(!(strncmp(ligne, "<!--$PRESENTATION_PART1_TITLE$-->", 28)))
        {
            fprintf(data->maindata.res, "<!--$PRESENTATION_PART1_TITLE$-->\n%s\n", data->infos.title1);
            fgets(ligne, 500, data->maindata.index);
        }
        else if(!(strncmp(ligne, "<!--$PRESENTATION_PART2_TITLE$-->", 28)))
        {
            fprintf(data->maindata.res, "<!--$PRESENTATION_PART2_TITLE$-->\n%s\n", data->infos.title2);
            fgets(ligne, 500, data->maindata.index);
        }
        else if(!(strncmp(ligne, "<!--$PRESENTATION_PART3_TITLE$-->", 28)))
        {
            fprintf(data->maindata.res, "<!--$PRESENTATION_PART3_TITLE$-->\n%s\n", data->infos.title3);
            fgets(ligne, 500, data->maindata.index);
        }
        else if(!(strncmp(ligne, "<!--$PRESENTATION_PART1_CONTENT$-->", 28)))
        {
            fprintf(data->maindata.res, "<!--$PRESENTATION_PART1_CONTENT$-->\n%s\n", data->infos.content1);
            fgets(ligne, 500, data->maindata.index);
        }
        else if(!(strncmp(ligne, "<!--$PRESENTATION_PART2_CONTENT$-->", 28)))
        {
            fprintf(data->maindata.res, "<!--$PRESENTATION_PART2_CONTENT$-->\n%s\n\n", data->infos.content2);
            fgets(ligne, 500, data->maindata.index);
        }
        else if(!(strncmp(ligne, "<!--$PRESENTATION_PART3_CONTENT$-->", 28)))
        {
            fprintf(data->maindata.res, "<!--$PRESENTATION_PART3_CONTENT$-->\n%s\n\n", data->infos.content3);
            fgets(ligne, 500, data->maindata.index);
        }
        else if(!(strncmp(ligne, "                    <p id=\"map_legend_address\">", 40)))
        {
            fprintf(data->maindata.res, "                    <p id=\"map_legend_address\">\n%s\n", data->infos.address);
            fgets(ligne, 500, data->maindata.index);
            fgets(ligne, 500, data->maindata.index);
        }
        else if(!(strncmp(ligne, "<!--$FACEBOOK-->", 14)))
        {
            fprintf(data->maindata.res, "<!--$FACEBOOK-->\n\n\t\t\t\t\t<a href=\"%s\">\n<li>\n<div class=\"icon_rounder\" id=\"ic_fb\"><img id=\"fb_img\" src=\"images/facebook.png\"></div>\n<span id=\"fb_id\">%s</span>\n</li>\n</a>\n", data->infos.fblink, data->infos.fbname);
            for(i = 0; i<9; i++)
                fgets(ligne, 500, data->maindata.index);
        }
        else if(!(strncmp(ligne, "<!--$TWITTER-->", 14)))
        {
            fprintf(data->maindata.res, "<!--$TWITTER-->\n<a href=\"%s\">\n<li>\n<div class=\"icon_rounder\" id=\"ic_tw\"><img id=\"tw_img\" src=\"images/twitter.png\"></div>\n<span id=\"tw_id\">\n%s\n</span>\n</li>\n</a>\n\n", data->infos.twlink, data->infos.twname);
            for(i = 0; i<9; i++)
                fgets(ligne, 500, data->maindata.index);
        }
        else if(!(strncmp(ligne, "<!--$GOOGLEPLUS-->", 15)))
        {
            fprintf(data->maindata.res, "<!--$GOOGLEPLUS-->\n<a href=\"%s\">\n<li>\n<div class=\"icon_rounder\" id=\"ic_gp\"><img id=\"gp_img\" src=\"images/googleplus.png\"></div>\n<span id=\"gp_id\">\n%s\n</span>\n</li>\n</a>\n\n", data->infos.gplink, data->infos.gpname);
            for(i = 0; i<8; i++)
                fgets(ligne, 500, data->maindata.index);
        }
        else if(strncmp(ligne, "<!--$MAIL$-->\n", 8) == 0)
        {
            fprintf(data->maindata.res, "<!--$MAIL-->\n<a href=\"mailto:%s\">\n<li>\n<div class=\"icon_rounder\" id=\"ic_m\"><img id=\"m_img\" src=\"images/mail.png\"></div>\n<span id=\"m_id\">\n%s\n</span>\n</li>\n</a>\n\n", data->infos.mail, data->infos.mail);
            for(i = 0; i<8; i++)
                fgets(ligne, 500, data->maindata.index);
        }
        else
            fputs(ligne, data->maindata.res);


    fclose(data->maindata.index);
    fclose(data->maindata.res);



}

G_MODULE_EXPORT void change_template(GtkWidget *widget, struct Data *data)
{
    strcpy(data->template_selected, "");
    if(widget == data->maindata.template_button[MATERIAL])  //on regarde quel bouton a généré le signal
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

void update_template_path(struct Data *data)
{

    strcpy(data->template_path,"res/templates/");

    memset(&(data->template_path[14]), 0, 8);

    strcpy(&(data->template_path[14]), data->template_selected);

    memset(data->maindata.index_path, 0, 50);
    strcpy(data->maindata.index_path, data->template_path);
    strcat(data->maindata.index_path, "/index_var.html");


    memset(data->maindata.res_path, 0, 50);
    strcpy(data->maindata.res_path, data->template_path);
    strcat(data->maindata.res_path, "/index.html");

}

/*
void openMainWindow(struct Data *data)
{
    data->maindata.MainWindow = GTK_WIDGET(gtk_builder_get_object (data->builder, "MainWindow"));
    data->maindata.addnew_button = GTK_WIDGET(gtk_builder_get_object(data->builder, "add"));


    gtk_widget_hide (data->sessiondata.SessionWindow);
    gtk_widget_show_all(GTK_WIDGET(data->maindata.MainWindow));
}*/

G_MODULE_EXPORT int open_explorer(GtkButton* button, struct Data *data)
{
    if(data->template_selected[0] == 0){
        open_error_dialog(data, "Select a template first!");
        return TRUE;
    }
    char command[1024];
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    strcat(cwd, "\\res\\templates\\");
    strcat(cwd, data->template_selected);
    sprintf(command, "%%SystemRoot%%\\explorer.exe %s", cwd);
    system(command);
    return FALSE;
}
/*
G_MODULE_EXPORT void save(GtkWidget *widget, struct Data *data)
{
    get_infos(data);

    fprintf(data->save, "{\n\t\"template\": \"%s\",\n\t\"site_title\": \"%s\",\n\t\"logo1\": \"%s\",\n\t\"title1\": \"%s\",\n\t\"content1\": \"%s\",\n\t\"logo2\": \"%s\",\n\t\"title2\": \"%s\",\n\t\"content2\": \"%s\",\n\t\"logo3\": \"%s\",\n\t\"title3\": \"%s\",\n\t\"content3\": \"%s\",\n\t\"address\": \"%s\",\n\t\"facebook_link\": \"%s\",\n\t\"facebook_name\": \"%s\",\n\t\"twitter_link\": \"%s\",\n\t\"twitter_name\": \"%s\",\n\t\"googleplus_link\": \"%s\",\n\t\"googleplus_name\": \"%s\",\n\t\"mail\": \"\"\n}",
                data->template_selected,
                data->infos.site_title,
                data->infos.logo1,
                data->infos.title1,
                data->infos.content1,
                data->infos.logo2,
                data->infos.title2,
                data->infos.content2,
                data->infos.logo3,
                data->infos.title3,
                data->infos.content3,
                data->infos.address,
                data->infos.fblink,
                data->infos.fbname,
                data->infos.twlink,
                data->infos.twname,
                data->infos.gplink,
                data->infos.gpname,
                data->infos.mail);
}*/

G_MODULE_EXPORT void quit(gpointer *osef, struct Data *data)
{
    if(data->infos.logo1 != NULL)
        g_free(data->infos.logo1);
    if(data->infos.logo2 != NULL)
        g_free(data->infos.logo2);
    if(data->infos.logo3 != NULL)
        g_free(data->infos.logo3);



    gtk_main_quit();
}

char *repl_str(const char *str, const char *old, const char *new) //licence : domaine publique
{

	/* Adjust each of the below values to suit your needs. */

	/* Increment positions cache size initially by this number. */
	size_t cache_sz_inc = 16;
	/* Thereafter, each time capacity needs to be increased,
	 * multiply the increment by this factor. */
	const size_t cache_sz_inc_factor = 3;
	/* But never increment capacity by more than this number. */
	const size_t cache_sz_inc_max = 1048576;

	char *pret, *ret = NULL;
	const char *pstr2, *pstr = str;
	size_t i, count = 0;
	ptrdiff_t *pos_cache = NULL;
	size_t cache_sz = 0;
	size_t cpylen, orglen, retlen, newlen, oldlen = strlen(old);

	/* Find all matches and cache their positions. */
	while ((pstr2 = strstr(pstr, old)) != NULL) {
		count++;

		/* Increase the cache size when necessary. */
		if (cache_sz < count) {
			cache_sz += cache_sz_inc;
			pos_cache = realloc(pos_cache, sizeof(*pos_cache) * cache_sz);
			if (pos_cache == NULL) {
				goto end_repl_str;
			}
			cache_sz_inc *= cache_sz_inc_factor;
			if (cache_sz_inc > cache_sz_inc_max) {
				cache_sz_inc = cache_sz_inc_max;
			}
		}

		pos_cache[count-1] = pstr2 - str;
		pstr = pstr2 + oldlen;
	}

	orglen = pstr - str + strlen(pstr);

	/* Allocate memory for the post-replacement string. */
	if (count > 0) {
		newlen = strlen(new);
		retlen = orglen + (newlen - oldlen) * count;
	} else	retlen = orglen;
	ret = malloc(retlen + 1);
	if (ret == NULL) {
		goto end_repl_str;
	}

	if (count == 0) {
		/* If no matches, then just duplicate the string. */
		strcpy(ret, str);
	} else {
		/* Otherwise, duplicate the string whilst performing
		 * the replacements using the position cache. */
		pret = ret;
		memcpy(pret, str, pos_cache[0]);
		pret += pos_cache[0];
		for (i = 0; i < count; i++) {
			memcpy(pret, new, newlen);
			pret += newlen;
			pstr = str + pos_cache[i] + oldlen;
			cpylen = (i == count-1 ? orglen : pos_cache[i+1]) - pos_cache[i] - oldlen;
			memcpy(pret, pstr, cpylen);
			pret += cpylen;
		}
		ret[retlen] = '\0';
	}

end_repl_str:
	/* Free the cache and return the post-replacement string,
	 * which will be NULL in the event of an error. */
	free(pos_cache);
	return ret;
}
