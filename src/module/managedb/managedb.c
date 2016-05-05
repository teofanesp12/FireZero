/*******************************************************************************\
 * managedb.c -- Using GUI.                                                    *
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

#include <module/managedb.h>
#include <bootstrap_db.h>
#include <glib/gi18n.h>
//#include <module/login.h>

/* Objects the GUI */
typedef struct {
    GtkWidget *entry_db;
    GtkWidget *entry_pwd;
    GtkWidget *demo;
    GtkWidget *rootpwd;
    GtkWidget *rootpwd_reply;
    GtkWidget *button;
} FZ_Create;

typedef struct {
    GtkWidget *combo_db;
    GtkWidget *entry_pwd;
    GtkWidget *button;
} FZ_BackUP;

typedef struct {//TODO create new GUI
    GtkWidget *chooser;
    GtkWidget *entry_pwd;
    GtkWidget *new_dbname;
    GtkWidget *button;
    GtkFileFilter *filter;
} FZ_Restore;

typedef struct {
    GtkWidget *combo_db;
    GtkWidget *entry_pwd;
    GtkWidget *button;
} FZ_Delete;

typedef struct {
    GtkWidget *Host,
              *Port,
              *Login,
              *PassWord,
              *entry_pwd,
              *button_load,
              *button_save;
} FZ_Advanced;

GtkWidget *windowdb = NULL;

/* Stack Side */
void
Welcome_side(GtkWidget *widget, GtkWidget *stack);

void
Create_side(GtkWidget *widget, GtkWidget *stack);

void
Backup_side(GtkWidget *widget, GtkWidget *stack);

void
Delete_side(GtkWidget *widget, GtkWidget *stack);

void
Restore_side(GtkWidget *widget, GtkWidget *stack);

void
Advanced_side(GtkWidget *widget, GtkWidget *stack);

/* Buttons */
void
button_create_clicked (GtkButton *button, gpointer user_data);

void
button_refresh_backup_clicked (GtkButton *button, gpointer user_data);

void
button_refresh_delete_clicked (GtkButton *button, gpointer user_data);

//void
//button_load_conf_clicked (GtkButton *button, gpointer user_data);

void
button_save_conf_clicked (GtkButton *button, gpointer user_data);

/* Methods tools */
void
refresh_combo_db (FZ_BackUP* backup, FZ_Delete *delete);

/* Validate Focus */

gboolean
validate_create_focus (
    GtkWidget *widget,
    GdkEvent  *event,
    gpointer   user_data
);

/* StartUP */
void
firez_db_manage (GSimpleAction *action,
                 GVariant      *parameter,
                 gpointer       user_data){
    ManageDB_sidebar(GTK_APPLICATION(user_data));
}

void
ManageDB_sidebar(GtkApplication *application){
    GtkWidget *sidebar;
    GtkWidget *stack;
    GtkWidget *box;
    GtkWidget *widget;
    GtkWidget *header;
    
    windowdb = gtk_application_window_new (application);
    
    header = gtk_header_bar_new ();
    gtk_header_bar_set_show_close_button (GTK_HEADER_BAR(header), TRUE);
    gtk_window_set_titlebar (GTK_WINDOW(windowdb), header);
    gtk_window_set_title(GTK_WINDOW(windowdb), "Gerenciamento do Banco de Dados");
    
    gtk_window_set_default_size (GTK_WINDOW (windowdb), 500, 500);
    
    g_signal_connect (windowdb, "destroy",
                        G_CALLBACK (gtk_widget_destroyed), &windowdb);
    
    box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
    sidebar = gtk_stack_sidebar_new ();
    gtk_box_pack_start (GTK_BOX (box), sidebar, FALSE, FALSE, 0);

    stack = gtk_stack_new ();
    gtk_stack_set_transition_type (GTK_STACK (stack), GTK_STACK_TRANSITION_TYPE_SLIDE_UP_DOWN);
    gtk_stack_sidebar_set_stack (GTK_STACK_SIDEBAR (sidebar), GTK_STACK (stack));

    /* Separator between sidebar and stack */
    widget = gtk_separator_new (GTK_ORIENTATION_VERTICAL);
    gtk_box_pack_start (GTK_BOX(box), widget, FALSE, FALSE, 0);

    gtk_box_pack_start (GTK_BOX (box), stack, TRUE, TRUE, 0);
    
    
    /* Precisamos adicionar as ações... */
    Welcome_side(widget, stack);
    Create_side(widget, stack);
    Backup_side(widget, stack);
    Restore_side(widget, stack);
    Delete_side(widget, stack);
    Advanced_side(widget, stack);
    
    gtk_container_add (GTK_CONTAINER (windowdb), box);
    
    gtk_widget_show_all (windowdb);
}

