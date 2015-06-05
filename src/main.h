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
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define MATERIAL 0
#define FLAT 1
#define SOBER 2
#define CLASSIC 3

void openMainWindow(struct Data*);

void copy_logo(struct Data*);

void get_infos(struct Data*);
char *repl_str(const char *, const char *, const char *);

void update_html(struct Data *);
void open_error_dialog(struct Data*, const gchar *error);

G_MODULE_EXPORT void quit(gpointer*, struct Data*);

G_MODULE_EXPORT void change_template(GtkWidget*, struct Data*);
void update_template_path(struct Data*);
G_MODULE_EXPORT int update_infos(GtkWidget*, struct Data *);

G_MODULE_EXPORT void new_session(GtkButton*, struct Data*);
G_MODULE_EXPORT void open_session(GtkButton*, struct Data*);

G_MODULE_EXPORT int open_file(GtkWidget*, struct Data*);

int verif_html_comment(struct Data*);

G_MODULE_EXPORT int open_explorer(GtkButton*, struct Data*);
G_MODULE_EXPORT void save(GtkWidget*, struct Data *);

static int jsoneq(const char *, jsmntok_t *, const char *);
void update_entries(struct Data *data);

#endif
