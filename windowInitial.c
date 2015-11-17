#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//variables globales
GtkBuilder *gtkBuilder;
GtkWidget *window;
GtkWidget *txtUser;
GtkWidget *txtPassword;

void imprimir(){
	printf("HOla\n");
}
void on_window_destroy (GtkWidget *object, gpointer user_data) {
	gtk_main_quit();
}//end on window destroy


int main(int argc, char *argv[])
{
	GtkWidget *btnLogin;
	gtk_init(&argc, &argv);
	gtkBuilder = gtk_builder_new();
	gtk_builder_add_from_file(gtkBuilder, "windowInitial.glade", NULL);
	window = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "windowInitial"));
	gtk_widget_set_size_request(GTK_WINDOW(window),900,800);
	btnLogin = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "btnLogin"));
	txtUser= GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "txtUser"));
	txtPassword=GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "txtPassword"));
	g_signal_connect (window, "destroy", G_CALLBACK (on_window_destroy), NULL);
	gtk_widget_set_tooltip_text (btnLogin, "Proporcione los datos indicados para realizar el inicio de sesión. ");
	g_signal_connect (btnLogin, "clicked",G_CALLBACK (imprimir),NULL);
	g_object_unref(G_OBJECT(gtkBuilder));
	gtk_widget_show(window);
	gtk_main();
	return 0;
}