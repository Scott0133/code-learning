//未考虑错误情况
#include"define.h"
#include<stdio.h>
#include<stdlib.h>

typedef struct LNode {
    int data;
    struct LNode *next;
}LNode, *LinkList;

void InitList(LinkList *L);
int Insert(LinkList *L, int x);     //头插法插入一个元素
int Delete(LinkList *L, int x, int *e);     //删除指定位置节点,返回值
void PrintLinkList(LinkList L);

int main()
{
    int e;
    LinkList L;
    InitList(&L);
    Insert(&L, 10);
    Insert(&L, 20);
    Insert(&L, 30);
    Delete(&L, 2, &e);
    printf("now deleted num is %d\n", e);
    PrintLinkList(L);

}

void InitList(LinkList *L)
{
    (*L) = (LNode *)malloc(sizeof(LNode));
    (*L)->next = NULL;
}

int Insert(LinkList *L, int x)
{
    LNode *temp = (LNode *)malloc(sizeof(LNode));
    temp->data = x;
    temp->next = (*L)->next;
    (*L)->next = temp;
    return TRUE;
}

int Delete(LinkList *L, int x, int *e)
{
    int i;
    LNode *p = (*L);
    LNode *q;
    for (i=1; i<x; i++)
    {
        p = p->next;
    }
    (*e) = p->next->data;
    q = p->next;
    p->next = q->next;
    free(q);
}

void PrintLinkList(LinkList L)
{
    LNode *temp = L;
    while (temp->next != NULL)
    {
        printf("%d ", temp->next->data);
        temp = temp->next;
    }
}