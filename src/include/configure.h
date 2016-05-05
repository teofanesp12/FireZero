/*******************************************************************************\
 * configure.h -- Using GUI.                                                   *
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

#ifndef CONFIG_H
#define CONFIG_H

/*
#ifndef DEBUG
#define DEBUG
#endif
*/
#ifndef LOCAL_SHARE
#define LOCAL_SHARE ".local/share/FireZero"
#endif
volatile struct {
   char* Host;
   char* Port;
   char* Login;
   char* PassWord;
} DBConf;

#endif // CONFIG_H
