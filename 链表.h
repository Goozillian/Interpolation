#include <stdlib.h>
typedef struct Point{
  float x;
  float y;
  float z;
}Point;
#define ElemType Point
#define OK 0
#define TRUE 1
#define FALSE 0
#define ERROR 1
typedef int Status;
typedef struct LNode{
  ElemType data; //与似Java将数据域定义成Object类是因为Object类是广义超类，任何类对象都可以给其赋值，增加了代码的通用性，那这个在C中应该也是可以模拟的。与所谓容器说之似统一参数表一样统一接口么之增加参数层级的兼容性，这是一种高层级的思想
  struct LNode *next;
}LNode,*LinkList;

extern void assign(Point &to,Point from);
extern Status InitList(LinkList &L);
extern Status DestroyList(LinkList &L);
extern Status ListInsert(LinkList &L,ElemType e);
