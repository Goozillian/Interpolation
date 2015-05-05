#include "链表.h"
void assign(Point &to,Point from)
{
  to.x=from.x;
  to.y=from.y;
  to.z=from.z;
}
Status InitList(LinkList &L)
{
  L=(LinkList)malloc(sizeof(LNode));
  L->next=NULL; //先建立一个带头结点的单链表
  return 0;
}
Status DestroyList(LinkList &L)
{ /* 初始条件：线性表L已存在。操作结果：销毁线性表L */
  LinkList q;
  if(L==NULL)return 1;
  while(L)
  {
    q=(L)->next;//这样写是说明->的用法
    free(L);
    L=q;
  }
  return 0;
}
Status ListInsert(LinkList &L,ElemType e)
{
  //在带头结点的单链线性表L中第i个位置之前插入元素e
  LinkList p=L;
  LinkList q=L->next;
  while(q){p=p->next;q=q->next;} //寻找第i-1个结点
  LinkList s=(LinkList)malloc(sizeof(LNode)); //生成新结点
  assign(s->data,e);s->next=NULL;
  p->next=s;
  return OK;
}
