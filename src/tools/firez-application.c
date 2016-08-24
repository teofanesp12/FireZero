/*******************************************************************************\
 * firez-application.c -- App config.                                          *
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

#include <tools/firez-application.h>
#include <tools/firez-window.h>

//Modules:
#include <module/login.h>
#include <module/managedb.h>

#include <glib.h>
#include <glib-object.h>
#include <gio/gio.h>
#include <glib/gi18n.h>

#define FireZero_Service "fire.zero.org"

struct _FirezApplicationPrivate
{
    GtkWidget      *window;

    //GSettings      *settings;

    gboolean        debug;
    gboolean        configdb;
    gchar          *uuid;
    //icaltimetype   *initial_date;
};

static void     firez_application_finalize             (GObject                 *object);
static void     firez_application_activate             (GApplication            *app);
static void     firez_application_startup              (GApplication            *app);
static void     firez_application_set_app_menu         (GApplication            *app);
static gint     firez_application_command_line         (GApplication            *app,
                                                        GApplicationCommandLine *command_line);
static void     firez_application_show_about           (GSimpleAction           *simple,
                                                       GVariant                *parameter,
                                                       gpointer                 user_data);
static void     firez_application_quit                 (GSimpleAction           *simple,
                                                       GVariant                *parameter,
                                                       gpointer                 user_data);

G_DEFINE_TYPE_WITH_PRIVATE (FirezApplication, firez_application, GTK_TYPE_APPLICATION);

static gboolean show_version = FALSE;
static gboolean show_configdb = FALSE;
static gchar* date = NULL;
static gchar* uuid = NULL;

static GOptionEntry firez_application_goptions[] = {
    {
        "version", 'v', 0,
        G_OPTION_ARG_NONE, &show_version,
        N_("Display version number"), NULL
    },
    {
        "date", 'd', 0,
        G_OPTION_ARG_STRING, &date,
        N_("Open FIREZERO on the passed date"), NULL
    },
    {
        "uuid", 'u', 0,
        G_OPTION_ARG_STRING, &uuid,
        N_("Open FIREZERO showing the passed event"), NULL
    },
    {
        "configure", 'c', 0,
        G_OPTION_ARG_NONE, &show_configdb,
        N_("Open FIREZERO showing the configure data base"), NULL
    },
    { NULL }
};

static const GActionEntry firez_app_entries[] = {
  { "login",      firez_login_new },// module/login.h
  { "managedb",   firez_db_manage },// module/managedb.h
  { "about",      firez_application_show_about },
  { "quit",       firez_application_quit },
};



static void
firez_application_class_init (FirezApplicationClass *klass)
{
    GObjectClass *object_class;
    GApplicationClass *application_class;

    object_class = G_OBJECT_CLASS (klass);
    object_class->finalize = firez_application_finalize;

    application_class = G_APPLICATION_CLASS (klass);
    application_class->activate     = firez_application_activate;
    application_class->startup      = firez_application_startup;
    application_class->command_line = firez_application_command_line;

    //application_class->dbus_register = firez_application_dbus_register;
    //application_class->dbus_unregister = firez_application_dbus_unregister;
}

static void
firez_application_init (FirezApplication *self){
    FirezApplicationPrivate *priv = firez_application_get_instance_private (self);

    //priv->settings = g_settings_new ("fire.zero.org");

    self->priv = priv;
}

static void
firez_application_finalize (GObject *object){
    FirezApplicationPrivate *priv = FIREZ_APPLICATION (object)->priv;

    g_free (priv->uuid);
    //if (priv->initial_date != NULL)
    //    g_free (priv->initial_date);


    //g_clear_object (&(priv->settings));

    G_OBJECT_CLASS (firez_application_parent_class)->finalize (object);
}

static void
firez_application_activate (GApplication *application){
    FirezApplicationPrivate *priv;
    GError *error;
    
    priv = FIREZ_APPLICATION (application)->priv;
    
    /* Creates menus */
    firez_application_set_app_menu (application);
    
    if (priv->window != NULL){
        gtk_window_present (GTK_WINDOW (priv->window));
    }else{
        firez_window_new(FIREZ_APPLICATION (application));
    }
    
    if (priv->configdb)
        ManageDB_sidebar(FIREZ_APPLICATION (application));
}

static void
firez_application_startup (GApplication *app)
{
  G_APPLICATION_CLASS (firez_application_parent_class)->startup (app);
  //TODO

  /* We're assuming the application is called as a service only by the shell search system */
  if ((g_application_get_flags (app) & G_APPLICATION_IS_SERVICE) != 0)
    g_application_set_inactivity_timeout (app, 3 * 60 * 1000);
}