void
Welcome_side(GtkWidget *widget, GtkWidget *stack){
    widget = gtk_label_new ("Este assistente ira ajuda-lo a Gerenciar um Banco de Dados Mais Rapido e melhor.");
    gtk_stack_add_named (GTK_STACK (stack), widget, "Bem-vindos");
    gtk_container_child_set (GTK_CONTAINER (stack), widget, "title", "Bem-vindos", NULL);
}

void
Create_side(GtkWidget *widget, GtkWidget *stack){
    widget = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    //widget = gtk_label_new ("Este assistente ira ajuda-lo a Criar um Banco de Dados.");
    
    static FZ_Create field;// caso não for static da pau
    
    GtkWidget *container_all,
              *container_label,
              *container_entry,
              *label_all
              ;
    // Container all
    container_all = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_container_add(GTK_CONTAINER(widget), container_all);
    
    // Label's
    container_label = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8);
    gtk_widget_set_halign(container_label, GTK_ALIGN_END);
    gtk_container_add(GTK_CONTAINER(container_all), container_label);
    
    /* nome do DB */
    label_all = gtk_label_new ("Novo Banco de Dados: ");
    gtk_widget_set_halign(label_all, GTK_ALIGN_END);
    gtk_box_pack_start(GTK_BOX(container_label), label_all, FALSE, FALSE, 5);
    
    /* Code Builder or password SuperUser */
    label_all = gtk_label_new ("Senha Master: ");
    gtk_widget_set_halign(label_all, GTK_ALIGN_END);
    gtk_box_pack_start(GTK_BOX(container_label), label_all, FALSE, FALSE, 5);
    
    /* ROOT Password */
    label_all = gtk_label_new ("Senha do Administrador: ");
    gtk_widget_set_halign(label_all, GTK_ALIGN_END);
    gtk_box_pack_start(GTK_BOX(container_label), label_all, FALSE, FALSE, 5);
    
    
    
    label_all = gtk_label_new ("Confirme a Senha do Administrador: ");
    gtk_widget_set_halign(label_all, GTK_ALIGN_END);
    gtk_box_pack_start(GTK_BOX(container_label), label_all, FALSE, FALSE, 5);
    
    
    // Entry's
    container_entry = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(container_all), container_entry);
    gtk_widget_set_hexpand(container_entry, TRUE);
    
    /* nome do DB */
    field.entry_db=gtk_entry_new();
    gtk_widget_set_tooltip_text(field.entry_db, "Digite o Novo Nome do Banco de Dados.");
    gtk_entry_set_placeholder_text(GTK_ENTRY(field.entry_db), "Banco de Dados");
    gtk_box_pack_start(GTK_BOX(container_entry), field.entry_db, FALSE, FALSE, 0);
    
    /* Code Builder or password SuperUser */
    field.entry_pwd=gtk_entry_new();
    gtk_widget_set_tooltip_text(field.entry_pwd, "Digite a senha de Super Usuario.");
    gtk_entry_set_visibility(GTK_ENTRY(field.entry_pwd), FALSE);
    gtk_entry_set_placeholder_text(GTK_ENTRY(field.entry_pwd), "Senha Mestre");
    gtk_box_pack_start(GTK_BOX(container_entry), field.entry_pwd, FALSE, FALSE, 0);
    
    /* ROOT Password */
    field.rootpwd = gtk_entry_new();
    gtk_widget_set_tooltip_text(field.rootpwd, "Digite a senha de Adimistrador do Novo Banco de Dados (login:admin).");
    gtk_entry_set_placeholder_text(GTK_ENTRY(field.rootpwd), "Senha do Administrador");
    gtk_entry_set_visibility(GTK_ENTRY(field.rootpwd), FALSE);
    gtk_box_pack_start(GTK_BOX(container_entry), field.rootpwd, FALSE, FALSE, 0);
    
    /* ROOT Password Reply */
    field.rootpwd_reply = gtk_entry_new();
    gtk_widget_set_tooltip_text(field.rootpwd_reply, "Digite a senha de Adimistrador do Novo Banco de Dados (login:admin).");
    gtk_entry_set_placeholder_text(GTK_ENTRY(field.rootpwd_reply), "Confirme a Senha");
    gtk_entry_set_visibility(GTK_ENTRY(field.rootpwd_reply), FALSE);
    gtk_box_pack_start(GTK_BOX(container_entry), field.rootpwd_reply, FALSE, FALSE, 0);
    
    
    
    /* Demo info preload */
    field.demo = gtk_check_button_new_with_label("Demostração?");
    gtk_widget_set_halign(field.demo, GTK_ALIGN_CENTER);
    gtk_widget_set_tooltip_text(field.demo, "Se na criação as informações de Demostração serão instaladas.");
    gtk_container_add(GTK_CONTAINER(widget), field.demo);
    
    
    
    
    /* Botão de Criar */
    field.button = gtk_button_new_with_label ("Criar");
    gtk_widget_set_tooltip_text(field.button, "Sera ativado quando as Informações estiverem corretas.");
    gtk_widget_set_sensitive (field.button, FALSE);// disable button
    g_signal_connect (GTK_BUTTON (field.button),
                    "clicked", 
                    G_CALLBACK (button_create_clicked), 
                    (gpointer) &field);
    gtk_container_add( GTK_CONTAINER(widget) ,field.button );
    gtk_stack_add_named (GTK_STACK (stack), widget, "Criar");
    gtk_container_child_set (GTK_CONTAINER (stack), widget, "title", "Criar", NULL);
    
    /* Validate Focus */
    
    g_signal_connect (GTK_ENTRY (field.entry_db),
                    "focus-out-event", 
                    G_CALLBACK (validate_create_focus), 
                    (gpointer) &field);
    
    g_signal_connect (GTK_ENTRY (field.entry_pwd),
                    "focus-out-event", 
                    G_CALLBACK (validate_create_focus), 
                    (gpointer) &field);
    
    g_signal_connect (GTK_ENTRY (field.rootpwd),
                    "focus-out-event", 
                    G_CALLBACK (validate_create_focus), 
                    (gpointer) &field);
    
    g_signal_connect (GTK_ENTRY (field.rootpwd_reply),
                    "focus-out-event", 
                    G_CALLBACK (validate_create_focus), 
                    (gpointer) &field);
}

