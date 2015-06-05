#include <stdio.h>
#include <stdlib.h>

void displayRenderer(char template[])
{
    char start[50];
    system("SET var=%cd%");
    sprintf(start, "start QtWeb.exe %%cd%%\\res\\templates\\%s\\index.html", template);
    printf("%s",start);
    system(start);
}

int main()
{
    displayRenderer("material");
    return 0;
}
