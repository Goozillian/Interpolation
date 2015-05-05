#include <gtk/gtk.h>
extern GtkWidget *window;
typedef struct coordinateBox_data{
  GtkWidget *box;
  GtkWidget *head_label;
  GtkWidget *label[3];
  GtkWidget *entry[3];
  GtkWidget *hbox[3];
}coordinateBox_data;
extern coordinateBox_data w_tab1[2];
extern coordinateBox_data w_tab2[3];
