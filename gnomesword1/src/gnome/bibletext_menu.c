/*
 * GnomeSword Bible Study Tool
 * bibletext_menu.c - menu for Bible texts windows
 *
 * Copyright (C) 2000,2001,2002,2003 GnomeSword Developer Team
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <gnome.h>

#include "gui/bibletext.h"
#include "gui/bibletext_menu.h"
#include "gui/gnomesword.h"
#include "gui/gtkhtml_display.h"
#include "gui/bibletext_dialog.h"
#include "gui/commentary_dialog.h"
#include "gui/shortcutbar_main.h"
#include "gui/shortcutbar_viewer.h"
#include "gui/cipher_key_dialog.h"
#include "gui/html.h"
#include "gui/dialog.h"
#include "gui/font_dialog.h"
#include "gui/main_window.h"
#include "gui/percomm.h"
#include "gui/dictlex.h"
#include "gui/shortcutbar_main.h"
#include "gui/shortcutbar_viewer.h"

#include "main/bibletext.h"
#include "main/settings.h"
#include "main/lists.h"
#include "main/sword.h"


/******************************************************************************
 * Name
 *  on_copy_activate
 *
 * Synopsis
 *   #include "gui/bibletext.h"
 *
 *   void on_copy_activate(GtkMenuItem * menuitem, TEXT_DATA * t)	
 *
 * Description
 *   copy selected text to clipboard
 *
 * Return value
 *   void
 */

static void on_copy_activate(GtkMenuItem * menuitem, TEXT_DATA * t)
{
	gui_copy_html(t->html);
}

/******************************************************************************
 * Name
 *  on_print_activate
 *
 * Synopsis
 *   #include "gui/bibletext.h"
 *
 *   void on_print_activate(GtkMenuItem * menuitem, TEXT_DATA * t)	
 *
 * Description
 *   send contents of Bible pane (window) to the printer
 *
 * Return value
 *   void
 */

static void on_print_activate(GtkMenuItem * menuitem, TEXT_DATA * t)
{
	gui_html_print(t->html);
}


/******************************************************************************
 * Name
 *  on_find_activate
 *
 * Synopsis
 *   #include "gui/bibletext.h"
 *
 *  void on_find_activate(GtkMenuItem * menuitem, TEXT_DATA * t)	
 *
 * Description
 *   opens find dialog
 *
 * Return value
 *   
 */

static void on_find_activate(GtkMenuItem * menuitem, TEXT_DATA * t)
{
	//searchGS_FIND_DLG(c, FALSE, NULL);
}

/******************************************************************************
 * Name
 *  on_lookup_selection_activate
 *
 * Synopsis
 *   #include "gui/bibletext.h"
 *   void on_lookup_selection_activate(GtkMenuItem * menuitem,
 *				  gchar * modDescription)   	
 *
 * Description
 *   lookup seledtion in a dict/lex module
 *
 * Return value
 *   void
 */

static void on_lookup_selection_activate(GtkMenuItem * menuitem,
					 gchar * dict_mod_description)
{
	gchar *dict_key, mod_name[16];

	memset(mod_name, 0, 16);
	module_name_from_description(mod_name, dict_mod_description);

	dict_key = gui_get_word_or_selection(cur_t->html, FALSE);
	if (dict_key) {
		if (settings.inViewer)
			gui_display_dictlex_in_viewer(mod_name,
						      dict_key);
		if (settings.inDictpane)
			gui_change_module_and_key(mod_name, dict_key);
		g_free(dict_key);
	}
}

/******************************************************************************
 * Name
 *  on_same_lookup_selection_activate				       
 *
 * Synopsis
 *  #include "gui/bibletext.h"
 *
 *  void on_same_lookup_selection_activate(GtkMenuItem * menuitem,
 *                                         TEXT_DATA * t) 	
 *
 * Description
 *   lookup seledtion in current dict/lex module
 *
 * Return value
 *   void
 */ 

static void on_same_lookup_selection_activate(GtkMenuItem * menuitem,
					      TEXT_DATA * t)
{
	gchar *dict_key = gui_get_word_or_selection(t->html, FALSE);
	if (dict_key) {
		if (settings.inViewer)
			gui_display_dictlex_in_viewer(settings.
						      DictWindowModule,
						      dict_key);
		if (settings.inDictpane)
			gui_change_module_and_key(settings.
						  DictWindowModule,
						  dict_key);
		g_free(dict_key);
	}
}

/******************************************************************************
 * Name
 *  on_view_mod_activate
 *
 * Synopsis
 *   #include "gui/bibletext.h"
 *
 *   void on_view_mod_activate(GtkMenuItem * menuitem, gpointer user_data)	
 *
 * Description
 *   show a different text module by changing the notebook page
 *
 * Return value
 *   void
 */

