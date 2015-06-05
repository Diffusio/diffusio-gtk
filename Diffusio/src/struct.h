/*
 * Diffusio - Build presentation websites easily
 * https://github.com/diffusio
 * http://diffusio.co
 * 
 * Copyright (C) 2015 
 * 
 * Pierre JACQUIER  
 * http://pierre-jacquier.com
 * 
 * Grégoire DUVAUCHELLE
 * https://github.com/kalterkrieg
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 2.1 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public 
*/


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
    GtkWidget *save_dialog;
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
    GtkButton *explorer;

};

struct Infos
{
    gchar *site_title;
    /*char *title[3];
    char *logo[3];                     Idem
    char *content[3];*/
    gchar *title1;
    gchar *title2;
    gchar *title3;
    gchar *logo1;
    gchar *logo2;
    gchar *logo3;
    gchar *content1;
    gchar *content2;
    gchar *content3;
    gchar *address;
    gchar *mail;
    gchar *fbname;
    gchar *fblink;
    gchar *twname;
    gchar *twlink;
    gchar *gpname;
    gchar *gplink;

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
    gchar template_selected[20];
    gchar template_path[40];


};


#endif
