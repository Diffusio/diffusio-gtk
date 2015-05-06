#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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


int getLastNewsId(char file[99])
{
	FILE *fichier, *output;
	fichier = fopen(file, "r");
	char ligne[1000];
	int buffer;
	while(fgets(ligne, 1000, fichier) != NULL)
		if(ligne[0] == '#' && ligne[1] == '#')
			if(buffer < atoi(&ligne[2]))
				buffer = atoi(&ligne[2]);
	fclose(fichier);
	return buffer;
}

void addANews(News *news)
{
	FILE *in, *out, *new;
	int id;
	in = fopen(news->file_in, "r");
	new = fopen(news->file_news, "r");
	out = fopen(news->file_out, "w");
	id = news->id;
	char ligne[1000];
	while(fgets(ligne, 1000, in) != NULL)
		if(ligne[0] != '#' && ligne[1] != '#' && ligne[2] != '#' && ligne[3] != 'N' && ligne[4] != 'E' && ligne[5] != 'W' && ligne[6] != 'S')
			fputs(ligne, out);
		else
			fprintf(out, "##%d\n", id);
	fclose(in);
	fclose(out);
	fclose(new);
}

int main()
{
	printf("%d\n", getLastNewsId("index_in.html"));
	News news;
	news.id = getLastNewsId("index_in.html");
	strcpy(news.file_in,"index_in.html");
	strcpy(news.file_out,"index.html");
	strcpy(news.file_news,"add_news.html");
	addANews(&news);
	return 0;
}