static void on_view_mod_activate(GtkMenuItem * menuitem,
				 gpointer user_data)
{
	gint page;

	page = GPOINTER_TO_INT(user_data);
	gtk_notebook_set_page(GTK_NOTEBOOK(widgets.notebook_text),
			      page);
}


/******************************************************************************
 * Name
 *  
 *
 * Synopsis
 *   #include "gui/bibletext.h"
 *
 *   void (GtkMenuItem * menuitem, gpointer user_data)	
 *
 * Description
 *   
 *
 * Return value
 *   void
 */ 

static void edit_percomm(GtkMenuItem * menuitem, gpointer user_data)
{
	if(settings.use_percomm_dialog)
		gui_open_commentary_editor((gchar *) user_data);
	else {
		gtk_notebook_set_page(GTK_NOTEBOOK(
			widgets.workbook_lower),settings.percomm_page);
		gui_set_percomm_page((gchar *) user_data);		
	}
}

/******************************************************************************
 * Name
 *  on_text_showtabs_activate
 *
 * Synopsis
 *   #include "gui/bibletext.h"
 *
 *  void on_text_showtabs_activate(GtkMenuItem * menuitem, gpointer user_data)	
 *
 * Description
 *   display text module notebook tabs
 *
 * Return value
 *   void
 */

static void on_text_showtabs_activate(GtkMenuItem * menuitem,
				      gpointer user_data)
{
	settings.text_tabs = GTK_CHECK_MENU_ITEM(menuitem)->active;
	gtk_notebook_set_show_tabs(GTK_NOTEBOOK(widgets.notebook_text),
				   settings.text_tabs);
	gui_set_text_frame_label();
}


/******************************************************************************
 * Name
 *  on_view_new_activate
 *
 * Synopsis
 *   #include "gui/bibletext.h"
 *
 *  void on_view_new_activate(GtkMenuItem * menuitem, TEXT_DATA * t)	
 *
 * Description
 *   opens view text dialog
 *
 * Return value
 *   void
 */

static void on_view_new_activate(GtkMenuItem * menuitem, TEXT_DATA * t)
{
	gui_open_bibletext_dialog(t->mod_name);
}

/******************************************************************************
 * Name
 *  gui_unlock_bibletext
 *
 * Synopsis
 *   #include "gui/bibletext.h"
 *
 *  void gui_unlock_bibletext(GtkMenuItem * menuitem,TEXT_DATA * t) 	
 *
 * Description
 *   opens add cipher key dialog
 *
 * Return value
 *   void
 */

void gui_unlock_bibletext(GtkMenuItem * menuitem, TEXT_DATA * t)
{
	gchar *cipher_key;

	cipher_key = gui_add_cipher_key(t->mod_name, t->cipher_old);
	if (cipher_key) {
		t->cipher_key = cipher_key;
		cur_t = t;
		gui_module_is_locked_display(t->html,
					     t->mod_name,
					     t->cipher_key);
	}
}


/******************************************************************************
 * Name
 *  set_module_font_activate
 *
 * Synopsis
 *   #include "gui/bibletext.h"
 *
 *   void set_module_font_activate(GtkMenuItem * menuitem,
				     TEXT_DATA * t)
 *
 * Description
 *   
 *
 * Return value
 *   void
 */

static void set_module_font_activate(GtkMenuItem * menuitem,
				     TEXT_DATA * t)
{
	gui_set_module_font(t->mod_name);
}


/******************************************************************************
 * Name
 *  global_option_red_words
 *
 * Synopsis
 *   #include "gui/bibletext.h"
 *
 *   void global_option_red_words(GtkMenuItem * menuitem,
				      TEXT_DATA * t)
 *
 * Description
 *   
 *
 * Return value
 *   void
 */

static void global_option_red_words(GtkMenuItem * menuitem,
				      TEXT_DATA * t)
{
	t->tgs->words_in_red = GTK_CHECK_MENU_ITEM(menuitem)->active;
	chapter_display(t->html, t->mod_name,
		     t->tgs, t->key,
		     TRUE);
}


/******************************************************************************
 * Name
 *  global_option_strongs
 *
 * Synopsis
 *   #include "gui/bibletext.h"
 *
 *   void global_option_strongs(GtkMenuItem * menuitem,
				      TEXT_DATA * t)
 *
 * Description
 *   
 *
 * Return value
 *   void
 */

