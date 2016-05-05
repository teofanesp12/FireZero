/*******************************************************************************\
 * login.h -- Using GUI.                                                       *
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


#ifndef LOGIN_H
#define LOGIN_H


#include <libpq-fe.h>
#include <gtk/gtk.h>
#include <module/managedb.h>

#include <stdbool.h>

void
firez_login_new(
    GSimpleAction *action,
    GVariant      *parameter,
    gpointer       user_data
);

void
authorized_login(
    GtkDialog *dialog,
    gint       response_id,
    gpointer   user_data
);

void
authorized_login_entry(
    GtkEntry *entry,
    gpointer  user_data
);

void
Dialog_Login(
    GtkWindow *window,
    gpointer user_data
);

void
closed_login(
    GtkDialog *dialog,
    gpointer  user_data
);

int
conexao(
    void
);

void
complet_combo_db(
    GtkWidget *combo_box
);
#endif // LOGIN_H
