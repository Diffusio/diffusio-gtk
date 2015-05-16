#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STARTCOMMENTBOOL ligne[0] == '<' && ligne[1] == '!' && ligne[2] == '-' && ligne[3] == '-'

typedef struct News News;
struct News
{
	char file_news[99];
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
	f2 = fopen(file2,"r+");
	char line[999];
	while(fgets(line, 999, f1) != NULL)
		fputs(line,f2);
	fclose(f1);
	fclose(f2);
}

int getLastNewsId(char file[99])
{
	FILE *fichier, *output;
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
	FILE *in, *out, *new;
	int id;
	in = fopen(news->file_in, "r");
	new = fopen(news->file_news, "r");
	out = fopen(news->file_out, "r+");
	id = news->id + 1;
	char ligne[1000];
	while(fgets(ligne, 1000, in) != NULL)
		if(STARTCOMMENTBOOL && ligne[4] == '#' && ligne[5] == '$' && ligne[6] == '#' && ligne[7] == 'N' && ligne[8] == 'E' && ligne[9] == 'W')
			fprintf(out, "<!--#$#NEW-->\n\n<!--##%d-->\n\n<div class='card elevation-1 news' id='news_%d'><div class='news_datetime' id='news_datetime_%d'>04/21/2045 - 14:54</div><span class='news_title'   id='news_title_%d'><a class='pointer' onclick='openNews(%d);'>Added via C</a> </span><p class='news_summary'>First news ahah</p><p class='news_content'  id='news_content_%d'>%s</p><div class='read_more'><a class='pointer' onclick='openCircleNews(%d)'>READ MORE</a></div></div>\n\n", id,id,id,id,id,id,"CONTENT",id);
	else
			fputs(ligne, out);
	fclose(in);
	fclose(out);
	fclose(new);
}

int main()
{
	News news;
	copyFile("index.html","index_temp.html");
	news.id = getLastNewsId("index_temp.html");
	printf("%d\n", news.id);
	strcpy(news.file_in,"index_temp.html");
	strcpy(news.file_out,"index.html");
	strcpy(news.file_news,"add_news.html");
	addANews(&news);
	return 0;
}