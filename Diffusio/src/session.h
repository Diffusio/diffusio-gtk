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


#ifndef SESSION
#define SESSION

#include <windows.h>
#include <gtk/gtk.h>
#include "main.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "addnews.h"
#include "struct.h"

#define OPEN 0
#define CANCEL 1



void load_widgets(struct Data*);
gboolean close_splash(struct Data*);

G_MODULE_EXPORT void openAboutWindow (GtkWidget*, struct Data*);

G_MODULE_EXPORT void cb_changed(GtkButton*, struct Data *);

G_MODULE_EXPORT void session_new_delete(GtkWidget*, struct Data *);

G_MODULE_EXPORT void session_open_chooser_selection_changed_cb(GtkWidget*, struct Data *);

G_MODULE_EXPORT void session_open_delete_button_clicked_cb(GtkWidget*, struct Data *);
#endif