static void global_option_strongs(GtkMenuItem * menuitem,
				      TEXT_DATA * t)
{
	t->tgs->strongs = GTK_CHECK_MENU_ITEM(menuitem)->active;
	chapter_display(t->html, t->mod_name,
		     t->tgs, t->key,
		     TRUE);
}


/******************************************************************************
 * Name
 *  global_option_morph
 *
 * Synopsis
 *   #include "gui/bibletext.h"
 *
 *   void global_option_morph(GtkMenuItem * menuitem,
				      TEXT_DATA * t)
 *
 * Description
 *   
 *
 * Return value
 *   void
 */

static void global_option_morph(GtkMenuItem * menuitem,
				      TEXT_DATA * t)
{
	t->tgs->morphs = GTK_CHECK_MENU_ITEM(menuitem)->active;
	chapter_display(t->html, t->mod_name,
		     t->tgs, t->key,
		     TRUE);
}


/******************************************************************************
 * Name
 *  global_option_footnotes
 *
 * Synopsis
 *   #include "gui/bibletext.h"
 *
 *   void global_option_footnotes(GtkMenuItem * menuitem,
				      TEXT_DATA * t)
 *
 * Description
 *   
 *
 * Return value
 *   void
 */

static void global_option_footnotes(GtkMenuItem * menuitem,
				      TEXT_DATA * t)
{
	t->tgs->footnotes = GTK_CHECK_MENU_ITEM(menuitem)->active;
	chapter_display(t->html, t->mod_name,
		     t->tgs, t->key,
		     TRUE);
}

/******************************************************************************
 * Name
 *  global_option_greekaccents
 *
 * Synopsis
 *   #include "gui/bibletext.h"
 *
 *   void global_option_greekaccents(GtkMenuItem * menuitem,
				      TEXT_DATA * t)
 *
 * Description
 *   
 *
 * Return value
 *   void
 */

static void global_option_greekaccents(GtkMenuItem * menuitem,
				      TEXT_DATA * t)
{
	t->tgs->greekaccents = GTK_CHECK_MENU_ITEM(menuitem)->active;
	chapter_display(t->html, t->mod_name,
		     t->tgs, t->key,
		     TRUE);
}


/******************************************************************************
 * Name
 *  global_option_lemmas
 *
 * Synopsis
 *   #include "gui/bibletext.h"
 *
 *   void global_option_lemmas(GtkMenuItem * menuitem,
				      TEXT_DATA * t)
 *
 * Description
 *   
 *
 * Return value
 *   void
 */

static void global_option_lemmas(GtkMenuItem * menuitem,
				      TEXT_DATA * t)
{
	t->tgs->lemmas = GTK_CHECK_MENU_ITEM(menuitem)->active;
	chapter_display(t->html, t->mod_name,
		     t->tgs, t->key,
		     TRUE);
}


/******************************************************************************
 * Name
 *  global_option_scripturerefs
 *
 * Synopsis
 *   #include "gui/bibletext.h"
 *
 *   void global_option_scripturerefs(GtkMenuItem * menuitem,
				      TEXT_DATA * t)
 *
 * Description
 *   
 *
 * Return value
 *   void
 */

static void global_option_scripturerefs(GtkMenuItem * menuitem,
				      TEXT_DATA * t)
{
	t->tgs->scripturerefs = GTK_CHECK_MENU_ITEM(menuitem)->active;
	chapter_display(t->html, t->mod_name,
		     t->tgs, t->key,
		     TRUE);
}


/******************************************************************************
 * Name
 *  global_option_hebrewpoints
 *
 * Synopsis
 *   #include "gui/bibletext.h"
 *
 *   void global_option_hebrewpoints(GtkMenuItem * menuitem,
				      TEXT_DATA * t)
 *
 * Description
 *   
 *
 * Return value
 *   void
 */

static void global_option_hebrewpoints(GtkMenuItem * menuitem,
				      TEXT_DATA * t)
{
	t->tgs->hebrewpoints = GTK_CHECK_MENU_ITEM(menuitem)->active;
	chapter_display(t->html, t->mod_name,
		     t->tgs, t->key,
		     TRUE);
}


/******************************************************************************
 * Name
 *  global_option_hebrewcant
 *
 * Synopsis
 *   #include "gui/bibletext.h"
 *
 *   void global_option_hebrewcant(GtkMenuItem * menuitem,
				      TEXT_DATA * t)
 *
 * Description
 *   
 *
 * Return value
 *   void
 */

static void global_option_hebrewcant(GtkMenuItem * menuitem,
				      TEXT_DATA * t)
{
	t->tgs->hebrewcant = GTK_CHECK_MENU_ITEM(menuitem)->active;
	chapter_display(t->html, t->mod_name,
		     t->tgs, t->key,
		     TRUE);
}


