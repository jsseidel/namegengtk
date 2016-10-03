#include <stdlib.h>
#include <time.h>
#include "namegen.h"

int main (int argc, char *argv[]) {
	NameGenApp *app;
	GtkBuilder *builder;
	GError *err=NULL;      

	srand(time(NULL));

	/* Allocate new app */
	app = g_slice_new(NameGenApp);

	/* Initialize GTK */
	gtk_init(&argc, &argv);

	/* Create a new builder to load our GUI */	
	builder = gtk_builder_new();
	if (gtk_builder_add_from_resource(builder, BUILDER_XML_RESOURCE, &err) == 0) {
		fprintf(stderr, "Can't add glade xml resource to builder: %s\n", err->message);
		g_error_free(err);
		return 1;	
	}

	/* Load up our outlets, which will be referenced in the signal handlers  */
	app->pWindow = GTK_WIDGET(gtk_builder_get_object(builder, "pWindow"));
	app->pRadioMale = GTK_WIDGET(gtk_builder_get_object(builder, "pRadioMale"));
	app->pRadioFemale = GTK_WIDGET(gtk_builder_get_object(builder, "pRadioFemale"));
	app->pSpinNumNames = GTK_WIDGET(gtk_builder_get_object(builder, "pSpinNumNames"));
	app->pScaleFirstNameObs = GTK_WIDGET(gtk_builder_get_object(builder, "pScaleFirstNameObs"));
	app->pScaleSurnameObs = GTK_WIDGET(gtk_builder_get_object(builder, "pScaleSurnameObs"));
	app->pTextView = GTK_WIDGET(gtk_builder_get_object(builder, "pTextView"));

	/* Connect signals and pass our app as the user-defined data */
	gtk_builder_connect_signals(builder, app);

	/* Free memory used by GtkBuilder object */
	g_object_unref(G_OBJECT(builder));

	/* Show the constructed app window */
	gtk_widget_show(app->pWindow);

	/* Load name DB */
	load_name_db(app);

	/* Event loop */
	gtk_main();

	/* Free up app memory */
	g_slice_free(NameGenApp, app);

	return 0;
}
