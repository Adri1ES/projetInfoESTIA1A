
#ifndef CALLBACKS_H
#define CALLBACKS_H

#include <gtk/gtk.h>

G_MODULE_EXPORT void init_spin_button (GtkSpinButton *spb, double min_val, double max_val, double val, double step, int digits);
G_MODULE_EXPORT void on_window1_realize (GtkObject *object,gpointer user_data) ;
G_MODULE_EXPORT void on_window1_destroy (GtkObject *object,gpointer user_data) ;

#endif /* CALLBACKS_H */
