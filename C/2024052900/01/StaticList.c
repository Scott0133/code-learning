//静态分配顺序表

#include<stdio.h>
#include"mydef.h"
#define MAXSIZE 10

typedef struct {
    ElemType data[MAXSIZE];
    int length;
}SqList;

void InitList(SqList *L);
void Insert(SqList *L, int i, int e);

int main()
{
    SqList L;
    InitList(&L);
    Insert(&L, 1, 10);
    Insert(&L, 1, 20);
    Insert(&L, 1, 30);
    Insert(&L, 1, 40);

    return 0;
}

void InitList(SqList *L)
{
    for (int i =0; i<MAXSIZE; i++)
    {
        L->data[i] = 0;
    }
    L->length = 0;
}

void Insert(SqList *L, int i, int e)
{
    for (int j=L->length; j>=i; j--)
    {
        L->data[j] = L->data[j-1];
    }
    L->data[i-1] = e;
    L->length++;
}
