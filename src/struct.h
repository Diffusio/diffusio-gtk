#ifndef STRUCT
#define STRUCT

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

};

struct MainData
{
    GtkWidget *MainWindow;
    GtkButton *quit;
    GtkButton *addnew_button;

};

struct Data
{
    GtkBuilder *builder;
    gpointer user_data;
    struct SessionData sessiondata;
    struct MainData maindata;
    struct NewContent new_content;
    struct News news;

};

#endif
