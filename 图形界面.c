#include <GL/glut.h>
#include "图形界面.h"
#include "空间直线插补.h"
#include "空间圆弧插补.h"
GtkWidget *window;
void about_system()
{
  GtkWidget *dialog=gtk_message_dialog_new(GTK_WINDOW(window),
  GTK_DIALOG_DESTROY_WITH_PARENT,
  GTK_MESSAGE_INFO,
  GTK_BUTTONS_OK,
  "罗婷婷插补仿真系统，版权所有，翻版必究！");
  gtk_window_set_title(GTK_WINDOW(dialog), "About");
  /*
  GdkColor c1;
  gdk_color_parse (color[rand()%5], &c1);
  gtk_widget_modify_bg(dialog,GTK_STATE_NORMAL,&c1);
  */
  gtk_dialog_run(GTK_DIALOG (dialog));
  gtk_widget_destroy(dialog);
}

GtkWidget* createTab(gchar *filename, gchar *text) {
    GtkWidget *box;
    GtkWidget *label;
    GtkWidget *image;

    box = gtk_hbox_new(FALSE, 5);
    gtk_container_set_border_width(GTK_CONTAINER(box), 2);

    image = gtk_image_new_from_file(filename);
    label = gtk_label_new(text);

    gtk_box_pack_start(GTK_BOX(box), image, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 5);

    gtk_widget_show (image);
    gtk_widget_show (label);

    return box;    
}

