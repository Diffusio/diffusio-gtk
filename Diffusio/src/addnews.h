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
