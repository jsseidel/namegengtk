#include "namegen.h"
#include <gio/gio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "resources.h"

static gboolean _load_name_strings_from_input_stream(NameArray *ap, GInputStream *isp);

void get_random_name(NameGenApp *app, gboolean male, gint fnobscurity, gint lnobscurity, gchar *postfix, gchar *nameBuffer, gsize nameBufferSize) {
	gint setSize, obsOffset;
	NameArray *fnlp, *lnlp;
	gchar *fnp, *lnp;

	nameBuffer[0] = '\0';

	fnlp = (male ? &app->mfn : &app->ffn);
	lnlp = &app->ln;

	setSize = (int)((double)fnlp->len/(double)MAX_OBSCURITY_FIRST);	
	obsOffset = setSize * (fnobscurity-1);	

	fnp = fnlp->pnames[rand()%setSize+obsOffset];	
	
	setSize = (int)((double)lnlp->len/(double)MAX_OBSCURITY_LAST);	
	obsOffset = setSize * (lnobscurity-1);	
	
	lnp = lnlp->pnames[rand()%setSize+obsOffset];

	g_strlcat(nameBuffer, fnp, nameBufferSize);
	g_strlcat(nameBuffer, " ", nameBufferSize);
	g_strlcat(nameBuffer, lnp, nameBufferSize);
	g_strlcat(nameBuffer, postfix, nameBufferSize);
}

gboolean load_name_db(NameGenApp *app) {
	GResource *rp;
	GInputStream *isp;
	GError *err = NULL;

	rp = resources_get_resource();

	if (rp == NULL) {
		fprintf(stderr, "Couldn't load resources.\n");
		return FALSE;	
	}

	isp = g_resource_open_stream(rp, FFN_RESOURCE, G_RESOURCE_LOOKUP_FLAGS_NONE, &err);
	if (err != NULL) {
		fprintf (stderr, "Error opening resource stream (%s): %s\n", FFN_RESOURCE, err->message);
		return FALSE;		
	}

	if(!_load_name_strings_from_input_stream(&app->ffn, isp)) {
		fprintf(stderr, "Error loading names from input stream ffn\n");
		return FALSE;	
	}
	
	isp = g_resource_open_stream(rp, MFN_RESOURCE, G_RESOURCE_LOOKUP_FLAGS_NONE, &err);
	if (err != NULL) {
		fprintf (stderr, "Error opening resource stream (%s): %s\n", MFN_RESOURCE, err->message);
		return FALSE;		
	}

	if(!_load_name_strings_from_input_stream(&app->mfn, isp)) {
		fprintf(stderr, "Error loading names from input stream mfn\n");
		return FALSE;	
	}
	
	isp = g_resource_open_stream(rp, LN_RESOURCE, G_RESOURCE_LOOKUP_FLAGS_NONE, &err);
	if (err != NULL) {
		fprintf (stderr, "Error opening resource stream (%s): %s\n", LN_RESOURCE, err->message);
		return FALSE;		
	}

	if(!_load_name_strings_from_input_stream(&app->ln, isp)) {
		fprintf(stderr, "Error loading names from input stream mfn\n");
		return FALSE;	
	}
	
	return TRUE;
}

static gboolean _load_name_strings_from_input_stream(NameArray *ap, GInputStream *isp) {
	gchar **lp;
	gchar *rp;
	gint nameCount;
	gsize charsRead;
	GError *err=NULL;
	GDataInputStream *disp;

	disp = g_data_input_stream_new(isp);

	/* First pass to count number of strings in the file */
	do {
		rp = g_data_input_stream_read_line(disp, &charsRead, NULL, &err);
		if (err != NULL) {
			fprintf (stderr, "Error reading lines from file: %s\n", err->message);
    	g_error_free (err);
			g_object_unref(disp);
			return FALSE;
		}	
		g_free(rp);
		nameCount++;
	} while (rp != NULL);

	lp = malloc(nameCount*sizeof(gchar *));

	/* Second pass to store the strings */
	g_seekable_seek(G_SEEKABLE(disp), 0, G_SEEK_SET, NULL, &err);
	if (err != NULL) {
		fprintf (stderr, "Error seeking to start of file: %s\n", err->message);
		g_error_free (err);
		g_object_unref(disp);
		free(lp);
		return FALSE;
	}	

	nameCount = 0;
	do {
		rp = g_data_input_stream_read_line(disp, &charsRead, NULL, &err);
		if (err != NULL) {
			fprintf (stderr, "Error reading lines from file: %s\n", err->message);
    	g_error_free (err);
			g_object_unref(disp);
			free(lp);
			return FALSE;
		}	
		
		if (rp != NULL) {
			lp[nameCount++] = rp;
		}

	} while (rp != NULL);
	
	g_object_unref(disp);

	ap->pnames = lp;
	ap->len = nameCount;

	return TRUE;
}

void free_app(NameGenApp *app) {
	gint i;

	for (i=0; i<app->ffn.len; i++) {
		g_free(app->ffn.pnames[i]);	
	}
	free(app->ffn.pnames);
	
	for (i=0; i<app->mfn.len; i++) {
		g_free(app->mfn.pnames[i]);	
	}
	free(app->mfn.pnames);
	
	for (i=0; i<app->ln.len; i++) {
		g_free(app->ln.pnames[i]);	
	}
	free(app->ln.pnames);
}