/******************************************************************************
 * Name
 *  global_option_headings
 *
 * Synopsis
 *   #include "gui/bibletext.h"
 *
 *   void global_option_headings(GtkMenuItem * menuitem,
				      TEXT_DATA * t)
 *
 * Description
 *   
 *
 * Return value
 *   void
 */

static void global_option_headings(GtkMenuItem * menuitem,
				      TEXT_DATA * t)
{
	t->tgs->headings = GTK_CHECK_MENU_ITEM(menuitem)->active;
	chapter_display(t->html, t->mod_name,
		     t->tgs, t->key,
		     TRUE);
}



/******************************************************************************
 * Name
 *  global_option_variants_all
 *
 * Synopsis
 *   #include "gui/bibletext.h"
 *
 *   void global_option_variants_all(GtkMenuItem * menuitem,
				      TEXT_DATA * t)
 *
 * Description
 *   
 *
 * Return value
 *   void
 */

static void global_option_variants_all(GtkMenuItem * menuitem,
				      TEXT_DATA * t)
{
	t->tgs->variants_all = GTK_CHECK_MENU_ITEM(menuitem)->active;
	if(t->tgs->variants_all)
		chapter_display(t->html, t->mod_name,
		     	t->tgs, t->key,
		    	TRUE);
}


/******************************************************************************
 * Name
 *  global_option_variants_primary
 *
 * Synopsis
 *   #include "gui/bibletext.h"
 *
 *   void global_option_variants_primary(GtkMenuItem * menuitem,
				      TEXT_DATA * t)
 *
 * Description
 *   
 *
 * Return value
 *   void
 */

static void global_option_variants_primary(GtkMenuItem * menuitem,
				      TEXT_DATA * t)
{
	t->tgs->variants_primary = GTK_CHECK_MENU_ITEM(menuitem)->active;
	if(t->tgs->variants_primary)
		chapter_display(t->html, t->mod_name,
		     	t->tgs, t->key,
		     	TRUE);
}


/******************************************************************************
 * Name
 *    global_option_variants_scondary
 *
 * Synopsis
 *   #include "gui/bibletext.h"
 *
 *   void global_option_variants_scondary(GtkMenuItem * menuitem,
				      TEXT_DATA * t)
 *
 * Description
 *   
 *
 * Return value
 *   void
 */

static void global_option_variants_scondary(GtkMenuItem * menuitem,
				      TEXT_DATA * t)
{
	t->tgs->variants_secondary = GTK_CHECK_MENU_ITEM(menuitem)->active;
	if(t->tgs->variants_secondary)
		chapter_display(t->html, t->mod_name,
			     t->tgs, t->key,
			     TRUE);
}


/******************************************************************************
 * Name
 *    add_global_option_items
 *
 * Synopsis
 *   #include "gui/bibletext.h"
 *
 *   void add_global_option_items(TEXT_DATA * t)
 *
 * Description
 *   add global module options to popup menus (Bible texts)
 *
 * Return value
 *   void
 */

