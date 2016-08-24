/*******************************************************************************\
 * firez-window.c -- Description File.                                         *
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

#include <tools/firez-window.h>

#include <glib/gi18n.h>

//void
//load_geometry (GtkWindow *win){
//    
//}

static void
firez_window_finalize (GObject *object);

struct _FirezWindowPrivate
{
	int test;
};

G_DEFINE_TYPE_WITH_PRIVATE (FirezWindow, firez_window, GTK_TYPE_APPLICATION_WINDOW)



static void
firez_window_class_init (FirezWindowClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS (klass);
	GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

	//klass->tab_removed = firez_window_tab_removed;

	//object_class->dispose = firez_window_dispose;
	object_class->finalize = firez_window_finalize;
	//object_class->get_property = firez_window_get_property;

	//widget_class->window_state_event = firez_window_window_state_event;
	//widget_class->configure_event = firez_window_configure_event;
	//widget_class->key_press_event = firez_window_key_press_event;
}

static void
firez_window_init(FirezWindow *window){
    // TODO subtituir o firez_window_new
}

static void
firez_window_finalize (GObject *object)
{
	FirezWindow *window = FIREZ_WINDOW (object);

	//g_slist_free_full (window->priv->closed_docs_stack, (GDestroyNotify)g_object_unref);

	G_OBJECT_CLASS (firez_window_parent_class)->finalize (object);
}

/* Public API */
void firez_window_new(FirezApplication *application){
    /* Construimos a Janela */
    GtkWidget *header;
    GtkWidget *button, *button1;
    GtkWidget *box;
    GtkWidget *image;
    GIcon *icon;
    
    GtkWidget *searchbar;
    GtkWidget *entry;
    GtkWidget *container_bar, *vbox;
    
    GtkWidget *window;
    
    //GtkWidget *toolbar;
    //GtkStyleContext *style_context;
    //GtkToolItem *new_button;
    
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_application (GTK_WINDOW (window), GTK_APPLICATION (application));
    //Dialog_Login(GTK_WINDOW(window), NULL);
    
    gtk_window_set_default_size (GTK_WINDOW (window), 700, 600);
    gtk_widget_set_size_request(window, 100, 100);
    //gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    /* Enquanto isso montamos a GUI */
    // gtk_window_set_title(GTK_WINDOW(window), "Fire Zero - Bombeiros");
    header = gtk_header_bar_new ();
    gtk_header_bar_set_show_close_button (GTK_HEADER_BAR (header), TRUE);
    gtk_header_bar_set_title (GTK_HEADER_BAR (header), _("Fire Zero - Firefighters"));
    gtk_header_bar_set_has_subtitle (GTK_HEADER_BAR (header), FALSE);
    
    /* END */
    button = gtk_button_new ();
    icon = g_themed_icon_new ("changes-prevent-symbolic");
    image = gtk_image_new_from_gicon (icon, GTK_ICON_SIZE_BUTTON);
    g_object_unref (icon);
    gtk_container_add (GTK_CONTAINER (button), image);
    gtk_header_bar_pack_end (GTK_HEADER_BAR (header), button);
    
    button1 = gtk_toggle_button_new ();
    icon = g_themed_icon_new ("insert-object-symbolic");
    image = gtk_image_new_from_gicon (icon, GTK_ICON_SIZE_BUTTON);
    g_object_unref (icon);
    gtk_container_add (GTK_CONTAINER (button1), image);
    gtk_header_bar_pack_end (GTK_HEADER_BAR (header), button1);
    
    /* START */
    box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_style_context_add_class (gtk_widget_get_style_context (box), "linked");
    button = gtk_button_new ();
    gtk_container_add (GTK_CONTAINER (button), gtk_image_new_from_icon_name ("pan-start-symbolic", GTK_ICON_SIZE_BUTTON));
    gtk_container_add (GTK_CONTAINER (box), button);
    button = gtk_button_new ();
    gtk_container_add (GTK_CONTAINER (button), gtk_image_new_from_icon_name ("view-refresh-symbolic", GTK_ICON_SIZE_BUTTON));
    gtk_container_add (GTK_CONTAINER (box), button);
    button = gtk_button_new ();
    gtk_container_add (GTK_CONTAINER (button), gtk_image_new_from_icon_name ("pan-end-symbolic", GTK_ICON_SIZE_BUTTON));
    gtk_container_add (GTK_CONTAINER (box), button);

    gtk_header_bar_pack_start (GTK_HEADER_BAR (header), box);
    
    gtk_window_set_titlebar (GTK_WINDOW (window), header);
    
    
    vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add (GTK_CONTAINER (window), vbox);
    gtk_container_set_border_width (GTK_CONTAINER (vbox), 0);
    
    
    entry = gtk_search_entry_new ();
    container_bar = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_widget_set_halign (container_bar, GTK_ALIGN_CENTER);
    gtk_box_pack_start (GTK_BOX (container_bar), entry, FALSE, FALSE, 0);
    
    searchbar = gtk_search_bar_new ();
    gtk_search_bar_connect_entry (GTK_SEARCH_BAR (searchbar), GTK_ENTRY (entry));
    gtk_search_bar_set_show_close_button (GTK_SEARCH_BAR (searchbar), FALSE);
    gtk_container_add (GTK_CONTAINER (searchbar), container_bar);
    gtk_box_pack_start (GTK_BOX (vbox), searchbar, FALSE, FALSE, 0);
    
    g_object_bind_property (button1, "active",
                              searchbar, "search-mode-enabled",
                              G_BINDING_BIDIRECTIONAL);
    /* ToolBar 
    // Here we begin to create the toolbar 
    toolbar = gtk_toolbar_new ();
    // Set the toolbar to be the primary toolbar of the application 
    style_context = gtk_widget_get_style_context (toolbar);
    gtk_style_context_add_class (style_context, GTK_STYLE_CLASS_PRIMARY_TOOLBAR);
    // Create a button for the "new" action, with a stock image
    new_button = gtk_tool_button_new_from_stock (GTK_STOCK_NEW);
    // Show the "new" button's label
    gtk_tool_item_set_is_important (new_button, TRUE);
    // Insert the button in the desired position within the toolbar
    gtk_toolbar_insert (GTK_TOOLBAR (toolbar), new_button, 0);
    // Show the button
    gtk_widget_show (GTK_WIDGET (new_button));
    
    g_object_bind_property (button1, "active",
                              toolbar, "show-arrow",
                              G_BINDING_BIDIRECTIONAL);
    //
    // Once we've created the bare-bones of the toolbar, we make
    // sure it has enough horizontal space.
    //
    gtk_widget_set_hexpand (toolbar, TRUE);
    gtk_widget_show (toolbar);
    // Attach the toolbar to the grid and add it to the overall window
    GtkWidget *grid = gtk_grid_new ();
    gtk_grid_attach (GTK_GRID (grid), toolbar, 0, 0, 1, 1);
    gtk_container_add (GTK_CONTAINER (window), GTK_WIDGET (grid));
    gtk_widget_show (GTK_WIDGET (grid));*/
    
    gtk_widget_show_all (window);
    /* Sinais */
    //g_signal_connect (GTK_WINDOW(window), "activate_focus", G_CALLBACK (Dialog_Login), NULL);
    firez_application_set_window(application, GTK_WINDOW(window));
}


