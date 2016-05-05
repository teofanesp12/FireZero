
 * login.c -- Using GUI.                                                       *
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

#include <module/login.h>

#include <libpq-fe.h>
#include <stdio.h>

//TODO: delete to string and using GNU tools
#include <string.h>

#include <configure.h>


typedef char* String;

static GtkWidget
    *password_entry,
    *user_entry,
    *spinner,
    *dialog;

/* Esta função vai ser removida para outro perfil chamado tools */

GtkInfoBar *bar;
GtkWidget *message_label;
GtkGrid*
alert_create(char* msg){
    GtkWidget *widget, *content_area;
    GtkGrid *grid = GTK_GRID(gtk_grid_new());

    widget = gtk_info_bar_new ();
    bar = GTK_INFO_BAR (widget);

    gtk_widget_set_no_show_all (widget, TRUE);
    message_label = gtk_label_new (msg);
    gtk_widget_show (message_label);
    content_area = gtk_info_bar_get_content_area (bar);
    gtk_container_add (GTK_CONTAINER (content_area),
                       message_label);

    gtk_info_bar_add_button (bar,
                             "_OK",
                             GTK_RESPONSE_OK);
    g_signal_connect (bar,
                      "response",
                      G_CALLBACK (gtk_widget_hide),
                      NULL);
    gtk_grid_attach (GTK_GRID (grid),
                     widget,
                     0, 2, 1, 1);

    // show an error message
    //gtk_label_set_text (GTK_LABEL (message_label), msg);

    //gtk_info_bar_set_message_type (bar, GTK_MESSAGE_ERROR);
    //gtk_info_bar_set_message_type (bar, GTK_MESSAGE_WARNING);
    //gtk_info_bar_set_message_type (bar, GTK_MESSAGE_QUESTION);
    gtk_info_bar_set_message_type (bar, GTK_MESSAGE_OTHER);

    gtk_widget_show (GTK_WIDGET(bar));
    return grid;
}

void
alert(GtkMessageType message_type, char* msg, ...){
    gtk_label_set_text (GTK_LABEL (message_label), msg);
    gtk_info_bar_set_message_type (bar, message_type);
    gtk_widget_show (GTK_WIDGET(bar));
}

/* Metodos do Banco de Dados */
int
conexao(){
    if (!dbName)
        dbName = "postgres";
    
    gchar *filename = g_build_filename ( g_get_home_dir(), LOCAL_SHARE, "firezero.conf", NULL );
    if (!g_file_test (filename, G_FILE_TEST_IS_REGULAR)){
        g_print("Error: File ConfDB\n");//TODO Open GUI Conf
        alert(GTK_MESSAGE_ERROR, "Configure o Sistema: Conexão do Banco de Dados.\n");
        g_free (filename);
        return 1;
    }
    g_free (filename);
    
    button_load_conf_clicked(NULL,NULL);
    #ifdef DEBUG
    g_print("%s:%s-%s-%s\n",DBConf.Host, DBConf.Port, DBConf.Login, DBConf.PassWord);
    #endif
    conn = PQsetdbLogin(DBConf.Host, DBConf.Port, NULL, NULL, dbName, DBConf.Login, DBConf.PassWord);
    if(PQstatus(conn) == CONNECTION_OK){
        alert(GTK_MESSAGE_WARNING, "Conexão efetuada com sucesso.");
    }else{
        alert(GTK_MESSAGE_ERROR, g_strdup_printf( "Falha na conexão. Erro: %s\n", PQerrorMessage(conn) ));
        PQfinish(conn);
        return 1;
    }
    return 0;
}

/* StartUP*/
void
firez_login_new(GSimpleAction *action,
                GVariant      *parameter,
                gpointer       user_data){
    //FirezApplication *fzapp;
    //fzapp = FIREZ_APPLICATION(user_data)
    //fzapp->parent APP
    
    Dialog_Login(NULL, user_data);
}