static void add_global_option_items(TEXT_DATA * t)
{
	GtkWidget * item;
	GtkWidget * menu;
	GSList *group = NULL;	
	
	if(check_for_global_option(t->mod_name, "GBFRedLetterWords")) {
		t->tgs->words_in_red = 
			load_module_options(t->mod_name, "Red letter words");
		
		item =
		    gtk_check_menu_item_new_with_label(_("Red letter words"));
		gtk_widget_show(item);
		gtk_container_add(GTK_CONTAINER(t->module_options_menu), item);
			
		GTK_CHECK_MENU_ITEM(item)->active = t->tgs->words_in_red;
		gtk_signal_connect(GTK_OBJECT(item), "toggled",
				   GTK_SIGNAL_FUNC
				   (global_option_red_words),
				   t);
	}
	
	if((check_for_global_option(t->mod_name, "GBFStrongs")) ||
		(check_for_global_option(t->mod_name, "ThMLStrongs")) ||
		(check_for_global_option(t->mod_name, "OSISStrongs"))) {
		t->tgs->strongs = 
			load_module_options(t->mod_name, "Strong's Numbers");
		
		item =
		    gtk_check_menu_item_new_with_label(_("Strong's Numbers"));
		gtk_widget_show(item);
		gtk_container_add(GTK_CONTAINER(t->module_options_menu), item);
			
		GTK_CHECK_MENU_ITEM(item)->active = t->tgs->strongs;
		gtk_signal_connect(GTK_OBJECT(item), "toggled",
				   GTK_SIGNAL_FUNC
				   (global_option_strongs),
				   t);
	}
	
	if((check_for_global_option(t->mod_name, "GBFMorph")) ||
		(check_for_global_option(t->mod_name, "ThMLMorph")) ||
		(check_for_global_option(t->mod_name, "OSISSMorph"))) {
		t->tgs->morphs = 
			load_module_options(t->mod_name, "Morphological Tags");
		
		item =
		    gtk_check_menu_item_new_with_label(_("Morphological Tags"));
		gtk_widget_show(item);
		gtk_container_add(GTK_CONTAINER(t->module_options_menu), item);
			
		GTK_CHECK_MENU_ITEM(item)->active = t->tgs->morphs;
		gtk_signal_connect(GTK_OBJECT(item), "toggled",
				   GTK_SIGNAL_FUNC
				   (global_option_morph),
				   t);
	}
	
	if((check_for_global_option(t->mod_name, "GBFFootnotes")) ||
		(check_for_global_option(t->mod_name, "ThMLFootnotes"))) {
		t->tgs->footnotes = 
			load_module_options(t->mod_name, "Footnotes");
		
		item =
		    gtk_check_menu_item_new_with_label(_("Footnotes"));
		gtk_widget_show(item);
		gtk_container_add(GTK_CONTAINER(t->module_options_menu), item);
			
		GTK_CHECK_MENU_ITEM(item)->active = t->tgs->footnotes;
		gtk_signal_connect(GTK_OBJECT(item), "toggled",
				   GTK_SIGNAL_FUNC
				   (global_option_footnotes),
				   t);
	}
	
	if(check_for_global_option(t->mod_name, "UTF8GreekAccents")) {
		t->tgs->greekaccents = 
			load_module_options(t->mod_name, "Greek Accents");
		
		item =
		    gtk_check_menu_item_new_with_label(_("Greek Accents"));
		gtk_widget_show(item);
		gtk_container_add(GTK_CONTAINER(t->module_options_menu), item);
			
		GTK_CHECK_MENU_ITEM(item)->active = t->tgs->greekaccents;
		gtk_signal_connect(GTK_OBJECT(item), "toggled",
				   GTK_SIGNAL_FUNC
				   (global_option_greekaccents),
				   t);
	}
	
	if(check_for_global_option(t->mod_name, "ThMLLemma")) {
		t->tgs->lemmas = 
			load_module_options(t->mod_name, "Lemmas");
		
		item =
		    gtk_check_menu_item_new_with_label(_("Lemmas"));
		gtk_widget_show(item);
		gtk_container_add(GTK_CONTAINER(t->module_options_menu), item);
			
		GTK_CHECK_MENU_ITEM(item)->active = t->tgs->lemmas;
		gtk_signal_connect(GTK_OBJECT(item), "toggled",
				   GTK_SIGNAL_FUNC
				   (global_option_lemmas),
				   t);
	}
	
	if(check_for_global_option(t->mod_name, "ThMLScripref")) {
		t->tgs->scripturerefs = 
			load_module_options(t->mod_name, "Scripture Cross-references");
		
		item =
		    gtk_check_menu_item_new_with_label(_("Scripture Cross-references"));
		gtk_widget_show(item);
		gtk_container_add(GTK_CONTAINER(t->module_options_menu), item);
			
		GTK_CHECK_MENU_ITEM(item)->active = t->tgs->scripturerefs;
		gtk_signal_connect(GTK_OBJECT(item), "toggled",
				   GTK_SIGNAL_FUNC
				   (global_option_scripturerefs),
				   t);
	}
	
	if(check_for_global_option(t->mod_name, "UTF8HebrewPoints")) {
		t->tgs->hebrewpoints = 
			load_module_options(t->mod_name, "Hebrew Vowel Points");
		
		item =
		    gtk_check_menu_item_new_with_label(_("Hebrew Vowel Points"));
		gtk_widget_show(item);
		gtk_container_add(GTK_CONTAINER(t->module_options_menu), item);
			
		GTK_CHECK_MENU_ITEM(item)->active = t->tgs->hebrewpoints;
		gtk_signal_connect(GTK_OBJECT(item), "toggled",
				   GTK_SIGNAL_FUNC
				   (global_option_hebrewpoints),
				   t);
	}
	
	if(check_for_global_option(t->mod_name, "UTF8Cantillation")) {
		t->tgs->hebrewcant = 
			load_module_options(t->mod_name, "Hebrew Cantillation");
		
		item =
		    gtk_check_menu_item_new_with_label(_("Hebrew Cantillation"));
		gtk_widget_show(item);
		gtk_container_add(GTK_CONTAINER(t->module_options_menu), item);
			
		GTK_CHECK_MENU_ITEM(item)->active = t->tgs->hebrewcant;
		gtk_signal_connect(GTK_OBJECT(item), "toggled",
				   GTK_SIGNAL_FUNC
				   (global_option_hebrewcant),
				   t);
	}
	
	if(check_for_global_option(t->mod_name, "ThMLHeadings")) {
		t->tgs->headings = 
			load_module_options(t->mod_name, "Headings");
		
		item =
		    gtk_check_menu_item_new_with_label(_("Headings"));
		gtk_widget_show(item);
		gtk_container_add(GTK_CONTAINER(t->module_options_menu), item);
			
		GTK_CHECK_MENU_ITEM(item)->active = t->tgs->headings;
		gtk_signal_connect(GTK_OBJECT(item), "toggled",
				   GTK_SIGNAL_FUNC
				   (global_option_headings),
				   t);
	}
	
	if(check_for_global_option(t->mod_name, "ThMLVariants")) {
		t->tgs->variants_all = 
			load_module_options(t->mod_name, "All Readings");
		t->tgs->variants_primary = 
			load_module_options(t->mod_name, "Primary Reading");
		t->tgs->variants_secondary = 
			load_module_options(t->mod_name, "Secondary Reading");
		item =
		    gtk_menu_item_new_with_label(_("Variants"));
		gtk_container_add(GTK_CONTAINER(t->module_options_menu), item);
		gtk_widget_show(item);
		
		menu = gtk_menu_new();
		gtk_menu_item_set_submenu(GTK_MENU_ITEM(item),
				  menu);
		
		item = gtk_radio_menu_item_new_with_label (group, _("All Readings"));
  		group = gtk_radio_menu_item_group (GTK_RADIO_MENU_ITEM (item));
		gtk_widget_show(item);
		gtk_container_add(GTK_CONTAINER(menu), item);
		if(t->tgs->variants_all)		   
			gtk_check_menu_item_set_active (
				GTK_CHECK_MENU_ITEM (item), 
					t->tgs->variants_all); 
		gtk_signal_connect(GTK_OBJECT(item), "toggled",
				   GTK_SIGNAL_FUNC
				   (global_option_variants_all),
				   t);
				   
		item = gtk_radio_menu_item_new_with_label (group, _("Primary Readings"));
  		group = gtk_radio_menu_item_group (GTK_RADIO_MENU_ITEM (item));
		gtk_widget_show(item);
		gtk_container_add(GTK_CONTAINER(menu), item);
		if(t->tgs->variants_primary)		   
			gtk_check_menu_item_set_active (
				GTK_CHECK_MENU_ITEM (item), 
					t->tgs->variants_primary);  
		gtk_signal_connect(GTK_OBJECT(item), "toggled",
				   GTK_SIGNAL_FUNC
				   (global_option_variants_primary),
				   t);
		
		item = gtk_radio_menu_item_new_with_label (group, _("Secondary Readings"));
  		group = gtk_radio_menu_item_group (GTK_RADIO_MENU_ITEM (item));
		gtk_widget_show(item);
		gtk_container_add(GTK_CONTAINER(menu), item);
		gtk_signal_connect(GTK_OBJECT(item), "toggled",
				   GTK_SIGNAL_FUNC
				   (global_option_variants_scondary),
				   t);	
		if(t->tgs->variants_secondary)		   
			gtk_check_menu_item_set_active (
				GTK_CHECK_MENU_ITEM (item), 
					t->tgs->variants_secondary);   
	}
	
}