GtkWidget*
new_window_app(GApplication *application){
    /* Construimos a Janela */
    GtkWidget *header;
    GtkWidget *button, *button1;
    GtkWidget *box;
    GtkWidget *image;
    GIcon *icon;
    
    GtkWidget *searchbar;
    GtkWidget *entry;
    GtkWidget *container_bar, *vbox;
    
    GtkWidget *window;
    
    //GtkWidget *toolbar;
    //GtkStyleContext *style_context;
    //GtkToolItem *new_button;
    
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_application (GTK_WINDOW (window), GTK_APPLICATION (application));
    //Dialog_Login(GTK_WINDOW(window), NULL);
    
    gtk_window_set_default_size (GTK_WINDOW (window), 700, 600);
    gtk_widget_set_size_request(window, 100, 100);
    //gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    /* Enquanto isso montamos a GUI */
    // gtk_window_set_title(GTK_WINDOW(window), "Fire Zero - Bombeiros");
    header = gtk_header_bar_new ();
    gtk_header_bar_set_show_close_button (GTK_HEADER_BAR (header), TRUE);
    gtk_header_bar_set_title (GTK_HEADER_BAR (header), _("Fire Zero - Firefighters"));
    gtk_header_bar_set_has_subtitle (GTK_HEADER_BAR (header), FALSE);
    
    /* END */
    button = gtk_button_new ();
    icon = g_themed_icon_new ("changes-prevent-symbolic");
    image = gtk_image_new_from_gicon (icon, GTK_ICON_SIZE_BUTTON);
    g_object_unref (icon);
    gtk_container_add (GTK_CONTAINER (button), image);
    gtk_header_bar_pack_end (GTK_HEADER_BAR (header), button);
    
    button1 = gtk_toggle_button_new ();
    icon = g_themed_icon_new ("insert-object-symbolic");
    image = gtk_image_new_from_gicon (icon, GTK_ICON_SIZE_BUTTON);
    g_object_unref (icon);
    gtk_container_add (GTK_CONTAINER (button1), image);
    gtk_header_bar_pack_end (GTK_HEADER_BAR (header), button1);
    
    /* START */
    box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_style_context_add_class (gtk_widget_get_style_context (box), "linked");
    button = gtk_button_new ();
    gtk_container_add (GTK_CONTAINER (button), gtk_image_new_from_icon_name ("pan-start-symbolic", GTK_ICON_SIZE_BUTTON));
    gtk_container_add (GTK_CONTAINER (box), button);
    button = gtk_button_new ();
    gtk_container_add (GTK_CONTAINER (button), gtk_image_new_from_icon_name ("view-refresh-symbolic", GTK_ICON_SIZE_BUTTON));
    gtk_container_add (GTK_CONTAINER (box), button);
    button = gtk_button_new ();
    gtk_container_add (GTK_CONTAINER (button), gtk_image_new_from_icon_name ("pan-end-symbolic", GTK_ICON_SIZE_BUTTON));
    gtk_container_add (GTK_CONTAINER (box), button);

    gtk_header_bar_pack_start (GTK_HEADER_BAR (header), box);
    
    gtk_window_set_titlebar (GTK_WINDOW (window), header);
    
    
    vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add (GTK_CONTAINER (window), vbox);
    gtk_container_set_border_width (GTK_CONTAINER (vbox), 0);
    
    
    entry = gtk_search_entry_new ();
    container_bar = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_widget_set_halign (container_bar, GTK_ALIGN_CENTER);
    gtk_box_pack_start (GTK_BOX (container_bar), entry, FALSE, FALSE, 0);
    
    searchbar = gtk_search_bar_new ();
    gtk_search_bar_connect_entry (GTK_SEARCH_BAR (searchbar), GTK_ENTRY (entry));
    gtk_search_bar_set_show_close_button (GTK_SEARCH_BAR (searchbar), FALSE);
    gtk_container_add (GTK_CONTAINER (searchbar), container_bar);
    gtk_box_pack_start (GTK_BOX (vbox), searchbar, FALSE, FALSE, 0);
    
    g_object_bind_property (button1, "active",
                              searchbar, "search-mode-enabled",
                              G_BINDING_BIDIRECTIONAL);
    /* ToolBar 
    // Here we begin to create the toolbar 
    toolbar = gtk_toolbar_new ();
    // Set the toolbar to be the primary toolbar of the application 
    style_context = gtk_widget_get_style_context (toolbar);
    gtk_style_context_add_class (style_context, GTK_STYLE_CLASS_PRIMARY_TOOLBAR);
    // Create a button for the "new" action, with a stock image
    new_button = gtk_tool_button_new_from_stock (GTK_STOCK_NEW);
    // Show the "new" button's label
    gtk_tool_item_set_is_important (new_button, TRUE);
    // Insert the button in the desired position within the toolbar
    gtk_toolbar_insert (GTK_TOOLBAR (toolbar), new_button, 0);
    // Show the button
    gtk_widget_show (GTK_WIDGET (new_button));
    
    g_object_bind_property (button1, "active",
                              toolbar, "show-arrow",
                              G_BINDING_BIDIRECTIONAL);
    //
    // Once we've created the bare-bones of the toolbar, we make
    // sure it has enough horizontal space.
    //
    gtk_widget_set_hexpand (toolbar, TRUE);
    gtk_widget_show (toolbar);
    // Attach the toolbar to the grid and add it to the overall window
    GtkWidget *grid = gtk_grid_new ();
    gtk_grid_attach (GTK_GRID (grid), toolbar, 0, 0, 1, 1);
    gtk_container_add (GTK_CONTAINER (window), GTK_WIDGET (grid));
    gtk_widget_show (GTK_WIDGET (grid));*/
    
    gtk_widget_show_all (window);
    /* Sinais */
    //g_signal_connect (GTK_WINDOW(window), "activate_focus", G_CALLBACK (Dialog_Login), NULL);
    return window;
}
