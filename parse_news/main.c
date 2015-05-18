#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define STARTCOMMENTBOOL ligne[0] == '<' && ligne[1] == '!' && ligne[2] == '-' && ligne[3] == '-'

typedef struct NewContent NewContent;
struct NewContent
    {
    	    GtkWidget *title;
    		GtkWidget *content;
    		GtkWidget *summary;
    };

typedef struct News News;
struct News
{
	char file_in[99];
	char file_out[99]; 
	int id;
	char title[99]; 
	char datetime[20]; 
	char summary[200];
	char content[999];
};

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
		if(STARTCOMMENTBOOL && ligne[4] == '#' && ligne[5] == '#')
			if(buffer < atoi(&ligne[6]))
				buffer = atoi(&ligne[6]);
	fclose(fichier);
	return buffer;
}

void addANews(News *news)
{
	FILE *in, *out;
	int id;
	in = fopen(news->file_in, "r");
	out = fopen(news->file_out, "w+");
	id = news->id + 1;
	char ligne[1000];
	while(fgets(ligne, 1000, in) != NULL)
		if(STARTCOMMENTBOOL && ligne[4] == '#' && ligne[5] == '$' && ligne[6] == '#' && ligne[7] == 'N' && ligne[8] == 'E' && ligne[9] == 'W')
			fprintf(out, "<!--#$#NEW-->\n\n<!--##%d-->\n\n<div class='card elevation-1 news' id='news_%d'><div class='news_datetime' id='news_datetime_%d'>%s</div><span class='news_title'   id='news_title_%d'><a class='pointer' onclick='openNews(%d);'>%s</a> </span><p class='news_summary'>%s</p><p class='news_content'  id='news_content_%d'>%s</p><div class='read_more'><a class='pointer' onclick='openCircleNews(%d)'>READ MORE</a></div></div>\n\n", id,id,id,news->datetime,id,id,news->title,news->summary,id,news->content,id);
		else
			fputs(ligne, out);
	fclose(in);
	fclose(out);
}

gboolean closeDialog (GdkEventKey *event, NewContent *new_content, gpointer *window)
{
	gtk_widget_destroy(window);
	return TRUE;
}

gboolean prepareNews (GdkEventKey *event, NewContent *new_content)
{  
    News news;
    copyFile("index.html","index_temp.html");
	news.id = getLastNewsId("index_temp.html");
    strcpy(news.title,gtk_entry_get_text(GTK_ENTRY(new_content->title)));
    strcpy(news.summary,gtk_entry_get_text(GTK_ENTRY(new_content->summary)));
    strcpy(news.content,gtk_entry_get_text(GTK_ENTRY(new_content->content)));
    time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	sprintf(news.datetime,"%d/%d/%d %d:%d:%d\n",  tm.tm_mon + 1,tm.tm_mday,  tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
	strcpy(news.file_in,"index_temp.html");
	strcpy(news.file_out,"index.html");
	addANews(&news);
	GtkBuilder *gtkBuilder;
    GtkWidget *window;
    gtkBuilder = gtk_builder_new();
    gtk_builder_add_from_file(gtkBuilder, "ok_dialog.glade", NULL);
    window = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "dialog1"));
    GtkButton *quit = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "exit"));
    gtk_widget_show(window);	
    g_signal_connect(G_OBJECT(quit), "clicked", G_CALLBACK(closeDialog),window);
    return TRUE;
}

int main(int argc, char *argv[])
{
    GtkBuilder *gtkBuilder;
    GtkWidget *window;
    gtk_init(&argc, &argv);
    
    gtkBuilder = gtk_builder_new();
    gtk_builder_add_from_file(gtkBuilder, "addnews.glade", NULL);
    window = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "applicationwindow1"));
    gtk_widget_set_size_request(window, 400, 300);
    

    GtkLabel *label  = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "label1"));
    GtkButton *button = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "add"));
    gtk_label_set_label(label,"");
    gtk_widget_show(window);
    
    NewContent new_content;
    new_content.title = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "title"));
    new_content.content = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "content"));
    new_content.summary = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "summary"));
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(prepareNews),&new_content);
    gtk_main();
    
    return 0;
}