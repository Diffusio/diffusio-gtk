#include "parsecss.h"

int main()
{
	parseCss("style.css","out.css");
}

void parseCss(char *filein, char *fileout)
{
	FILE *in,*out;
	in = fopen(filein, "r");
	out = fopen(fileout, "w+");
		char line[1000];
		char *accentcolor, *fontcolor;
		int pos_accentcolor, pos_fontcolor;
		int i;
		while(fgets(line, 1000, in) != NULL)
		{
			accentcolor = strstr(line, "@AccentColor");
			fontcolor = strstr(line, "@FontColor");
			pos_accentcolor = accentcolor - line;
			pos_fontcolor = fontcolor - line;
			if(accentcolor == NULL && fontcolor == NULL)
				fputs(line, out);
			else
			{
				if(accentcolor != NULL)
				{
					for(i=0;i<pos_accentcolor;i++)
						fprintf(out,"%c", line[i]);
					fprintf(out,"%s;\n", "#313131");
				}
				if(fontcolor != NULL)
				{
					for(i=0;i<pos_fontcolor;i++)
						fprintf(out,"%c", line[i]);
					fprintf(out,"%s;\n", "black");
				}
			}
		}
		fclose(in);
		fclose(out);
}