void
Backup_side(GtkWidget *widget, GtkWidget *stack){
    widget = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    static FZ_BackUP field;
    // widget = gtk_label_new ("Este assistente ira ajuda-lo a\nCriar um Backup de um Banco de Dados.");
    
    GtkWidget *container_label,
              *container_entry,
              *label_all,
              *button_refresh
              ;
    
    /* Label's */
    container_label = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8);
    gtk_widget_set_halign(container_label, GTK_ALIGN_END);
    gtk_container_add(GTK_CONTAINER(widget), container_label);
    
    /* Banco de Dados */
    label_all = gtk_label_new("Banco de Dados: ");
    gtk_widget_set_halign(label_all, GTK_ALIGN_END);
    gtk_box_pack_start(GTK_BOX(container_label), label_all, FALSE, FALSE, 5);
    
    /* Senha Mestre */
    label_all = gtk_label_new("Senha Master: ");
    gtk_widget_set_halign(label_all, GTK_ALIGN_END);
    gtk_box_pack_start(GTK_BOX(container_label), label_all, FALSE, FALSE, 5);
    
    /* Button Refresh */
    button_refresh = gtk_button_new_with_label("Atualizar");
    gtk_box_pack_start(GTK_BOX(container_label), button_refresh, FALSE, FALSE, 0);
    
    
    // Entry's
    container_entry = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(widget), container_entry);
    gtk_widget_set_hexpand(container_entry, TRUE);
    
    /* Banco de Dados */
    field.combo_db = gtk_combo_box_text_new ();
    gtk_widget_set_tooltip_text(field.combo_db, "Banco de Dados.");
    gtk_box_pack_start(GTK_BOX(container_entry), field.combo_db, FALSE, FALSE, 0);
    
    /* Code Builder or password SuperUser */
    field.entry_pwd=gtk_entry_new();
    gtk_widget_set_tooltip_text(field.entry_pwd, "Digite a senha de Super Usuario.");
    gtk_entry_set_visibility(GTK_ENTRY(field.entry_pwd), FALSE);
    gtk_entry_set_placeholder_text(GTK_ENTRY(field.entry_pwd), "Senha Mestre");
    gtk_box_pack_start(GTK_BOX(container_entry), field.entry_pwd, FALSE, FALSE, 0);
    
    /* Button Refresh */
    field.button = gtk_button_new_with_label("Backup");
    gtk_box_pack_start(GTK_BOX(container_entry), field.button, FALSE, FALSE, 0);
    
    
    gtk_stack_add_named (GTK_STACK (stack), widget, "Backup");
    gtk_container_child_set (GTK_CONTAINER (stack), widget, "title", "Backup", NULL);
    
    //TODO Criar os sinais refresh e backup.
    
    g_signal_connect (GTK_BUTTON (button_refresh),
                    "clicked", 
                    G_CALLBACK (button_refresh_backup_clicked), 
                    (gpointer) &field);
}

