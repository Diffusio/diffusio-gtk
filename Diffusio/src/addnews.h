#ifndef ADDNEWS
#define ADDNEWS
#include <time.h>
#include "session.h"
#include "main.h"
#include "struct.h"




G_MODULE_EXPORT gboolean prepareNews (GdkEventKey *event, struct Data *data);

G_MODULE_EXPORT gboolean closeDialog (GdkEventKey *event, struct Data *data);

void addANews(struct Data *data);

int getLastNewsId(char []);

int copyFile(char [], char []);



#endif