static gint
firez_application_command_line (GApplication            *app,
                               GApplicationCommandLine *command_line)
{
    FirezApplicationPrivate *priv;

    GOptionContext *context;
    gchar **argv;
    GError *error;
    gint argc;

    priv = FIREZ_APPLICATION (app)->priv;
    argv = g_application_command_line_get_arguments (command_line, &argc);
    context = g_option_context_new (N_("- FIREZERO management"));
    g_option_context_add_main_entries (context, firez_application_goptions, GETTEXT_PACKAGE);

    error = NULL;
    if (!g_option_context_parse (context, &argc, &argv, &error)){
        g_critical ("Failed to parse argument: %s", error->message);
        g_error_free (error);
        g_option_context_free (context);
        return 1;
    }

    if (show_version){
        g_print ("firezero: Version %s\n", PACKAGE_VERSION);
        return 0;
    }

    if (uuid != NULL){
        firez_application_set_uuid (FIREZ_APPLICATION (app), uuid);
        g_clear_pointer (&uuid, g_free);
    }
    
    if (show_configdb)
        firez_application_set_configdb(FIREZ_APPLICATION (app), show_configdb);
    

    g_option_context_free (context);
    g_strfreev (argv);

    g_application_activate (app);

  return 0;
}

static void
firez_application_set_app_menu (GApplication *app)
{
    
    GMenu *menu;

    g_action_map_add_action_entries (G_ACTION_MAP (app),
                                   firez_app_entries,
                                   G_N_ELEMENTS (firez_app_entries),
                                   app);

    menu = g_menu_new ();
    g_menu_append (menu, _("Login"), "app.login");
    g_menu_append (menu, _("Manager Data Base"), "app.managedb");
    g_menu_append (menu, "_About", "app.about");
    g_menu_append (menu, "_Quit", "app.quit");
    
    const gchar *accels[2] = { "<Primary>q", NULL };
    gtk_application_set_accels_for_action (GTK_APPLICATION (app), "app.quit", accels);
    
    gtk_application_set_app_menu (app, G_MENU_MODEL (menu));
    g_object_unref (menu);
}

static void
firez_application_show_about (GSimpleAction *simple,
                             GVariant      *parameter,
                             gpointer       user_data)
{
  FirezApplicationPrivate *priv;
  char *copyright;
  GDateTime *date;
  int created_year = 2015;
  const gchar *authors[] = {
    "Teófanes Enrique Paz Morón <teofanesp12@gmail.org>",
    NULL
  };
  const gchar *artists[] = {
    "Teófanes Enrique Paz Morón <teofanesp12@gmail.org>",
    NULL
  };

    priv = FIREZ_APPLICATION (user_data)->priv;
    date = g_date_time_new_now_local ();

    if (g_date_time_get_year (date) == created_year){
      copyright = g_strdup_printf (_("Copyright \xC2\xA9 %Id "
                                     "The FireZero authors"),
                                   created_year);
    }else{
        copyright = g_strdup_printf (_("Copyright \xC2\xA9 %Id\xE2\x80\x93%Id "
                                     "The FireZero authors"),
                                   created_year, g_date_time_get_year (date));
    }

    gtk_show_about_dialog (GTK_WINDOW (priv->window),
                         "program-name", _("FIREZERO"),
                         "version", VERSION,
                         "copyright", copyright,
                         "license-type", GTK_LICENSE_GPL_3_0,
                         "authors", authors,
                         "artists", artists,
                         "logo-icon-name", "firezero",
                         "translator-credits", _("translator-credits"),
                         NULL);
    g_free (copyright);
    g_date_time_unref (date);
}

static void
firez_application_quit (GSimpleAction *simple,
                       GVariant      *parameter,
                       gpointer       user_data)
{
  FirezApplicationPrivate *priv = FIREZ_APPLICATION (user_data)->priv;

  gtk_widget_destroy (priv->window);
}

/* Public API */
FirezApplication*
firez_application_new (void){
    g_set_application_name ("firezero");

    return g_object_new (firez_application_get_type (),
                       "application-id", "fire.zero.org",//TODO Using to FireZero_Service
                       "flags", G_APPLICATION_HANDLES_COMMAND_LINE,
                       NULL);
}
/*
GSettings*
firez_application_get_settings (FirezApplication *app)
{
  return app->priv->settings;
}
*/
void
firez_application_set_uuid (FirezApplication *application,
                           const gchar     *uuid)
{
  FirezApplicationPrivate *priv = application->priv;

  g_free (priv->uuid);
  priv->uuid = g_strdup (uuid);
}

void
firez_application_set_configdb (FirezApplication *application,
                                const gboolean configdb){
    FirezApplicationPrivate *priv = application->priv;
    priv->configdb = configdb;
}

void
firez_application_set_window(FirezApplication *app, GtkWindow *window){
    FirezApplicationPrivate *priv = app->priv;
    priv->window = window;
}
/*
void
firez_application_set_initial_date (FirezApplication *application,
                                   const icaltimetype *date)
{
  FirezApplicationPrivate *priv = application->priv;

  g_free (priv->initial_date);
  priv->initial_date = gcal_dup_icaltime (date);
}*/