void
Restore_side(GtkWidget *widget, GtkWidget *stack){
    //TODO create GUI
    widget = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    static FZ_Restore field;
    
    // widget = gtk_label_new ("Este assistente ira ajuda-lo a\nRestaurar um Backup de um Banco de Dados.");
    GtkWidget *container_label,
              *container_entry,
              *label_all
              ;
    
    /* Label's */
    container_label = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8);
    gtk_widget_set_halign(container_label, GTK_ALIGN_END);
    gtk_container_add(GTK_CONTAINER(widget), container_label);
    
    /* File */
    label_all = gtk_label_new("Arquivo: ");
    gtk_widget_set_halign(label_all, GTK_ALIGN_END);
    gtk_box_pack_start(GTK_BOX(container_label), label_all, FALSE, FALSE, 5);
    
    /* Password */
    label_all = gtk_label_new("Senha Mestre: ");
    gtk_widget_set_halign(label_all, GTK_ALIGN_END);
    gtk_box_pack_start(GTK_BOX(container_label), label_all, FALSE, FALSE, 5);
    
    /* New DB */
    label_all = gtk_label_new("Nova Base de Dados: ");
    gtk_widget_set_halign(label_all, GTK_ALIGN_END);
    gtk_box_pack_start(GTK_BOX(container_label), label_all, FALSE, FALSE, 5);
    
    
    
    // Entry's
    container_entry = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(widget), container_entry);
    gtk_widget_set_hexpand(container_entry, TRUE);
    
    /* File */
    field.chooser = gtk_file_chooser_button_new (_("Select a file"), GTK_FILE_CHOOSER_ACTION_OPEN);
    field.filter = gtk_file_filter_new ();
    
    gtk_file_filter_set_name (field.filter, _("SQL/Dump"));
    gtk_file_filter_add_mime_type(field.filter, "application/sql");
    //gtk_file_filter_add_mime_type(field.filter, "application/octet-stream");
    gtk_file_filter_add_pattern (field.filter, "*.dump");
    //gtk_file_filter_add_pattern (field.filter, "*.sql");
    g_object_ref_sink (field.filter);
    gtk_file_chooser_set_local_only (GTK_FILE_CHOOSER (field.chooser), FALSE);
    gtk_file_chooser_set_filter (GTK_FILE_CHOOSER(field.chooser), field.filter);
    gtk_box_pack_start(GTK_BOX(container_entry), field.chooser, FALSE, FALSE, 0);
    
    /* Code Builder or password SuperUser */
    field.entry_pwd=gtk_entry_new();
    gtk_widget_set_tooltip_text(field.entry_pwd, "Digite a senha de Super Usuario.");
    gtk_entry_set_visibility(GTK_ENTRY(field.entry_pwd), FALSE);
    gtk_entry_set_placeholder_text(GTK_ENTRY(field.entry_pwd), "Senha Mestre");
    gtk_box_pack_start(GTK_BOX(container_entry), field.entry_pwd, FALSE, FALSE, 0);
    
    /* Code Builder or password SuperUser */
    field.new_dbname=gtk_entry_new();
    gtk_widget_set_tooltip_text(field.new_dbname, "Digite o nome do Novo banco de dados.");
    gtk_entry_set_placeholder_text(GTK_ENTRY(field.new_dbname), "Nome da Nova Base");
    gtk_box_pack_start(GTK_BOX(container_entry), field.new_dbname, FALSE, FALSE, 0);
    
    //TODO to continue...
    
    gtk_stack_add_named (GTK_STACK (stack), widget, "Restaurar");
    gtk_container_child_set (GTK_CONTAINER (stack), widget, "title", "Restaurar", NULL);
}

