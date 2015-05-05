#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include "链表.h"
LinkList L;
const GLfloat GL_PI = 3.1415926536f;
typedef struct glPoint{
  GLfloat x;
  GLfloat y;
  GLfloat z;
}glPoint;
void draw1(void)
{
  GLfloat x,y,z,angle;
  glClear(GL_COLOR_BUFFER_BIT); 
  //设置画图使用的颜色 
  glColor3f(1.0f, 0.0f, 0.0f); 
  //保存矩阵 
  glPushMatrix(); 
  //旋转, 如果不旋转，那些不同层次的点都重叠在一起，看不出3D效果了。 
  glRotatef(200.0f, 1.0f, 0.0f, 0.0f); 
  glRotatef(120.5f, 0.0f, 1.0f, 0.0f); 
  glBegin(GL_LINES);
  z=0.0f;
  for(angle=0.0f;angle<=GL_PI*3.0f;angle+=0.5f)
  {
    x=50.0f*sin(angle);
    y=50.0f*cos(angle);
    glVertex3f(x,y,z);
    x=50.0f*sin(angle+3.1415f);
    y=50.0f*cos(angle+3.1415f);
    glVertex3f(x,y,z);
  }
  glEnd();
  glPopMatrix();
  glFlush();
}
static GLfloat xx=0.0,yy=0.0,zz=0.0,radius=66.0,M=88.0,N=88.0; //单个文件使用到全局变量要用static
void draw2(void)
{
 float step_z = GL_PI/M;  
 float step_xy = 2*GL_PI/N;  
 float x[4],y[4],z[4];  
  
 float angle_z = 0.0;  
 float angle_xy = 0.0;  
 int i=0, j=0;  
 glClear(GL_COLOR_BUFFER_BIT); 
  //设置画图使用的颜色 
  glClearColor(1.0,1.0,1.0,0.0);
  //保存矩阵 
  glPushMatrix(); 
  //旋转, 如果不旋转，那些不同层次的点都重叠在一起，看不出3D效果了。 
  glRotatef(200.0f, 1.0f, 0.0f, 0.0f); 
  glRotatef(120.5f, 0.0f, 1.0f, 0.0f); 
  glBegin(GL_LINES); 
  for(i=0; i<M; i++)  
  {  
   angle_z = i * step_z;  
     
   for(j=0; j<N; j++)  
   {  
    angle_xy = j * step_xy;  
  
    x[0] = radius * sin(angle_z) * cos(angle_xy);  
    y[0] = radius * sin(angle_z) * sin(angle_xy);  
    z[0] = radius * cos(angle_z);  
  
    x[1] = radius * sin(angle_z + step_z) * cos(angle_xy);  
    y[1] = radius * sin(angle_z + step_z) * sin(angle_xy);  
    z[1] = radius * cos(angle_z + step_z);  
  
    x[2] = radius*sin(angle_z + step_z)*cos(angle_xy + step_xy);  
    y[2] = radius*sin(angle_z + step_z)*sin(angle_xy + step_xy);  
    z[2] = radius*cos(angle_z + step_z);  
  
    x[3] = radius * sin(angle_z) * cos(angle_xy + step_xy);  
    y[3] = radius * sin(angle_z) * sin(angle_xy + step_xy);  
    z[3] = radius * cos(angle_z);  
  
    for(int k=0; k<4; k++)  
    {  
     glVertex3f(xx+x[k], yy+y[k],zz+z[k]);  
    }  
   }  
  }  
 glEnd();
  glPopMatrix();
  glFlush(); 
}
void draw3(void)
{
  glClear(GL_COLOR_BUFFER_BIT); 
  //设置画图使用的颜色 
  glClearColor(1.0,1.0,1.0,0.0); 
  //保存矩阵 
  glPushMatrix(); 
  //旋转, 如果不旋转，那些不同层次的点都重叠在一起，看不出3D效果了。 
  glRotatef(200.0f, 1.0f, 0.0f, 0.0f); 
  glRotatef(120.5f, 0.0f, 1.0f, 0.0f); 
  glBegin(GL_LINES);
  
  GLfloat l=66;
  glPoint P[8]={{0,0,0},{l,0,0},{l,l,0},{0,l,0},{0,0,l},{l,0,l},{l,l,l},{0,l,l}};
  int i;
  for(i=0;i<8;i++)
  {
    glVertex3f(P[i].x,P[i].y,P[i].z);
    glVertex3f(l-P[i].x,P[i].y,P[i].z);
    glVertex3f(P[i].x,P[i].y,P[i].z);
    glVertex3f(P[i].x,l-P[i].y,P[i].z);
    glVertex3f(P[i].x,P[i].y,P[i].z);
    glVertex3f(P[i].x,P[i].y,l-P[i].z); //最初想到的是P[i].x+l再向%系统借力
  }
  
  glEnd();
  glPopMatrix();
  glFlush();
}
void draw4(void)
{
  glClear(GL_COLOR_BUFFER_BIT); 
  //设置画图使用的颜色 
  glClearColor(1.0,1.0,1.0,0.0); 
  //保存矩阵 
  glPushMatrix(); 
  //旋转, 如果不旋转，那些不同层次的点都重叠在一起，看不出3D效果了。 
  glRotatef(200.0f, 1.0f, 0.0f, 0.0f); 
  glRotatef(120.5f, 0.0f, 1.0f, 0.0f); 
  glBegin(GL_LINES);
  
  glVertex3f(0,0,-100);
  glVertex3f(0,0,100);
  glVertex3f(-100,0,0);
  glVertex3f(100,0,0);
  glVertex3f(0,-100,0);
  glVertex3f(0,100,0);
  
  glEnd();
  glPopMatrix();
  glFlush();
}
void draw5(void)
{
  glClear(GL_COLOR_BUFFER_BIT); 
  //设置画图使用的颜色 
  glClearColor(1.0,1.0,1.0,0.0); 
  //保存矩阵 
  glPushMatrix(); 
  //旋转, 如果不旋转，那些不同层次的点都重叠在一起，看不出3D效果了。 
  //glRotatef(200.0f, 1.0f, 0.0f, 0.0f); 
  //glRotatef(120.5f, 0.0f, 1.0f, 0.0f); 
  int n=1; //设置缩放倍数
  
  glBegin(GL_LINES);
  
  glVertex3f(0,0,-100);
  glVertex3f(0,0,100);
  glVertex3f(-100,0,0);
  glVertex3f(100,0,0);
  glVertex3f(0,-100,0);
  glVertex3f(0,100,0);
  
  if(L->next==NULL);
  else
  {
    LinkList p;
    p=L->next;
    while(p)
    {
      glVertex3f(p->data.x*n,p->data.y*n,p->data.z*n);
      //printf("%f,%f,%f\t",p->data.x*n,p->data.y*n,p->data.z*n); //float如果使用%d输入输出会出错
	  p=p->next;
    }
    printf("\n");
  }
  
  glEnd();
  glPopMatrix();
  glFlush();
}
void ChangeSize(GLsizei w, GLsizei h) 
{ 
  GLfloat nRange = 100.0f; 
  if(h == 0) 
  { 
    h = 1; 
  } 
  //设置视口 
  glViewport(0, 0, w, h); 
  glMatrixMode(GL_PROJECTION); 
  glLoadIdentity(); 
  //设置可视区域 
  GLfloat aspect = (GLfloat)w / (GLfloat)h; 
  if(w <= h) 
  { 
    glOrtho(-nRange, nRange, -nRange/aspect, nRange/aspect, -nRange, nRange); 
  } 
  else 
  { 
    glOrtho(-nRange*aspect, nRange*aspect, -nRange, nRange, -nRange, nRange); 
  } 
  glMatrixMode(GL_MODELVIEW); 
  glLoadIdentity(); 
} 
static void SetupRC() 
{ 
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f); 
} 
int OpenGL()
{
	//glutInit(&argc, argv);//对GLUT进行初始化，这个函数必须在其它的GLUT使用之前调用一次
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE); //设置显示方式
	glutInitWindowPosition(100, 100); 
	glutInitWindowSize(666, 666);
	glutCreateWindow("OpenGL"); //根据前面设置的信息创建窗口。参数将被作为窗口的标题
	SetupRC();
	glutDisplayFunc(draw5); //当需要画图时，请调用myDisplay函数
	glutReshapeFunc(ChangeSize);
	glutMainLoop(); //进行一个消息循环
	return 0;
}
