/* Instituto Tecnológico de Costa Rica.
   Centro Académico de San José
   Ingeniería en Computación

   Estudiante
   Kathy Brenes Guerrero

   Principios de Sistemas Operativos
   Fecha: 17 de Noviembre del 2015

   Interfaz para la pantalla principal del Spotify

 */


#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//variables globales
GtkBuilder *gtkBuilder;
GtkWidget *window;

void imprimir(){
	printf("Play\n");
}

void on_window_destroy (GtkWidget *object, gpointer user_data) {
	gtk_main_quit();
}//end on window destroy


int main(int argc, char *argv[])
{
	GtkWidget *btnPlay;
	GdkColor color;    
    GdkColor color2;
    
	gtk_init(&argc, &argv);
	gtkBuilder = gtk_builder_new();
	gtk_builder_add_from_file(gtkBuilder, "windowPlayMusic.glade", NULL);
	window = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "windowPlay"));
	gtk_widget_set_size_request(GTK_WINDOW(window),500,400);
	gdk_color_parse ("#008B8B", &color2);
	gtk_widget_modify_bg(GTK_WINDOW(window), GTK_STATE_NORMAL, &color2);

	btnPlay = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "btnPlay"));
	/*txtUser= GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "txtUser"));
	gdk_color_parse ("#ffffff", &color);
	gtk_widget_modify_text(GTK_WIDGET(btnLogin),GTK_STATE_NORMAL, &color);	*/
	g_signal_connect (window, "destroy", G_CALLBACK (on_window_destroy), NULL);
	gtk_widget_set_tooltip_text (btnPlay, "Reproducir aleatoriamente las canciones suministradas. ");
	g_signal_connect (btnPlay, "clicked",G_CALLBACK (imprimir),NULL);
	g_object_unref(G_OBJECT(gtkBuilder));
	gtk_widget_show(window);
	gtk_main();
	return 0;
}