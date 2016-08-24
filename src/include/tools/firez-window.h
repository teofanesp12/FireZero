/*******************************************************************************\
 * firez-window.h -- Description File.                                         *
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

#ifndef _FIREZ_WINDOW_H_
#define _FIREZ_WINDOW_H_

#include <gtk/gtk.h>
#include <tools/firez-application.h>

G_BEGIN_DECLS

typedef enum
{
	FIREZ_WINDOW_STATE_NORMAL		= 0,
	FIREZ_WINDOW_STATE_SAVING		= 1 << 1,
	FIREZ_WINDOW_STATE_PRINTING		= 1 << 2,
	FIREZ_WINDOW_STATE_LOADING		= 1 << 3,
	FIREZ_WINDOW_STATE_ERROR		= 1 << 4
} FirezWindowState;

#define FIREZ_TYPE_WINDOW              (firez_window_get_type())
#define FIREZ_WINDOW(obj)              (G_TYPE_CHECK_INSTANCE_CAST((obj), FIREZ_TYPE_WINDOW, FirezWindow))
#define FIREZ_WINDOW_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST((klass), FIREZ_TYPE_WINDOW, FirezWindowClass))
#define FIREZ_IS_WINDOW(obj)           (G_TYPE_CHECK_INSTANCE_TYPE((obj), FIREZ_TYPE_WINDOW))
#define FIREZ_IS_WINDOW_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FIREZ_TYPE_WINDOW))
#define FIREZ_WINDOW_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS((obj), FIREZ_TYPE_WINDOW, FirezWindowClass))

typedef struct _FirezWindow        FirezWindow;
typedef struct _FirezWindowClass   FirezWindowClass;
typedef struct _FirezWindowPrivate FirezWindowPrivate;

struct _FirezWindow
{
	GtkApplicationWindow window;

	/*< private > */
	FirezWindowPrivate *priv;
};

struct _FirezWindowClass
{
	GtkApplicationWindowClass parent_class;

	/* Signals 
	void	 (* tab_added)      	(FirezWindow *window,
					 FirezTab    *tab);
	void	 (* tab_removed)    	(FirezWindow *window,
					 FirezTab    *tab);
	void	 (* tabs_reordered) 	(FirezWindow *window);
	void	 (* active_tab_changed)	(FirezWindow *window,
				     	 FirezTab    *tab);
	void	 (* active_tab_state_changed)
					(FirezWindow *window);
	*/
};

/* Public methods */
GType 		 firez_window_get_type 			(void) G_GNUC_CONST;
void firez_window_new(
    FirezApplication *application
);

GtkWidget*
new_window_app(
    GApplication *application
);

G_END_DECLS
#endif/* _FIREZ_WINDOW_H_ */