void
Dialog_Login(GtkWindow *window,
               gpointer   user_data){
    GtkWidget *conteudo, *conteudo1, *conteudo2, *conteudo_all;
    GtkWidget *label_user, *label_password;
    
    //TODO: if not window create new.
    dialog = gtk_dialog_new_with_buttons ("Login...",
                                        window,
                                        GTK_DIALOG_USE_HEADER_BAR,
                                        "_OK",
                                        GTK_RESPONSE_OK,
                                        NULL);

    GtkWidget *combo_db;
    conteudo = gtk_dialog_get_content_area (GTK_DIALOG (dialog));

    /* Adicionamos as Informações para o Login */
    gtk_container_add(GTK_CONTAINER(conteudo), GTK_WIDGET(alert_create("Teste ")) );

    combo_db = gtk_combo_box_text_new ();
    gtk_widget_set_tooltip_text(combo_db, "Banco de Dados.");
    complet_combo_db(combo_db);
    gtk_combo_box_set_active (GTK_COMBO_BOX (combo_db), 0);
    gtk_container_add(GTK_CONTAINER(conteudo), combo_db);

    conteudo_all=gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_container_add(GTK_CONTAINER(conteudo), conteudo_all);

    // Label
    conteudo1=gtk_box_new(GTK_ORIENTATION_VERTICAL, 8);
    gtk_container_add(GTK_CONTAINER(conteudo_all), conteudo1);
    
    label_user = gtk_label_new("Usuario: ");
    gtk_widget_set_halign (GTK_WIDGET (label_user), GTK_ALIGN_END);
    gtk_box_pack_start(GTK_BOX(conteudo1), label_user, FALSE, FALSE, 5);
    
    label_password = gtk_label_new("Senha: ");
    gtk_widget_set_halign (GTK_WIDGET (label_password), GTK_ALIGN_END);
    gtk_box_pack_start(GTK_BOX(conteudo1), label_password, FALSE, FALSE, 5);


    // Entry
    conteudo2=gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(conteudo_all), conteudo2);
    

    user_entry=gtk_entry_new();
    gtk_widget_set_tooltip_text(user_entry, "Usuario do Sistema.");
    gtk_entry_set_placeholder_text(GTK_ENTRY(user_entry), "Usuario");
    gtk_box_pack_start(GTK_BOX(conteudo2), user_entry, FALSE, FALSE, 0);

    password_entry=gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(password_entry), FALSE);
    gtk_widget_set_tooltip_text(password_entry, "Senha do Usuario do Sistema.");
    gtk_entry_set_placeholder_text(GTK_ENTRY(password_entry), "Senha");
    gtk_box_pack_start(GTK_BOX(conteudo2), password_entry, FALSE, FALSE, 0);

    // Nosso carregador
    /*Create a spinner, with extra horizontal and vertical space*/
    spinner = gtk_spinner_new ();
    gtk_widget_set_hexpand (spinner, TRUE);
    //gtk_widget_set_vexpand (spinner, TRUE);
    gtk_box_pack_end(GTK_BOX(conteudo2), spinner, FALSE, FALSE, 0);

    gtk_widget_show_all (dialog);

    g_signal_connect (GTK_DIALOG (dialog),
                    "response",
                    G_CALLBACK (authorized_login),
                    combo_db);
    g_signal_connect (GTK_ENTRY (password_entry),
                    "activate",
                    G_CALLBACK (authorized_login_entry),
                    combo_db);
    g_signal_connect (dialog, "destroy",
                        G_CALLBACK (closed_login), user_data);
    // Preciso sair do programa caso não tiver conn
}
void
authorized_login_entry(GtkEntry *entry,
                       gpointer  user_data){
    authorized_login (GTK_DIALOG(dialog), -5,user_data);
}

