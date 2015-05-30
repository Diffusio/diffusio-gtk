#ifndef MAIN
#define MAIN

#include <gtk/gtk.h>
#include "session.h"
#include "addnews.h"
#include "struct.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

#define MATERIAL 0
#define FLAT 1
#define SOBER 2
#define CLASSIC 3

void openMainWindow(struct Data *data);

G_MODULE_EXPORT void quit(gpointer *osef, struct Data *data);

G_MODULE_EXPORT void change_material(GtkWidget *widget, struct Data *data);
G_MODULE_EXPORT void change_flat(GtkWidget *widget, struct Data *data);
G_MODULE_EXPORT void change_sober(GtkWidget *widget, struct Data *data);
G_MODULE_EXPORT void change_classic(GtkWidget *widget, struct Data *data);

G_MODULE_EXPORT void new_session(GtkButton *button, struct Data *data);
G_MODULE_EXPORT void open_session(GtkButton *button, struct Data *data);

G_MODULE_EXPORT void open_file(GtkMenuItem *menuitem, struct Data *data);


#endif
