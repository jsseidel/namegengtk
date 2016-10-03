#include "namegen.h"
#include <string.h>
#include <stdio.h>

void on_window_destroy(GtkWidget *object, NameGenApp *app) {
	gtk_main_quit();
}

void on_buttonQuit_clicked(GtkButton *widget, NameGenApp *app) {
	free_app(app);	
	gtk_main_quit();
}

void on_buttonGenerateNames_clicked(GtkButton *widget, NameGenApp *app) {
	GtkTextBuffer *tbp;
	int i;
	gchar name[MAX_NAME_LEN];
	GtkAdjustment *apnn, *apfn, *apln;
	GtkToggleButton *bp;

	tbp = gtk_text_view_get_buffer(GTK_TEXT_VIEW(app->pTextView));

	gtk_text_buffer_set_text(tbp, "", -1);

	apnn = gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(app->pSpinNumNames));
	apfn = gtk_range_get_adjustment(GTK_RANGE(app->pScaleFirstNameObs));
	apln = gtk_range_get_adjustment(GTK_RANGE(app->pScaleSurnameObs));

	bp = GTK_TOGGLE_BUTTON(app->pRadioMale);

	for (i=0; i<(int)gtk_adjustment_get_value(apnn); i++) {
		get_random_name(app, gtk_toggle_button_get_active(bp), (int)gtk_adjustment_get_value(apfn), (int)gtk_adjustment_get_value(apln), "\n", name, MAX_NAME_LEN);
		gtk_text_buffer_insert_at_cursor(tbp, name, strlen(name));
	}	
}