void
authorized_login (GtkDialog *dialog,
             gint       response_id,
             gpointer   user_data)
{
    gtk_spinner_start (GTK_SPINNER (spinner));
    const char *paramValues[2];

    //int status_conn;
    String senha, usuario;
    senha   = (String) gtk_entry_get_text( GTK_ENTRY( password_entry ) );
    usuario = (String) gtk_entry_get_text( GTK_ENTRY( user_entry     ) );
    /* Verificamos se os campos Login e Senha estão preenchidos */
    if ( strcmp( usuario, "" ) == 0){
        alert(GTK_MESSAGE_WARNING, "O Campo Usuario Não foi Preenchido...");
        gtk_spinner_stop (GTK_SPINNER (spinner));
        return;
    }

    if ( strcmp( senha, "" ) == 0){
        alert(GTK_MESSAGE_WARNING, "O Campo Senha Não foi Preenchido...");
        gtk_spinner_stop (GTK_SPINNER (spinner));
        return;
    }

    /* Agora Abrimos a conexao */
    dbName = gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT(user_data));
    if (conexao())
        return;

    /*Executa o comando*/
    paramValues[0] = usuario;
    paramValues[1] = senha;

    result = PQexecParams(conn,
                       "SELECT count(*) FROM users WHERE login = $1",
                       1,       /* one param */
                       NULL,    /* let the backend deduce param type */
                       paramValues,
                       NULL,    /* don't need param lengths since text */
                       NULL,    /* default to all text params */
                       0);      /* ask for binary results */
    if (PQresultStatus(result) != PGRES_TUPLES_OK)
    {
        printf( "SELECT Falho: %s", PQerrorMessage(conn));
        exit_connection();
        alert(GTK_MESSAGE_ERROR, g_strdup_printf( "O sistema Não Foi Instado na Base: %s\n",dbName) );
        gtk_spinner_stop (GTK_SPINNER (spinner));
        return;
    }

    /* Verificamos se o User Existe*/
    int num_records, i;
    num_records = PQntuples(result);
    for(i = 0 ; i < num_records ; i++)
    {
        if (strcmp(PQgetvalue(result, i, 0),"0" ) == 0){
            alert(GTK_MESSAGE_ERROR, "Usuario Não existe...");
            exit_connection();
            return;
        }
    }

    /* Verificamos a Senha do Usuario */
    result = PQexecParams(conn,
                       "SELECT count(*) FROM users WHERE login = $1 and password = $2",
                       2,       /* one param */
                       NULL,    /* let the backend deduce param type */
                       paramValues,
                       NULL,    /* don't need param lengths since text */
                       NULL,    /* default to all text params */
                       0);      /* ask for binary results */
    if (PQresultStatus(result) != PGRES_TUPLES_OK)
    {
        alert(GTK_MESSAGE_ERROR, g_strdup_printf( "SELECT failed: %s", PQerrorMessage(conn)) );
        exit_connection();
    }
    num_records = PQntuples(result);
    for(i = 0 ; i < num_records ; i++)
    {
        if (strcmp(PQgetvalue(result, i, 0),"0" ) == 0){
            alert(GTK_MESSAGE_ERROR, "Senha Errada...");
            gtk_spinner_stop (GTK_SPINNER (spinner));
            exit_connection();
            return;
        }
    }
    gtk_spinner_stop (GTK_SPINNER (spinner));
    gtk_widget_destroy (GTK_WIDGET (dialog));
}

void
closed_login(GtkDialog *dialog,
             gpointer  user_data){
    // caso já estiver conectado não sera necessario sair.
    GApplication *application = user_data;
    if (!conn)
        g_application_quit (application);
    if (strcmp(dbName, "postgres")==0)
        g_application_quit (application);
}


void
complet_combo_db(GtkWidget *combo_box){
    if (conexao())
        return;
    /*Executa o comando*/
    result = PQexec(conn, "select datname from pg_database where datistemplate=False;");

    if(!result)
    {
        alert(GTK_MESSAGE_ERROR, "Erro executando comando. ");
    }
    else
    {
        switch(PQresultStatus(result))
        {
            case PGRES_EMPTY_QUERY:
                printf("Nada aconteceu.\n");
                break;
            case PGRES_TUPLES_OK:
                printf("A query retornou %d linhas.\n", PQntuples(result));
                break;
            case PGRES_FATAL_ERROR:
                printf("Erro na Consulta: %s\n", PQresultErrorMessage(result));
                break;
            case PGRES_COMMAND_OK:
                printf("%s linhas afetadas.\n", PQcmdTuples(result));
                break;
            default:
                printf("Algum outro resultado ocorreu.\n");
                break;
        }
    }

    /* Pegamos a Quantidade de campos capturados */
    int campos = PQnfields(result);
    int count  = PQntuples(result);

    int i,j;
    for(i = 0; i < count; i++)
    {
        // Percorre todas as colunas
        for (j = 0; j < campos; j++)
        {
            // Imprime o valor do campo
            gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo_box), PQgetvalue(result, i, j));
        }
    }
    return exit_connection();
}
