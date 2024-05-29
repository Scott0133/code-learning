//动态分配顺序表

#include<stdio.h>
#include<stdlib.h>
#include "mydef.h"
#define INITSIZE 10

typedef struct {
    ElemType *data;
    int MAXSIZE;
    int length;
}SqList;

void InitList(SqList *L);
void IncreaseSize(SqList *L, int len);      //增加动态数组的长度
void Insert(SqList *L, int i, int e);       //在i处插入元素e
void Print(SqList L);

int main()
{
    SqList L;
    InitList(&L);
    Insert(&L, 1, 10);
    Insert(&L, 1, 20);
    Insert(&L, 1, 30);
    Insert(&L, 3, 100);
    Insert(&L, 1, 40);
    Print(L);
    //IncreaseSize(&L, 5);
    //printf("%d, %d, %d, %d", L.data[0],L.data[1],L.data[2],L.data[3]);
}

void InitList(SqList *L)
{
    L->data = (ElemType *)malloc(INITSIZE*sizeof(ElemType));
    L->length = 0;
    L->MAXSIZE = INITSIZE;
}

void IncreaseSize(SqList *L, int len)
{
    int *p = L->data;
    L->data = (ElemType *)malloc((L->MAXSIZE+len)*sizeof(ElemType));
    for (int i=0; i<L->length; i++)
    {
        L->data[i] = p[i];
    }
    L->MAXSIZE = L->MAXSIZE + 1;
    free(p);
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

void Print(SqList L)
{
    int i = 0;
    while (L.length != 0)
    {
        printf("%d\n", L.data[i++]);
        L.length--;
    }
}