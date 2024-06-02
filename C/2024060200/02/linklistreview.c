//未考虑错误情况
/*
debug分析（某次运行）：
函数Insert(LinkList *L, int x)中
    L地址为0x61fe18
    *L地址为0x731590
函数Print(LinkList L)中
    L地址为0x731590
*/
#include<stdio.h>
#include<stdlib.h>
#include "mydef.h"

typedef struct LNode {
    ElemType data;
    struct LNode *next;
}LNode, *LinkList;

void InitList(LinkList *L);                 //初始化链表
int Insert(LinkList *L, int x);      //仅在表L的首端处插入x元素
void Print(LinkList L);

int main()
{
    LinkList L;
    InitList(&L);
    Insert(&L, 10);
    Insert(&L, 20);
    Insert(&L, 30);

    Print(L);
    return 0;
}

void InitList(LinkList *L)
{
    (*L) = (LNode *)malloc(sizeof(LNode));
    (*L)->data = 0;
    (*L)->next = NULL;
}

int Insert(LinkList *L, int x)
{
    LNode *temp = (LNode *)malloc(sizeof(LNode));
    LNode *p = (*L);                                //用p指向头结点
    temp->data = x;
    temp->next = p->next;
    p->next = temp;
}

void Print(LinkList L)
{
    LNode *q = L;
    while (q->next != NULL)
    {
        q = q->next;
        printf("%d ", q->data);       //q->next为首元结点地址
    }
}