void
Delete_side(GtkWidget *widget, GtkWidget *stack){
    widget = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    static FZ_Delete field;
    // widget = gtk_label_new ("Este assistente ira ajuda-lo a\nDeletar um Banco de Dados.");
    
    GtkWidget *container_label,
              *container_entry,
              *label_all,
              *button_refresh
              ;
    
    /* Label's */
    container_label = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8);
    gtk_widget_set_halign(container_label, GTK_ALIGN_END);
    gtk_container_add(GTK_CONTAINER(widget), container_label);
    
    /* Banco de Dados */
    label_all = gtk_label_new("Banco de Dados: ");
    gtk_widget_set_halign(label_all, GTK_ALIGN_END);
    gtk_box_pack_start(GTK_BOX(container_label), label_all, FALSE, FALSE, 5);
    
    /* Senha Mestre */
    label_all = gtk_label_new("Senha Master: ");
    gtk_widget_set_halign(label_all, GTK_ALIGN_END);
    gtk_box_pack_start(GTK_BOX(container_label), label_all, FALSE, FALSE, 5);
    
    /* Button Refresh */
    button_refresh = gtk_button_new_with_label("Atualizar");
    gtk_box_pack_start(GTK_BOX(container_label), button_refresh, FALSE, FALSE, 0);
    
    
    // Entry's
    container_entry = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(widget), container_entry);
    gtk_widget_set_hexpand(container_entry, TRUE);
    
    /* Banco de Dados */
    field.combo_db = gtk_combo_box_text_new ();
    gtk_widget_set_tooltip_text(field.combo_db, "Banco de Dados.");
    gtk_box_pack_start(GTK_BOX(container_entry), field.combo_db, FALSE, FALSE, 0);
    
    /* Code Builder or password SuperUser */
    field.entry_pwd=gtk_entry_new();
    gtk_widget_set_tooltip_text(field.entry_pwd, "Digite a senha de Super Usuario.");
    gtk_entry_set_visibility(GTK_ENTRY(field.entry_pwd), FALSE);
    gtk_entry_set_placeholder_text(GTK_ENTRY(field.entry_pwd), "Senha Mestre");
    gtk_box_pack_start(GTK_BOX(container_entry), field.entry_pwd, FALSE, FALSE, 0);
    
    /* Button Refresh */
    field.button = gtk_button_new_with_label("Deletar");
    gtk_box_pack_start(GTK_BOX(container_entry), field.button, FALSE, FALSE, 0);
    
    gtk_stack_add_named (GTK_STACK (stack), widget, "Deletar");
    gtk_container_child_set (GTK_CONTAINER (stack), widget, "title", "Deletar", NULL);
    
    //TODO Criar os sinais refresh e delete.
    
    g_signal_connect (GTK_BUTTON (button_refresh),
                    "clicked", 
                    G_CALLBACK (button_refresh_delete_clicked), 
                    (gpointer) &field);
}

