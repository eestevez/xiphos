/*
 * GnomeSword Bible Study Tool
 * interlinear_dialog.h - dialog for detached interlinear
 *
 * Copyright (C) 2000,2001,2002 GnomeSword Developer Team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */
 
#ifndef __INTERLINEAR_DIALOG_H__
#define __INTERLINEAR_DIALOG_H__

#ifdef __cplusplus
extern "C" {
#endif

void gui_undock_interlinear_page(void);
void gui_btnDockInt_clicked(GtkButton *button, gpointer user_data);
GtkWidget *gui_create_interlinear_dialog(void);

#ifdef __cplusplus
}
#endif

#endif

