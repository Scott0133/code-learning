//v2 info
//封装int ListInsert()
//LinkList————head
#include<stdio.h>
#include<stdlib.h>
#include "mydef.h"

typedef struct LNode {
    int data;
    struct LNode* next;
}LNode, *LinkList;

int InitList(LinkList *L);                          //初始化单链表（带头结点）
int ListInsert(LinkList *L, int i, ElemType e);     //在表L第i个位置插入元素e（头插法）
int InsertNextNode(LNode *p, ElemType e);           //（表存在）尾插法，插入在p节点之后
int InsertPriorNode(LNode *p, ElemType e);          //（表存在）前插法，插入在p节点之前（仅交换前后值）
int ListDelete(LinkList *L, int i,int *e);          //在表L第i个位置删除节点，并用e的值返回
int DeleteNode(LNode *p);                           //（表存在）删除指定节点p
LNode *GetElem(LinkList L, int i);                  //按位查找，返回第i个元素
LNode *LocateElem(LinkList L, ElemType e);          //按值查找，找到数据域 == e的节点（ElemType为int类型）
int Length(LinkList L);                             //求表长
void Print(LinkList L);                             //打印链表元素

int main()
{
    LinkList L;
    int e;                       //声明返回值e
    InitList(&L);
    ListInsert(&L, 1, 10);
    ListInsert(&L, 1, 20);
    ListInsert(&L, 3, 30);
    ListInsert(&L, 1, 40);
    Print(L);
}

int InitList(LinkList *L)
{
    (*L) = (LNode *)malloc(sizeof(LNode));
    if ((*L) == NULL)
        return FALSE;
    (*L)->next = NULL;
    return TRUE;
}

int ListInsert(LinkList *L, int i, ElemType e)
{
    if (i < 1)
        return FALSE;
    LNode *p = GetElem((*L), i-1);
    return InsertNextNode(p, e);
}

int InsertNextNode(LNode *p, ElemType e)
{
    if (p == NULL)
        return FALSE;
    LNode *temp = (LNode *)malloc(sizeof(LNode));       //下与ListInsert()相同，可封装
    if (temp == NULL)                                   //内存分配失败
        return FALSE;
    temp->data = e;
    temp->next = p->next;
    p->next = temp;
}

int InsertPriorNode(LNode *p, ElemType e)
{
    if(p == NULL)
        return FALSE;
    LNode *temp = (LNode *)malloc(sizeof(LNode));
    if (temp == 0)
        return FALSE;
    temp->next = p->next;
    p->next = temp;
    temp->data = p->data;
    p->data = e;
}

int ListDelete(LinkList *L, int i,int *e)
{
    if (i < 1)
        return FALSE;
    LNode *p;       
    int j = 0;                  //当前p指向的是第几个结点
    p = (*L);                   //L指向头结点，头结点不存数据
    while (p!=NULL && j<i-1) {  //循环找到i-1个结点
        p = p->next;
        p++;
    }
    if (p == NULL)              //i值不合法
        return FALSE;
    if (p->next == NULL)
        return FALSE;
    LNode *del = p->next;       //del指向被删除的节点
    (*e) = del->data;           //用e返回元素值
    p->next = del->next;        //将*del节点从链断开
    free(del);                  //释放节点存储空间
    return TRUE;
}

int DeleteNode(LNode *p)        //注：若p为最后节点，会出现空指针错误
{
    if (p == NULL)
        return FALSE;
    LNode *del = p->next;       //del指向*p的后继节点
    p->data = p->next->data;    //和后继节点交换数据域
    p->next = del->next;        //将*del节点从链断开
    free(del);                  //释放后继节点存储空间
    return TRUE;
}

LNode *GetElem(LinkList L, int i)
{
    /*
    if (i < 0)
        return FALSE;
    */
    LNode *p;
    int j =0;                       ////当前p指向的是第几个结点
    p = L;                          //L指向头结点
    while (p != NULL && j<i)        //找到第i个节点
    {
        p = p->next;
        j++;
    }
    return p;
}

LNode *LocateElem(LinkList L, ElemType e)
{
    LNode *p = L->next;                             //从第一个节点开始查找
    while (p != NULL && p->data != e)
    {
        p = p->next;
    }
    return p;                                       //找到后返回该节点指针，否则返回NULL
}

int Length(LinkList L)
{
    int len = 0;
    LNode *p = L;
    while (p->next != NULL)
    {
        p = p->next;
        len++;
    }
    return len;
}

void Print(LinkList L)
{
    LNode *p = L->next;
    while (p != NULL)
    {
        printf("%d ", p->data);
        p = p->next;
    }
}