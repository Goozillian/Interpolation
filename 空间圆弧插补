#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include "链表.h"
#include "OpenGL.h"
Point S,E; //起点和终点
Point M; //圆上一点
Point SM,ME; //向量
Point Vorg; //圆心处单位法向量
Point O; //圆心坐标，但圆心坐标有可能不是整数，则与其把Point定义为浮点型或为圆心单独设立一个数据结构，不如使用偏差向量保存偏差值，这种做法实在绝妙。不过想想还是修改Point定义为浮点型吧一了百了
//float R_offset[3]={0,0,0}; //偏差向量
int AB(Point A,Point B,Point &C) //两个点确定一个向量。不用自己写出表达式之借助引擎自动生成，架设好基础系统后问题就越来越好办了，尤其基础系统还有基础系统之循重，所谓深度学习其实也是这样之亦系统论，这也是基础研究意义的体现
{
  C.x=B.x-A.x;
  C.y=B.y-A.y;
  C.z=B.z-A.z;
  return 0;
}
int AxB(Point A,Point B,Point &C) //向量积
{
  C.x=A.y*B.z-A.z*B.y;
  C.y=A.z*B.x-A.x*B.z;
  C.z=A.x*B.y-A.y*B.x;
  return 0;
}
float lenAB(Point A,Point B)
{
  return sqrt(pow(B.x-A.x,2)+pow(B.y-A.y,2)+pow(B.z-A.z,2));
}
void genVorg() //AxB=(AyBz-AzBy)i+(AzBx-AxBz)j+(AxBy-AyBx)k
{
  //M-S=(M.x-S.x,M.y-S.y,M.z-S.z);E-M=(E.x-M.x,E.y-M.y,E.z-M.z)
  AB(S,M,SM);
  AB(M,E,ME);
  AxB(SM,ME,Vorg);
  Point origin={0,0,0};
  float l=lenAB(origin,Vorg);
  Vorg.x/=l;
  Vorg.y/=l;
  Vorg.z/=l; //就是少了变为单位向量的这几步所以程序逻辑出错，bug真是博大精深
}
void solution_of_three_variable_linear_equations(float *a,float *b,float *c,float *d,Point &C) //三元一次方程组通解
{
  C.x=-((b[2]*c[1]*d[0] - b[1]*c[2]*d[0] - b[2]*c[0]*d[1] + b[0]*c[2]*d[1] + b[1]*c[0]*d[2] - b[0]*c[1]*d[2])/(a[2]*b[1]*c[0] - a[1]*b[2]*c[0] - a[2]*b[0]*c[1] + a[0]*b[2]*c[1] + a[1]*b[0]*c[2] - a[0]*b[1]*c[2]));
  C.y=-((-(a[2]*c[1]*d[0]) + a[1]*c[2]*d[0] + a[2]*c[0]*d[1] - a[0]*c[2]*d[1] - a[1]*c[0]*d[2] + a[0]*c[1]*d[2])/(a[2]*b[1]*c[0] - a[1]*b[2]*c[0] - a[2]*b[0]*c[1] + a[0]*b[2]*c[1] + a[1]*b[0]*c[2] - a[0]*b[1]*c[2]));
  C.z=-((a[2]*b[1]*d[0] - a[1]*b[2]*d[0] - a[2]*b[0]*d[1] + a[0]*b[2]*d[1] + a[1]*b[0]*d[2] - a[0]*b[1]*d[2])/(a[2]*b[1]*c[0] - a[1]*b[2]*c[0] - a[2]*b[0]*c[1] + a[0]*b[2]*c[1] + a[1]*b[0]*c[2] - a[0]*b[1]*c[2]));
}
int midAB(Point A,Point B,Point &C) //线段中点
{
  C.x=(A.x+B.x)/2;
  C.y=(A.y+B.y)/2;
  C.z=(A.z+B.z)/2;
  return 0;
}
void genO()
{
  Point P,Q;
  midAB(S,M,P);
  midAB(M,E,Q);
  float a[3]={-SM.x,-ME.x,-Vorg.x};
  float b[3]={-SM.y,-ME.y,-Vorg.y};
  float c[3]={-SM.z,-ME.z,-Vorg.z};
  float d[3]={SM.x*P.x+SM.y*P.y+SM.z*P.z,ME.x*Q.x+ME.y*Q.y+ME.z*Q.z,Vorg.x*S.x+Vorg.y*S.y+Vorg.z*S.z};
  solution_of_three_variable_linear_equations(a,b,c,d,O);
}
float AoB(Point A,Point B) //数量积
{
  return A.x*B.x+A.y*B.y+A.z*B.z;
}
float genTheta(Point location)
{
  Point OE,Olocation;
  AB(O,E,OE);
  AB(O,location,Olocation);
  return acos(AoB(OE,Olocation)/(lenAB(O,E)*lenAB(O,location)));
}
float abs(float a)
{
  if(a<0)return -a;
  else return a;
}
float threshold=0.1; //终点判断阈值，这个似乎要由起点终点动态确定
int allocation() //脉冲分配函数，也即插补函数。由于曲线皆有切线，切线就是速度，速度就是运动趋势，所以似乎矢量法很有前途，样条曲线似乎自带切线所以用得很普遍，这也是同一个原理
{
  Point location; //当前坐标
  assign(location,S);
  float R=lenAB(O,S); //半径，不应直接给出圆心，因为法向量需要圆弧上的一点来确定方向
  float Jx,Jy,Jz,Jrx,Jry,Jrz,a,b,c,theta,Ii,Ji,Ki;
  Jrx=Jry=Jrz=0;
  a=Vorg.x,b=Vorg.y,c=Vorg.z;
  Ii=location.x-O.x,Ji=location.y-O.y,Ki=location.z-O.z;
  theta=genTheta(location);
  ListInsert(L,location);
  printf("%f\n",R);
  printf("%f %f %f\n",O.x,O.y,O.z);
  printf("%f=%f=%f",lenAB(O,S),lenAB(O,E),lenAB(O,M));
  while(1){//break;
  Jx=abs(b*Ki-c*Ji),Jy=abs(c*Ii-a*Ki),Jz=abs(a*Ji-b*Ii);
  Jrx+=Jx,Jry+=Jy,Jrz+=Jz;
  
  Point di,Olocation;
  AB(O,location,Olocation);
  AxB(Vorg,Olocation,di);
  
  if(Jrx>=R)
  {
    Jrx-=R;
    if(di.x!=0)
    {
      Ii+=di.x/abs(di.x);
      location.x+=di.x/abs(di.x);
    }
  }
  if(Jry>=R)
  {
    Jry-=R;
    if(di.y!=0)
    {
      Ji+=di.y/abs(di.y);
      location.y+=di.y/abs(di.y);
    }
  }
  if(Jrz>=R)
  {
    Jrz-=R;
    if(di.z!=0)
    {
      Ki+=di.z/abs(di.z);
      location.z+=di.z/abs(di.z);
    }
  }
  ListInsert(L,location);
  ListInsert(L,location);
  float theta_temp=genTheta(location);
  if(theta_temp<theta&&theta_temp<threshold)break;
  else theta=theta_temp;
  //printf("%f %f %f ",location.x,location.y,location.z);
  //printf("%f\t",theta);
  //break;
  }
  return 0;
}
int main(int argc,char *argv[])
{
  scanf("%f%f%f",&S.x,&S.y,&S.z);
  scanf("%f%f%f",&E.x,&E.y,&E.z);
  scanf("%f%f%f",&M.x,&M.y,&M.z);
  //输入时要确保S、E、M互不重合，之毕竟三点才能确定一个圆
  InitList(L);
  genVorg();
  genO();
  allocation();
  glutInit(&argc, argv);//对GLUT进行初始化，这个函数必须在其它的GLUT使用之前调用一次
  OpenGL();
  DestroyList(L);
  return 0;
}
