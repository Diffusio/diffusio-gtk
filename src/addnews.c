#include "addnews.h"

void copyFile(char file1[99], char file2[99])
{
	FILE *f1, *f2;
	f1 = fopen(file1,"r");
	f2 = fopen(file2,"w+");
	char line[999];
	while(fgets(line, 999, f1) != NULL)
		fputs(line,f2);
	fclose(f1);
	fclose(f2);
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
		if(STARTCOMMENTBOOL && ligne[4] == '#' && ligne[5] == '$' && ligne[6] == '#' && ligne[7] == 'N' && ligne[8] == 'E' && ligne[9] == 'W')
			fprintf(out, "<!--#$#NEW-->\n\n<!--##%d-->\n\n<div class='card elevation-1 news' id='news_%d'><div class='news_datetime' id='news_datetime_%d'>%s</div><span class='news_title'   id='news_title_%d'><a class='pointer' onclick='openNews(%d);'>%s</a> </span><p class='news_summary'>%s</p><p class='news_content'  id='news_content_%d'>%s</p><div class='read_more'><a class='pointer' onclick='openCircleNews(%d)'>READ MORE</a></div></div>\n\n", id,id,id,data->news.datetime,id,id,data->news.title,data->news.summary,id,data->news.content,id);
		else
			fputs(ligne, out);
	fclose(in);
	fclose(out);
}


G_MODULE_EXPORT gboolean prepareNews (GdkEventKey *event, struct Data *data)
{
    copyFile("../../src/index.html","../../src/index_temp.html");
	data->news.id = getLastNewsId("../../src/index_temp.html");
    strcpy(data->news.title,gtk_entry_get_text(GTK_ENTRY(data->new_content.title)));
    strcpy(data->news.summary,gtk_entry_get_text(GTK_ENTRY(data->new_content.summary)));
    strcpy(data->news.content,gtk_entry_get_text(GTK_ENTRY(data->new_content.content)));
    time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	sprintf(data->news.datetime,"%d/%d/%d %d:%d:%d\n",  tm.tm_mon + 1,tm.tm_mday,  tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
	strcpy(data->news.file_in,"../../src/index_temp.html");
	strcpy(data->news.file_out,"index.html");
	addANews(data);
    gtk_dialog_run(GTK_DIALOG(data->new_content.dialog));
    gtk_widget_hide(GTK_DIALOG(data->new_content.dialog));
	return TRUE;
}


