//简单回顾链表，不考虑错误情况

#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100

typedef struct LNode {
    int data;
    struct LNode* next;
}LNode,*Linklist;

void InitList(Linklist *L);
void Insert(Linklist *L, int x);
void PrintList(Linklist L);

int main()
{
    Linklist L;
    InitList(&L);
    Insert(&L, 10);
    Insert(&L, 20);
    Insert(&L, 30);
    PrintList(L);
}

void InitList(Linklist *L)
{
    (*L) = (LNode *)malloc(MAXSIZE*sizeof(LNode));
    (*L)->next = NULL;
}

void Insert(Linklist *L, int x)
{
    LNode *temp = (LNode *)malloc(sizeof(LNode));
    temp->data = x;
    temp->next = (*L)->next;
    (*L)->next = temp;
}

void PrintList(Linklist L)
{
    LNode *p = L->next;
    while (p != NULL)
    {
        printf("%d ", p->data);
        p = p->next;
    }
}