void
Advanced_side(GtkWidget *widget, GtkWidget *stack){
    widget = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    static FZ_Advanced field;
    
    // widget = gtk_label_new ("Isto ira configurar as info de conexão.");
    
    GtkWidget *container_label,
              *container_entry,
              *label_all,
              *button_refresh,
              *container_all
              ;
    GtkAdjustment *adjustment;
    /* Create an adjustment representing an adjustable bounded value */
    //adjustment = gtk_adjustment_new (5432, 0, G_MAXDOUBLE, 1, 0, 0);
    adjustment = gtk_adjustment_new (5432, 0, 100000, 1, 0, 0);
    
    container_all = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_container_add(GTK_CONTAINER(widget), container_all);
    //
    // Label's
    //
    container_label = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8);
    gtk_widget_set_halign(container_label, GTK_ALIGN_END);
    gtk_container_add(GTK_CONTAINER(container_all), container_label);
    
    /* Host Server IP */
    label_all = gtk_label_new("IP: ");
    gtk_widget_set_halign(label_all, GTK_ALIGN_END);
    gtk_box_pack_start(GTK_BOX(container_label), label_all, FALSE, FALSE, 5);
    
    /* Host Server Port */
    label_all = gtk_label_new("Porta: ");
    gtk_widget_set_halign(label_all, GTK_ALIGN_END);
    gtk_box_pack_start(GTK_BOX(container_label), label_all, FALSE, FALSE, 5);
    
    /* Host Server User */
    label_all = gtk_label_new("Usuario: ");
    gtk_widget_set_halign(label_all, GTK_ALIGN_END);
    gtk_box_pack_start(GTK_BOX(container_label), label_all, FALSE, FALSE, 5);
    
    /* Host Server PassWord */
    label_all = gtk_label_new("Senha: ");
    gtk_widget_set_halign(label_all, GTK_ALIGN_END);
    gtk_box_pack_start(GTK_BOX(container_label), label_all, FALSE, FALSE, 5);
    
    //
    // Entry's
    //
    container_entry = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(container_all), container_entry);
    gtk_widget_set_hexpand(container_entry, TRUE);
    
    /* Host Server IP */
    field.Host = gtk_entry_new ();
    gtk_widget_set_tooltip_text(field.Host, "IP do Servidor do banco de dados...\nEX:localhost");
    gtk_entry_set_placeholder_text(GTK_ENTRY(field.Host), "EX: localhost");
    gtk_box_pack_start(GTK_BOX(container_entry), field.Host, FALSE, FALSE, 0);
    
    /* Host Server Porta */
    //field.Port = gtk_entry_new ();
    field.Port = gtk_spin_button_new (adjustment, 1, 0);
    gtk_widget_set_tooltip_text(field.Port, "Porta do Servidor do banco de dados...\nEX: 5432");
    gtk_entry_set_placeholder_text(GTK_ENTRY(field.Port), "EX: 5432");
    gtk_box_pack_start(GTK_BOX(container_entry), field.Port, FALSE, FALSE, 0);
    
    /* Host Server User */
    field.Login = gtk_entry_new ();
    gtk_widget_set_tooltip_text(field.Login, "Usuario do banco de dados...");
    gtk_entry_set_placeholder_text(GTK_ENTRY(field.Login), "Usuario");
    gtk_box_pack_start(GTK_BOX(container_entry), field.Login, FALSE, FALSE, 0);
    
    /* Host Server PassWord */
    field.PassWord = gtk_entry_new ();
    gtk_widget_set_tooltip_text(field.PassWord, "Senha do Usuario do banco de dados...");
    gtk_entry_set_placeholder_text(GTK_ENTRY(field.PassWord), "Senha");
    gtk_entry_set_visibility(GTK_ENTRY(field.PassWord), FALSE);
    gtk_box_pack_start(GTK_BOX(container_entry), field.PassWord, FALSE, FALSE, 0);
    
    /* Buttons */
    //container_button_all = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    //gtk_container_add(GTK_CONTAINER(container_all), container_button_all);

    field.button_load = gtk_button_new_with_label("Ler");
    gtk_box_pack_start(GTK_BOX(widget), field.button_load, FALSE, FALSE, 0);
    
    field.button_save = gtk_button_new_with_label("Salvar");
    gtk_box_pack_start(GTK_BOX(widget), field.button_save, FALSE, FALSE, 0);
    
    gtk_stack_add_named (GTK_STACK (stack), widget, "Avançado");
    gtk_container_child_set (GTK_CONTAINER (stack), widget, "title", "Avançado", NULL);
    
    /* Sinais */
    
    g_signal_connect (GTK_BUTTON (field.button_load),
                    "clicked", 
                    G_CALLBACK (button_load_conf_clicked), 
                    (gpointer) &field);
    
    g_signal_connect (GTK_BUTTON (field.button_save),
                    "clicked", 
                    G_CALLBACK (button_save_conf_clicked), 
                    (gpointer) &field);
}

