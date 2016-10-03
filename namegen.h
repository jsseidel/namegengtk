#include <gtk/gtk.h>
#include <glib.h>

#define BUILDER_XML_RESOURCE "/res/namegen.glade"
#define FFN_RESOURCE "/res/names/ffn.txt"
#define MFN_RESOURCE "/res/names/mfn.txt"
#define LN_RESOURCE "/res/names/ln.txt"
#define MAX_NAME_LEN 64
#define MAX_OBSCURITY_FIRST 20
#define MAX_OBSCURITY_LAST 20

#ifndef NAMEARRAY
#define NAMEARRAY
typedef struct {
	gchar **pnames;
	gint len;
} NameArray;
#endif

#ifndef NAMEGENAPP
#define NAMEGENAPP
typedef struct {
	/* 
	 * GTK stuff
	 */
	GtkWidget *pWindow;
	GtkWidget *pRadioMale;	
	GtkWidget *pRadioFemale;	
	GtkWidget *pSpinNumNames;	
	GtkWidget *pScaleFirstNameObs;	
	GtkWidget *pScaleSurnameObs;
	GtkWidget	*pTextView;
	/*
	 * App specific stuff
	 */
	NameArray ffn;	
	NameArray mfn;	
	NameArray ln;	
} NameGenApp;
#endif

/*
 * signal_handler.c
 */
void on_window_destroy(GtkWidget *object, NameGenApp *app);
void on_buttonQuit_clicked(GtkButton *widget, NameGenApp *app);
void on_buttonGenerateNames_clicked(GtkButton *widget, NameGenApp *app);
/*
 * namegen.c
 */
void get_random_name(NameGenApp *app, gboolean male, gint fnobscurity, gint lnobscurity, gchar *postfix, gchar *nameBuffer, gsize nameBufferSize);
gboolean load_name_db(NameGenApp *app);
void free_app(NameGenApp *app);
