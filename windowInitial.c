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
	GdkColor color;
    color.red = 0000;
    color.green = 0000;
    color.blue = 0;

    GdkColor color2;
    color2.red = 0xfff;
    color2.green = 0xffff;
    color2.blue = 0xfff;
	gtk_init(&argc, &argv);
	gtkBuilder = gtk_builder_new();
	gtk_builder_add_from_file(gtkBuilder, "windowInitial.glade", NULL);
	window = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "windowInitial"));
	gtk_widget_set_size_request(GTK_WINDOW(window),500,400);
	gtk_widget_modify_bg(GTK_WINDOW(window), GTK_STATE_NORMAL, &color);

	btnLogin = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "btnLogin"));
	txtUser= GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "txtUser"));
	gtk_widget_modify_bg(GTK_WIDGET(txtUser),GTK_STATE_NORMAL, &color2);
	txtPassword=GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "txtPassword"));
	g_signal_connect (window, "destroy", G_CALLBACK (on_window_destroy), NULL);
	gtk_widget_set_tooltip_text (btnLogin, "Proporcione los datos indicados para realizar el inicio de sesión. ");
	g_signal_connect (btnLogin, "clicked",G_CALLBACK (imprimir),NULL);
	g_object_unref(G_OBJECT(gtkBuilder));
	gtk_widget_show(window);
	gtk_main();
	return 0;
}