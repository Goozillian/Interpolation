#include <stdio.h>
#include <GL/glut.h>
#include "链表.h"
#include "OpenGL.h"
Point S,E; //起点和终点
int resume[3]={1,1,1}; //还原向量，这里原来用的bool，但由于后面设的值为-1所以出现了逻辑错误，所以找bug真是技术活，这个值得谨记
void swap(int &a,int &b)
{
  int temp;
  temp=a;
  a=b;
  b=temp;
}
int move_to_o(Point S,Point &E) //移动起点到原点
{
  E.x-=S.x;
  E.y-=S.y;
  E.z-=S.z;
  return 0;
}
int move_to_base(Point &E) //移动终点到第一象限
{
  if(E.x<0){E.x=-E.x;resume[0]=-1;}
  if(E.y<0){E.y=-E.y;resume[1]=-1;}
  if(E.z<0){E.z=-E.z;resume[2]=-1;}
  return 0;
}
int select(int order,Point p) //这种给结构体中的元素附加属性的技术是很有用的
{
  if(order==0)return p.x;
  else if(order==1)return p.y; //这里本来是默认order为1，2，3之这是之前设定，后来改为0，1，2后忘了改这里了，于是出现逻辑错误
  else return p.z;
}
int order[3]={0,1,2}; //顺序向量，这种给结构体中的元素附加属性的技术是很有用的，这里的设计似乎设计高层级抽象之多层转换之像抽象数组法
bool direction[3]; //方向向量，用以保存沿各坐标轴方向行进与否标志位
int allocation(Point E) //脉冲分配函数，也即插补函数
{
  Point location={0,0,0}; //当前坐标
  assign(location,S);
  int F[2],n;
  F[0]=F[1]=0,n=select(order[0],E);
  direction[order[0]]=1;
  //printf("%d\n",order[0]);
  bool skip[2]={0,0}; //为了配合流程图中的流程设立的步骤掠过标志位，这样就可以避免使用万劫不复的goto语句了
  ListInsert(L,location);
  while(n)
  {
    int i;
    for(i=0;i<2;i++)
    {
      if(!skip[i])F[i]=F[i]-select(order[0],E)+select(order[i+1],E); //这里本来错写为F1=F2-select(order[0])+select(order[1]);之这种非思维性错误是很难被发现的
      skip[i]=0; //复位是必要的之返回系统默认态
      //if(F[i]>0.5*select(order[0],E))direction[order[i+1]]=1;
      if(F[i]>=0)direction[order[i+1]]=1;
      else
      {
        direction[order[i+1]]=0;
        F[i]=F[i]+select(order[i+1],E);
        skip[i]=1;
      }
      //n--; 这个不能放在这里，否则n会变为负数则死循环
    }
    n--;
    location.x=location.x+direction[0]*resume[0]; //这里就没必要用direction[order[i+1]]了，毕竟会访问完
    location.y=location.y+direction[1]*resume[1];
    location.z=location.z+direction[2]*resume[2];
    ListInsert(L,location);
    ListInsert(L,location); //连续插入两次以驱动OpenGL
    //printf("%d\t",n); //其实输入输出语句是一种更便捷的调试手段
  }
  return 0;
}
int main(int argc,char *argv[])
{
  scanf("%f%f%f",&S.x,&S.y,&S.z);
  scanf("%f%f%f",&E.x,&E.y,&E.z);
  //printf("%f %f %f ",S.x,S.y,S.z);
  //判断三个坐标中哪个最大则哪个要分配的脉冲最多则脉冲间隔最短，而之后的算法都是依据脉冲间隔最短者做的，这需要形式化的处理，也算是基本功
  move_to_o(S,E);
  move_to_base(E);
  if(select(order[0],E)<select(order[1],E))swap(order[0],order[1]);
  if(select(order[0],E)<select(order[2],E))swap(order[0],order[2]);
  InitList(L);
  allocation(E);
  glutInit(&argc, argv);//对GLUT进行初始化，这个函数必须在其它的GLUT使用之前调用一次
  OpenGL();
  DestroyList(L);
  return 0;
}
