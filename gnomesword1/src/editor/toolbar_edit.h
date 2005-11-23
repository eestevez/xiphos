/*
 * GnomeSword Bible Study Tool
 * toolbar_edit.h - style toolbar for editors
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

#ifndef _TOOLBAR_EDIT_H
#define _TOOLBAR_EDIT_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifndef USE_GTKHTML38

#include "editor/editor.h"

GtkWidget *gui_toolbar_edit(GSHTMLEditorControlData *ecd);

#endif
#endif