/******************************************************************************
 * Name
 *  gui_create_pm_text
 *
 * Synopsis
 *   #include "gui/bibletext.h"
 *
 *   GtkWidget *gui_create_pm_text(TEXT_DATA * t)
 *
 * Description
 *   create popup menu for text module - attached to html widget
 *
 * Return value
 *   GtkWidget*
 */

GtkWidget *gui_create_pm_text(TEXT_DATA * t)
{
	GtkWidget *pm_text;
	GtkAccelGroup *pm_text_accels;
	GtkWidget *copy;
	GtkWidget *separator;
	GtkWidget *show;
	GtkWidget *show_menu;
	GtkWidget *module_options;
	GtkWidget *print;
	GtkWidget *edit;
	GtkWidget *edit_menu;
	GtkWidget *edit_note;
	GtkWidget *edit_note_menu = NULL;
	GtkAccelGroup *edit_note_menu_accels;
	GtkWidget *lookup_selection;
	GtkWidget *lookup_selection_menu;
	GtkAccelGroup *lookup_selection_menu_accels;
	GtkWidget *usecurrent;
	GtkWidget *item3;
	GtkWidget *item4;
	GtkWidget *view_new;
	GtkWidget *view_text;
	GtkWidget *view_text_menu;
	GtkAccelGroup *view_text_menu_accels;
	GtkWidget *set_font;
	GtkWidget *find;
	GtkWidget *add_module_key = NULL;
	GList *tmp;
	gchar buf[256];
	gint i=0;
	GtkTooltips *tooltips;

	tmp = NULL;
	sprintf(buf,"%s %s",t->mod_name, _("in a new window"));
	
	tooltips = gtk_tooltips_new();

	pm_text = gtk_menu_new();
	gtk_object_set_data(GTK_OBJECT(pm_text), "pm_text", pm_text);
	pm_text_accels =
	    gtk_menu_ensure_uline_accel_group(GTK_MENU(pm_text));
	    
	/*
	 * show menu
	 */
	show =
	    gtk_menu_item_new_with_label(_("Show"));
	gtk_widget_show(show);
	gtk_container_add(GTK_CONTAINER(pm_text), show);

	show_menu = gtk_menu_new();
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(show),
				  show_menu);
	if(!t->is_dialog) {
		t->showtabs =
		    gtk_check_menu_item_new_with_label(_("Tabs"));
		gtk_widget_show(t->showtabs);
		gtk_container_add(GTK_CONTAINER(show_menu), t->showtabs);
		gtk_signal_connect(GTK_OBJECT(t->showtabs), "activate",
			   GTK_SIGNAL_FUNC
			   (on_text_showtabs_activate), NULL);
	}


	view_new = gtk_menu_item_new_with_label(buf);
	gtk_widget_show(view_new);
	gtk_container_add(GTK_CONTAINER(show_menu), view_new);
	
	view_text = gtk_menu_item_new_with_label(_("New Module"));
	gtk_widget_show(view_text);
	gtk_container_add(GTK_CONTAINER(show_menu), view_text);

	view_text_menu = gtk_menu_new();
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(view_text),
				  view_text_menu);
	view_text_menu_accels =
	    gtk_menu_ensure_uline_accel_group(GTK_MENU(view_text_menu));

	/*
	 * module options menu
	 */
	module_options = gtk_menu_item_new_with_label(_("Module Options"));
	gtk_widget_show(module_options);
	gtk_container_add(GTK_CONTAINER(pm_text), module_options);
	
	t->module_options_menu = gtk_menu_new();
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(module_options),
				  t->module_options_menu);

	set_font = gtk_menu_item_new_with_label(_("Set Module Font"));
	gtk_widget_show(set_font);
	gtk_container_add(GTK_CONTAINER(t->module_options_menu), set_font);
	gtk_tooltips_set_tip(tooltips, set_font,
			     _("Set font for this module"), NULL);
			     
	separator = gtk_menu_item_new();
	gtk_widget_show(separator);
	gtk_container_add(GTK_CONTAINER(t->module_options_menu), separator);
	gtk_widget_set_sensitive(separator, FALSE);
	
	add_global_option_items(t);
	
	/*
	 * edit menu
	 */
	edit =
	    gtk_menu_item_new_with_label(_("Edit"));
	gtk_widget_show(edit);
	gtk_container_add(GTK_CONTAINER(pm_text), edit);

	edit_menu = gtk_menu_new();
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(edit),
				  edit_menu);
	
	copy = gtk_menu_item_new_with_label(_("Copy"));
	gtk_widget_show(copy);
	gtk_container_add(GTK_CONTAINER(edit_menu), copy);

	find = gtk_menu_item_new_with_label(_("Find"));
	gtk_widget_show(find);
	gtk_container_add(GTK_CONTAINER(edit_menu), find);
	
	print = gtk_menu_item_new_with_label(_("Print"));
	gtk_widget_show(print);
	gtk_container_add(GTK_CONTAINER(edit_menu), print);	


	if (settings.havepercomm && (!t->is_dialog)) {
		edit_note =
		    gtk_menu_item_new_with_label(_("Note"));
		gtk_widget_show(edit_note);
		gtk_container_add(GTK_CONTAINER(edit_menu), edit_note);

		edit_note_menu = gtk_menu_new();
		gtk_menu_item_set_submenu(GTK_MENU_ITEM(edit_note),
					  edit_note_menu);
		edit_note_menu_accels =
		    gtk_menu_ensure_uline_accel_group(GTK_MENU
						      (edit_note_menu));
	}
	
	/*
	 * lookup menu
	 */
	lookup_selection =
	    gtk_menu_item_new_with_label(_("Lookup Selection"));
	gtk_widget_show(lookup_selection);
	gtk_container_add(GTK_CONTAINER(pm_text), lookup_selection);

	lookup_selection_menu = gtk_menu_new();
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(lookup_selection),
				  lookup_selection_menu);
	lookup_selection_menu_accels =
	    gtk_menu_ensure_uline_accel_group(GTK_MENU
					      (lookup_selection_menu));

	usecurrent =
	    gtk_menu_item_new_with_label("Use Current Dictionary");
	gtk_widget_show(usecurrent);
	gtk_container_add(GTK_CONTAINER(lookup_selection_menu),
			  usecurrent);
			     
	separator = gtk_menu_item_new();
	gtk_widget_show(separator);
	gtk_container_add(GTK_CONTAINER(lookup_selection_menu), separator);
	gtk_widget_set_sensitive(separator, FALSE);

	/*
	 * if module has cipher key include this item
	 */
	if (t->cipher_old || t->is_locked) {
		separator = gtk_menu_item_new();
		gtk_widget_show(separator);
		gtk_container_add(GTK_CONTAINER(pm_text), separator);
		gtk_widget_set_sensitive(separator, FALSE);

		add_module_key =
		    gtk_menu_item_new_with_label(_
						 ("Unlock This Module"));
		gtk_widget_show(add_module_key);
		gtk_container_add(GTK_CONTAINER(pm_text),
				  add_module_key);

		gtk_signal_connect(GTK_OBJECT(add_module_key),
				   "activate",
				   GTK_SIGNAL_FUNC
				   (gui_unlock_bibletext), t);
	}

	tmp = get_list(DICT_DESC_LIST);
	while (tmp != NULL) {
		item4 =
		    gtk_menu_item_new_with_label((gchar *) tmp->data);
		gtk_widget_show(item4);
		gtk_signal_connect(GTK_OBJECT(item4), "activate",
				   GTK_SIGNAL_FUNC
				   (on_lookup_selection_activate),
				   (gchar *) tmp->data);
		
		gtk_container_add(GTK_CONTAINER
				  (lookup_selection_menu), item4);
		tmp = g_list_next(tmp);
	}
	g_list_free(tmp);

	tmp = NULL;
	i = 0;
	tmp = get_list(TEXT_DESC_LIST);
	while (tmp != NULL) {
		item3 =
		    gtk_menu_item_new_with_label((gchar *) tmp->data);
		gtk_widget_show(item3);
		gtk_signal_connect(GTK_OBJECT(item3), "activate",
				   GTK_SIGNAL_FUNC
				   (on_view_mod_activate),
				   GINT_TO_POINTER(i));
		gtk_container_add(GTK_CONTAINER(view_text_menu), item3);
		++i;
		tmp = g_list_next(tmp);
	}
	g_list_free(tmp);

	tmp = NULL;
	if (settings.havepercomm && (!t->is_dialog)) {
		i = 0;
		tmp = get_list(PERCOMM_LIST);
		while (tmp != NULL) {
			item3 =
			    gtk_menu_item_new_with_label((gchar *) tmp->
							 data);
			gtk_widget_show(item3);

			gtk_signal_connect(GTK_OBJECT(item3),
					   "activate",
					   GTK_SIGNAL_FUNC
					   (edit_percomm),
					   (gchar *) tmp->data);

			gtk_container_add(GTK_CONTAINER(edit_note_menu),
					  item3);
			++i;
			tmp = g_list_next(tmp);
		}
		g_list_free(tmp);
	}
	/*
	 * for using the current dictionary for lookup 
	 */
	gtk_signal_connect(GTK_OBJECT(usecurrent), "activate",
			   GTK_SIGNAL_FUNC
			   (on_same_lookup_selection_activate), t);

	gtk_signal_connect(GTK_OBJECT(copy), "activate",
			   GTK_SIGNAL_FUNC(on_copy_activate), t);
	gtk_signal_connect(GTK_OBJECT(print), "activate",
			   GTK_SIGNAL_FUNC(on_print_activate), t);
	gtk_signal_connect(GTK_OBJECT(find), "activate",
			   GTK_SIGNAL_FUNC(on_find_activate), t);

	gtk_signal_connect(GTK_OBJECT(view_new), "activate",
			   GTK_SIGNAL_FUNC(on_view_new_activate), t);


	gtk_signal_connect(GTK_OBJECT(set_font), "activate",
			   GTK_SIGNAL_FUNC(set_module_font_activate),
			   t);

	gtk_object_set_data(GTK_OBJECT(pm_text), "tooltips", tooltips);
	return pm_text;
}
