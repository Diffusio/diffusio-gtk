/*
 * Diffusio - Build presentation websites easily
 * https://github.com/diffusio
 * http://diffusio.co
 * 
 * Copyright (C) 2015 
 * 
 * Pierre JACQUIER  
 * http://pierre-jacquier.com
 * 
 * Grégoire DUVAUCHELLE
 * https://github.com/kalterkrieg
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 2.1 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public 
*/


#include "addnews.h"


int copyFile(char file1[99], char file2[99])
{
	FILE *f1, *f2;
	f1 = fopen(file1,"r");
	f2 = fopen(file2,"w+");
	if(f1 == NULL)
        return 1;

	char line[999];
	while(fgets(line, 999, f1) != NULL)
		fputs(line,f2);
	fclose(f1);
	fclose(f2);
	return 0;
}

int getLastNewsId(char file[99])
{
	FILE *fichier;
	fichier = fopen(file, "r");
	char ligne[1000];
	int buffer;
	while(fgets(ligne, 1000, fichier) != NULL)
		if(ligne[0] == '<' && ligne[1] == '!' && ligne[2] == '-' && ligne[3] == '-' && ligne[4] == '#' && ligne[5] == '#')
			if(buffer < atoi(&ligne[6]))
				buffer = atoi(&ligne[6]);
	fclose(fichier);
	return buffer;
}

void addANews(struct Data *data)
{
	FILE *in, *out;
	int id;
	in = fopen(data->news.file_in, "r");
	out = fopen(data->news.file_out, "w+");
	id = data->news.id + 1;
	char ligne[1000];

	while(fgets(ligne, 1000, in) != NULL)
		if(!(strncmp(ligne, "<!--#$#NEW--", 11)))
			fprintf(out, "<!--#$#NEW-->\n\n<!--##%d-->\n\n<div class='card elevation-1 news' id='news_%d'><div class='news_datetime' id='news_datetime_%d'>%s</div><span class='news_title'   id='news_title_%d'><a class='pointer' onclick='openNews(%d);'>%s</a> </span><p class='news_summary'>%s</p><p class='news_content'  id='news_content_%d'>%s</p><div class='read_more'><a class='pointer' onclick='openCircleNews(%d)'>READ MORE</a></div></div>\n\n", id,id,id,data->news.datetime,id,id,data->news.title,data->news.summary,id,data->news.content,id);
		else
			fputs(ligne, out);
	fclose(in);
	fclose(out);
}


G_MODULE_EXPORT gboolean prepareNews (GdkEventKey *event, struct Data *data)
{
    if(data->template_selected[0] == NULL)
    {
        open_error_dialog(data, "Select a template first!");
        return FALSE;
    }

    char temp[50];
    strcpy(temp, data->template_path);
    strcat(temp, "/index_temp.html");

    if(copyFile(data->maindata.res_path, temp))
    {
        open_error_dialog(data, "Render the website at least once");
        return FALSE;
    }

	data->news.id = getLastNewsId(temp);
    strcpy(data->news.title,gtk_entry_get_text(GTK_ENTRY(data->new_content.title)));
    strcpy(data->news.summary,gtk_entry_get_text(GTK_ENTRY(data->new_content.summary)));
    strcpy(data->news.content,gtk_entry_get_text(GTK_ENTRY(data->new_content.content)));
    time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	sprintf(data->news.datetime,"%d/%d/%d %d:%d:%d\n",  tm.tm_mon + 1,tm.tm_mday,  tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
	strcpy(data->news.file_in, temp);
	strcpy(data->news.file_out, data->maindata.res_path);
	addANews(data);
    gtk_dialog_run(GTK_DIALOG(data->new_content.dialog));
    gtk_widget_hide(GTK_WIDGET(data->new_content.dialog));
	return TRUE;
}


