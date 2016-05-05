/*******************************************************************************\
 * main.c -- Using GUI.                                                        *
 * Copyright (C) 2015  Teofanes Enrique Paz Moron <teofanesp12@gmail.com>      *
 *                                                                             *
 * FireZero is free software: you can redistribute it and/or modify            *
 * it under the terms of the GNU General Public License as published by        *
 * the Free Software Foundation, either version 3 of the License, or           *
 * (at your option) any later version.                                         *
 *                                                                             *
 * This program is distributed in the hope that it will be useful,             *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the               *
 * GNU General Public License for more details.                                *
 *                                                                             *
 * You should have received a copy of the GNU General Public License           *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.       *
 *******************************************************************************/
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <module/login.h>
#include <module/managedb.h>

#include <tools/firez-application.h>

#include <gtk/gtk.h>

// Dep top i18n
#include <langinfo.h>
#include <glib/gi18n-lib.h>
#include <locale.h>


GtkWidget* window;

int
main (int   argc, char *argv[]){
    FirezApplication *app;
    int status;
//    #ifdef ENABLE_NLS
    setlocale (LC_ALL, "");
    bindtextdomain (GETTEXT_PACKAGE, LOCALE_DIR);
    bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
    textdomain (GETTEXT_PACKAGE);
//    #endif
    app = firez_application_new ();
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);
    return status;
}
