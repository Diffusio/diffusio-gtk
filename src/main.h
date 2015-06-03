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

void openMainWindow(struct Data*);

void update_html(struct Data *);
void open_error_dialog(struct Data*, const gchar *error);

G_MODULE_EXPORT void quit(gpointer*, struct Data*);

G_MODULE_EXPORT void change_template(GtkWidget*, struct Data*);
void update_template_path(struct Data*);
G_MODULE_EXPORT int update_infos(GtkWidget*, struct Data *);

G_MODULE_EXPORT void new_session(GtkButton*, struct Data*);
G_MODULE_EXPORT void open_session(GtkButton*, struct Data*);

G_MODULE_EXPORT void open_file(GtkMenuItem*, struct Data*);


#endif
