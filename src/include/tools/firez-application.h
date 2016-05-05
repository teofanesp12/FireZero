/*******************************************************************************\
 * firez-application.h -- App Conf File.                                       *
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

#ifndef _FIREZ_APPLICATION_H_
#define _FIREZ_APPLICATION_H_

#include <gtk/gtk.h>


G_BEGIN_DECLS

#define FIREZ_TYPE_APPLICATION               (firez_application_get_type ())
#define FIREZ_APPLICATION(obj)               (G_TYPE_CHECK_INSTANCE_CAST ((obj), FIREZ_TYPE_APPLICATION, FirezApplication))
#define FIREZ_APPLICATION_CLASS(klass)       (G_TYPE_CHECK_CLASS_CAST ((klass), FIREZ_TYPE_APPLICATION, FirezApplicationClass))
#define FIREZ_IS_APPLICATION(obj)            (G_TYPE_CHECK_INSTANCE_TYPE ((obj), FIREZ_TYPE_APPLICATION))
#define FIREZ_IS_APPLICATION_CLASS(klass)    (G_TYPE_CHECK_CLASS_TYPE ((klass), FIREZ_TYPE_APPLICATION))
#define FIREZ_APPLICATION_GET_CLASS(obj)     (G_TYPE_INSTANCE_GET_CLASS ((obj), FIREZ_TYPE_APPLICATION, FirezApplicationClass))

typedef struct _FirezApplicationClass         FirezApplicationClass;
typedef struct _FirezApplication              FirezApplication;
typedef struct _FirezApplicationPrivate       FirezApplicationPrivate;

struct _FirezApplication
{
  GtkApplication parent;

  /*< private >*/
  FirezApplicationPrivate *priv;
};

struct _FirezApplicationClass
{
  GtkApplicationClass parent_class;
};


GType             firez_application_get_type     (void) G_GNUC_CONST;
FirezApplication* firez_application_new          (void);
//FirezManager*      firez_application_get_manager  (FirezApp *app);
//GSettings*        firez_application_get_settings (FirezApplication *app);
void              firez_application_set_uuid     (FirezApplication       *application,
                                                 const gchar     *uuid);
void              firez_application_set_configdb (FirezApplication       *application,
                                                  const gboolean configdb);
//void              firez_application_set_initial_date (FirezApp *application,
//                                                     const icaltimetype *date);

G_END_DECLS

#endif /*_FIREZ_APPLICATION_H_*/