/* Buttons */
void
button_create_clicked (GtkButton *button, gpointer user_data){
    
    FZ_Create *field = user_data;
    if (!conn)
        if (connection() != 0){
            g_print("Configure a Conexão do Sistema");
            return;
        }
    gchar* SQL;
    
    SQL = g_strdup_printf(str_boot_create, gtk_entry_get_text(GTK_ENTRY(field->entry_db)) );
    
    result = PQexec(conn, SQL );
    
    g_free(SQL);
    
    if(!result)
    {
        g_print("Erro executando comando. ");
    }
    else
    {
        switch(PQresultStatus(result))
        {
            case PGRES_EMPTY_QUERY:
                g_print("Nada aconteceu.\n");
                break;
            case PGRES_TUPLES_OK:
                g_print("A query retornou %d linhas.\n", PQntuples(result));
                break;
            case PGRES_FATAL_ERROR:
                g_print("Erro na Consulta: %s\n", PQresultErrorMessage(result));
                break;
            case PGRES_COMMAND_OK:
                g_print("%s linhas afetadas.\n", PQcmdTuples(result));
                break;
            default:
                g_print("Algum outro resultado ocorreu.\n");
                break;
        }
    }
}

void
button_load_conf_clicked(GtkButton *button, gpointer user_data){

    GError *error=NULL;
    GKeyFile *key_file;
    gchar *filename;
    FZ_Advanced *field=NULL;
    if (user_data)
        field = user_data;
    
    key_file = g_key_file_new();
    
    filename = g_build_filename ( g_get_home_dir(), LOCAL_SHARE, "firezero.conf", NULL );
    if (!g_file_test (filename, G_FILE_TEST_IS_REGULAR)){
        g_print("Error");//TODO Create Dialog
        g_key_file_free (key_file);
        g_free (filename);
        return;
    }
    
    if (!g_key_file_load_from_file(key_file, filename, G_KEY_FILE_NONE, &error))
        g_print("ERROR: %s\n", error->message);//TODO Create Dialog
    g_free (filename);
    
    //FIXME Pegamos todas as Info do Arquivo
    gchar *ip, *login, *password;
    int port, len_password;
    ip = g_key_file_get_value(key_file, "DBConf", "IP", error);
    port = g_key_file_get_integer(key_file, "DBConf", "port", error);
    login = g_key_file_get_value(key_file, "DBConf", "user", error);
    
    len_password = g_key_file_get_integer(key_file, "DBConf", "len", error);
    #ifdef DEBUG
    g_print("Len:%d\n",len_password);
    #endif
    if (len_password){
        password = g_key_file_get_value(key_file, "DBConf", "password", error);
        #ifdef DEBUG
        g_print("Senha0:%s\n",password);
        #endif
        password = g_base64_decode (password, &len_password);
        #ifdef DEBUG
        g_print("Senha1:%s\n",password);
        #endif
        password = g_utf8_strreverse (password, len_password);
        #ifdef DEBUG
        g_print("Senha2:%s\n",password);
        #endif
    }else
        password = "";
    
    if (field){
        gtk_entry_set_text( GTK_ENTRY(field->Host), ip=="" ? ip : "localhost");
        gtk_spin_button_set_value(field->Port, port);
        gtk_entry_set_text( GTK_ENTRY(field->Login), login);
        gtk_entry_set_text( GTK_ENTRY(field->PassWord), password);
    }
    
    #ifdef DEBUG
    if (error){
        g_print("ERRO: %s", error->message);
    }
    g_print("%s:%d\n%s-%s\n",ip,port,login, password);
    #endif
    
    DBConf.Host     = ip=="" ? ip : "localhost";
    DBConf.Port     = g_strdup_printf("%d", port);
    DBConf.Login    = login;
    DBConf.PassWord = password;
    
    #ifdef DEBUG
    g_print("%s:%s\n%s-%s\n",DBConf.Host,DBConf.Port,DBConf.Login, DBConf.PassWord);
    #endif
}

