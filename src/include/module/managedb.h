/*******************************************************************************\
 * managedb.h -- Using GUI.                                                    *
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

#ifndef MANAGEDB_H
#define MANAGEDB_H

#include <libpq-fe.h>
#include <gtk/gtk.h>
#include <libpq-fe.h>
#include <configure.h>

void
firez_db_manage(
    GSimpleAction *action,
    GVariant      *parameter,
    gpointer       user_data
);


void
ManageDB_sidebar(
    GtkApplication *application
);


void
button_load_conf_clicked (
    GtkButton *button,
    gpointer user_data
);


/* the functions SQL */

int
connection(
    void
);

void
exit_connection(
    void
);
/*Objeto de conexão*/
volatile PGconn *conn;// = NULL;
/*Ponteiro de resultado*/
volatile PGresult *result;
volatile char* dbName;

#endif // MANAGEDB_H
