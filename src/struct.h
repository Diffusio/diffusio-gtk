#ifndef STRUCT
#define STRUCT
#include "jsmn.h"

struct NewContent
{
        GtkWidget *title;
        GtkWidget *content;
        GtkWidget *summary;

        GtkWidget *dialog;
};


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


struct SessionData
{
    GtkWidget *SessionWindow;

    GtkEntry *name_entry;

    GtkWidget *new_button;
    GtkWidget *newtab_delete_button;
    GtkWidget *opentab_delete_button;
    GtkWidget *opentab_open_button;

    GtkFileChooser *new_chooser;
    GtkFileChooser *open_chooser;

    GtkLabel *folder_label;

    GtkWidget *about;
    GtkWidget *dialog_fexists;

    GtkWidget *splash_window;

};

struct MainData
{
    GtkWidget *MainWindow;
    GtkWidget *errdial;
    GtkWidget *quit;
    GtkWidget *addnew_button;
    GtkLabel *current_template;

    GtkWidget *template_button[4];

    /*GtkEntry *title[3];
    GtkFileChooser *logo[3];        Ne fonctionne pas
    GtkTextView *content[3];*/
    GtkEntry *site_title;
    GtkEntry *title1;
    GtkEntry *title2;
    GtkEntry *title3;
    GtkFileChooser *logo1;
    GtkFileChooser *logo2;
    GtkFileChooser *logo3;
    GtkTextView *content1;
    GtkTextView *content2;
    GtkTextView *content3;

    GtkEntry *address;
    GtkEntry *mail;
    GtkEntry *fbname;
    GtkEntry *fblink;
    GtkEntry *twname;
    GtkEntry *twlink;
    GtkEntry *gpname;
    GtkEntry *gplink;

    char index_path[50];  //index_var.html
    char res_path[50];  //index.html

    FILE* index;
    FILE *res;

    GtkButton *render;

};

struct Infos
{
    gchar *site_title;
    /*char *title[3];
    char *logo[3];                     Idem
    char *content[3];*/
    char *title1;
    char *title2;
    char *title3;
    char *logo1;
    char *logo2;
    char *logo3;
    char *content1;
    char *content2;
    char *content3;
    char *address;
    char *mail;
    char *fbname;
    char *fblink;
    char *twname;
    char *twlink;
    char *gpname;
    char *gplink;

};

struct Data
{
    GtkBuilder *builder;
    GtkTextBuffer *buffer;
    struct SessionData sessiondata;
    struct MainData maindata;
    struct NewContent new_content;
    struct News news;
    struct Infos infos;
    FILE *save;

    gchar template_selected[10];
    gchar template_path[29];
    gchar *savefile_path;

    jsmn_parser p;

};


#endif