void
button_save_conf_clicked (GtkButton *button, gpointer user_data){
    
    GError *error=NULL;
    GKeyFile *key_file;
    gchar *filename;
    FZ_Advanced *field = user_data;
    /*if (!conn)
        if (connection() != 0){
            g_print("Configure a Conexão do Sistema");
            return;
        }
    */
    key_file = g_key_file_new();
    
    // Attrs
    gchar *host = gtk_entry_get_text(field->Host);
    if (!host)
        host = "localhost";
    g_key_file_set_value (key_file, "DBConf", "IP", host);
    //g_free (host);
    
    gint port = gtk_spin_button_get_value_as_int (field->Port);
    if (!port)
        port = 5432;
    g_key_file_set_integer (key_file, "DBConf", "port", port);
    
    gchar *login = gtk_entry_get_text(field->Login);
    g_key_file_set_value (key_file, "DBConf", "user", login);
    //g_free (login);
    
    gchar *password = gtk_entry_get_text(field->PassWord);
    int len_password = gtk_entry_get_text_length(field->PassWord);
    if (len_password){
        g_key_file_set_integer (key_file, "DBConf", "len", len_password);
        password = g_utf8_strreverse (password, len_password);
        password = g_base64_encode (password, len_password);
        g_key_file_set_value (key_file, "DBConf", "password", password);
        //g_free (password);
    }
    
    filename = g_strdup_printf("%s/%s", g_get_home_dir (), LOCAL_SHARE);
    
    if (!g_file_test (filename, G_FILE_TEST_IS_DIR))
        if ( g_mkdir(filename, 0777) == -1 )
            g_print("Error: Criar Dir.\n");
    
    filename = g_build_filename (filename, "firezero.conf", NULL);
    
    if (!g_key_file_save_to_file (key_file, filename, &error))
        g_print("ERROR: %s\n", error->message);//TODO Create Dialog
    
    g_key_file_free (key_file);
    g_free (filename);

    //
    //TODO using to field DBConf and to save in filename
    //
}

void
button_refresh_backup_clicked (GtkButton *button, gpointer user_data){
    if (user_data)
        refresh_combo_db( (FZ_BackUP *) user_data, NULL);
}

void
button_refresh_delete_clicked (GtkButton *button, gpointer user_data){
    if (user_data)
        refresh_combo_db(NULL, (FZ_Delete *) user_data );
}

/* -- Validate Focus -- */
gboolean
focus_set_sensitive(gboolean old, gboolean new, GtkWidget *widget){
    if (old != new){
        gtk_widget_set_sensitive (widget, new);
    }
    return FALSE;
    //
    // did not receive focus-out-event.
    // If you connect a handler to this signal, 
    // it must return FALSE so the entry gets the event as well 
    //
}
gboolean
validate_create_focus (GtkWidget *widget,
               GdkEvent  *event,
               gpointer   user_data){
    // Validamos as Informações para liberar o botão.
    FZ_Create *field = user_data;
    gboolean active_button = gtk_widget_get_sensitive(field->button);
    gboolean active_button_old = active_button;
    
    // Validate DB
    if (g_strcmp0( gtk_entry_get_text( GTK_ENTRY(field->entry_db) ), "" ) == 0 ){
        return focus_set_sensitive(active_button_old, FALSE, field->button);
    }else{
        active_button = TRUE;
    }
    
    
    // Validate password
    if ( g_strcmp0( gtk_entry_get_text( GTK_ENTRY(field->rootpwd) ), gtk_entry_get_text( GTK_ENTRY(field->rootpwd_reply) ) ) == 0 ){
        active_button = TRUE;
    }else{
        return focus_set_sensitive(active_button_old, FALSE, field->button);
    }
    
    //TODO: Validate Password Master
    // para fazer
    
    return focus_set_sensitive(active_button_old, active_button, field->button);
}

/* Methods tools */
void
refresh_combo_db (FZ_BackUP* backup, FZ_Delete* delete){
    if (backup)
        g_print("BACKUP\n");
    else if (delete)
        g_print("DELETE\n");
    //TODO incluir os metodos para carregar as Databases.
}

/* the functions SQL */

int
connection(){
    /* @Return: 0 = No error, 1 = Error connection */
    if (!dbName)
        dbName = "postgres";
    
    button_load_conf_clicked(NULL,NULL);
    conn = PQsetdbLogin(DBConf.Host, DBConf.Port, NULL, NULL, dbName, DBConf.Login, DBConf.PassWord);
    if(PQstatus(conn) == CONNECTION_OK){
        g_print("Sucesso...");
    }else{
        g_print("Falha na conexão. Erro: %s\n", PQerrorMessage(conn));
        PQfinish(conn);
        return 1;
    }
    return 0;
}

void
exit_connection(void){
    /*Libera o nosso objeto*/
    if (result)
        PQclear(result);
    /*Verifica se a conexão está aberta e a encerra*/
    if(conn != NULL)
        PQfinish(conn);
    conn = NULL;
    #ifdef DEBUG
    g_print("Connection Closed...\n");
    #endif
}
