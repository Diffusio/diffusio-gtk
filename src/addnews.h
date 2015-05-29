#ifndef ADDNEWS
#define ADDNEWS
#include <time.h>
#include "session.h"
#include "main.h"
#include "struct.h"
#define STARTCOMMENTBOOL ligne[0] == '<' && ligne[1] == '!' && ligne[2] == '-' && ligne[3] == '-'




G_MODULE_EXPORT gboolean prepareNews (GdkEventKey *event, struct Data *data);

G_MODULE_EXPORT gboolean closeDialog (GdkEventKey *event, struct Data *data);

void addANews(struct Data *data);

int getLastNewsId(char []);

void copyFile(char [], char []);



#endif
