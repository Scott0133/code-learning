#include<stdio.h>
#include<stdlib.h>
#define ERROR 0;
#define OK 1;

typedef int ElemType;

typedef struct SeqList
{
    int n;
    int MaxLength;
    ElemType *element;
}SeqList;


typedef int Status;

Status Init(SeqList *L,int mSize)
{
    L->MaxLength = mSize;
    L->n = 0;
    L->element = (ElemType*)malloc(sizeof(ElemType)*mSize);
    if (!L->element)
    {
        return ERROR;
    }
    else
    {
        return OK;
    }
}

int main()
{
    SeqList L;
    Init(&L,10);
}