GtkWidget *coordinateBox(gchar *text,coordinateBox_data &w)  //子函数化处理图形界面设计后通过返回指针访问函数内数据在C语言里是不现实的，所以只能把数据外移，使用结构体处理可以实现形式化编制化处理，这是集合在信息编码上的妙用
{
  w.box=gtk_vbox_new(FALSE,0);/*创建组合框*/
  
  w.head_label=gtk_label_new(text);
  gtk_box_pack_start(GTK_BOX(w.box),w.head_label,FALSE,FALSE,5);
  
  w.hbox[0]=gtk_hbox_new(FALSE,0); //gtk组合框嵌套布局是很灵活有效的
  w.label[0]=gtk_label_new("x:");/*创建标号*/
  gtk_box_pack_start(GTK_BOX(w.hbox[0]),w.label[0],FALSE,FALSE,5);
  w.entry[0]=gtk_entry_new();/*创建录入构件*/
  gtk_box_pack_start(GTK_BOX(w.hbox[0]),w.entry[0],FALSE,FALSE,5);/*把录入构件加入组合框*/
  gtk_box_pack_start(GTK_BOX(w.box),w.hbox[0],FALSE,FALSE,5);
  
  w.hbox[1]=gtk_hbox_new(FALSE,0);
  w.label[1]=gtk_label_new("y:");/*创建标号*/
  gtk_box_pack_start(GTK_BOX(w.hbox[1]),w.label[1],FALSE,FALSE,5);/*把标号加入组合框*/
  w.entry[1]=gtk_entry_new();/*创建录入构件*/
  gtk_box_pack_start(GTK_BOX(w.hbox[1]),w.entry[1],FALSE,FALSE,5);/*把录入构件加入组合框*/
  gtk_box_pack_start(GTK_BOX(w.box),w.hbox[1],FALSE,FALSE,5);
  
  w.hbox[2]=gtk_hbox_new(FALSE,0);
  w.label[2]=gtk_label_new("z:");/*创建标号*/
  gtk_box_pack_start(GTK_BOX(w.hbox[2]),w.label[2],FALSE,FALSE,5);/*把标号加入组合框*/
  w.entry[2]=gtk_entry_new();/*创建录入构件*/
  gtk_box_pack_start(GTK_BOX(w.hbox[2]),w.entry[2],FALSE,FALSE,5);/*把录入构件加入组合框*/
  gtk_box_pack_start(GTK_BOX(w.box),w.hbox[2],FALSE,FALSE,5);

  return w.box;
}
GtkWidget *tab1Box(coordinateBox_data *w)
{
  GtkWidget *box[3];
  box[0]=gtk_hbox_new(TRUE,0);
  box[1]=coordinateBox("S坐标",w[0]);
  box[2]=coordinateBox("E坐标",w[1]);
  gtk_box_pack_start(GTK_BOX(box[0]),box[1],FALSE,FALSE,5);
  gtk_box_pack_start(GTK_BOX(box[0]),box[2],FALSE,FALSE,5);
  return box[0];
}
GtkWidget *tab2Box(coordinateBox_data *w)
{
  GtkWidget *box[4]; //编制化命名好处多多
  box[0]=gtk_hbox_new(TRUE,0);
  box[1]=coordinateBox("S坐标",w[0]);
  box[2]=coordinateBox("E坐标",w[1]);
  box[3]=coordinateBox("M坐标",w[2]);
  gtk_box_pack_start(GTK_BOX(box[0]),box[1],FALSE,FALSE,5);
  gtk_box_pack_start(GTK_BOX(box[0]),box[2],FALSE,FALSE,5);
  gtk_box_pack_start(GTK_BOX(box[0]),box[3],FALSE,FALSE,5);
  return box[0];
}
GtkWidget *addButton(GtkWidget *w,void (*f)())
{
  GtkWidget *box[2];
  box[0]=gtk_vbox_new(TRUE,0);
  box[1]=gtk_hbox_new(TRUE,0);
  GtkWidget *button=gtk_button_new_with_label("开始仿真");/*创建按钮*/
  gtk_signal_connect(GTK_OBJECT(button),"pressed",GTK_SIGNAL_FUNC(f),NULL);
  gtk_box_pack_start(GTK_BOX(box[0]),w,FALSE,FALSE,5);
  //GtkWidget *label=gtk_label_new("                                                                                        ");
  //GtkWidget *label=gtk_label_new("");
  //gtk_box_pack_start(GTK_BOX(box[1]),label,FALSE,FALSE,5);
  gtk_box_pack_start(GTK_BOX(box[1]),button,FALSE,FALSE,5);
  gtk_box_pack_start(GTK_BOX(box[0]),box[1],FALSE,FALSE,5);
  return box[0];
}
GtkWidget *createMenu()
{
  //建立菜单条并把第一级菜单项放入
  GtkWidget *menubar=gtk_menu_bar_new();//建立菜单条
  GtkWidget *menuitem[2];
  menuitem[0]=gtk_menu_item_new_with_label("文件");//建立菜单项
  gtk_menu_bar_append(GTK_MENU_BAR(menubar),menuitem[0]);//把菜单项加入到菜单条中
  menuitem[1]=gtk_menu_item_new_with_label("帮助");
  gtk_menu_bar_append(GTK_MENU_BAR(menubar),menuitem[1]);
  GtkWidget *menu[2];
  //建立menuitem[0]的子菜单
  menu[0]=gtk_menu_new();//建立菜单
  GtkWidget *menuitem0_0=gtk_menu_item_new_with_label("退出");
  gtk_menu_shell_append(GTK_MENU_SHELL(menu[0]),menuitem0_0);//把菜单项加入到菜单中
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuitem[0]),menu[0]);//最后把菜单menu1粘到菜单项menuitem1上
  //如法炮制menuitem[1]的子菜单
  menu[1]=gtk_menu_new();
  GtkWidget *menuitem1_0=gtk_menu_item_new_with_label("关于");
  gtk_menu_shell_append(GTK_MENU_SHELL(menu[1]),menuitem1_0);
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuitem[1]),menu[1]);

  //连接信号和函数
  gtk_signal_connect(GTK_OBJECT(menuitem0_0),"activate",GTK_SIGNAL_FUNC(gtk_main_quit),NULL);
  gtk_signal_connect(GTK_OBJECT(menuitem1_0),"activate",GTK_SIGNAL_FUNC(about_system),NULL);
  return menubar;
}
GtkWidget *to_a_vbox(GtkWidget *a,GtkWidget *b) //GTK布局的基本思想就是箱子套箱子，容器套容器。而之前不懂得使用子函数进行界面设计，所以显得很凌乱冗长，这就是少生多之思想与混沌思想的区别
{
  GtkWidget *vbox=gtk_vbox_new(FALSE,0);
  gtk_box_pack_start(GTK_BOX(vbox),a,FALSE,FALSE,5);
  gtk_box_pack_start(GTK_BOX(vbox),b,FALSE,FALSE,5);
  return vbox;
}
coordinateBox_data w_tab1[2];
coordinateBox_data w_tab2[3];
int main(int argc, char *argv[]) {
    
    
    GtkWidget *notebook;
    GtkWidget *tab;

    gtk_init(&argc, &argv);
    glutInit(&argc, argv);//对GLUT进行初始化，这个函数必须在其它的GLUT使用之前调用一次
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "罗婷婷插补仿真系统");
    gtk_window_set_icon_from_file(GTK_WINDOW(window),"Goozillian.jpg",0);
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);

    notebook = gtk_notebook_new();

    tab = createTab("Timting.jpg", "空间直线插补");
    
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), addButton(tab1Box(w_tab1),line_interpolation), tab);

    tab = createTab("Timting.jpg", "空间圆弧插补");
    
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), addButton(tab2Box(w_tab2),circle_interpolation/*不提供参数就要使用extern*/), tab);
    

    gtk_container_add(GTK_CONTAINER(window), to_a_vbox(createMenu(),notebook));

    g_signal_connect(GTK_OBJECT(window), "destroy",G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
