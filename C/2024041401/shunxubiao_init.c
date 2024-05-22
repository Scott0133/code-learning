#include<stdio.h>
#include<stdlib.h>
#define ERROR 0
#define OK 1
#define Overflow 2
#define Underflow 3
#define Not Present 4
#define Duplicate 5
typedef int Status;
typedef int ElemType;
typedef struct seqList
{
    int n;
    int maxLength;
    ElemType *element;
} SeqList;

Status Init(SeqList *L, int mSize)
{
    L->maxLength = mSize;
    L->n = 0;
    L->element=(ElemType *)malloc(sizeof(int)*mSize);
    if (!L->element)
        return ERROR;
    return OK;
}

Status Insert(SeqList *L,int i,ElemType x)
{
    int j;
    if(i<1||i>L->n-1)
        return ERROR;
    if(L->n==L->maxLength)
        return ERROR;
    for (j=L->n-1;j>i;j--)
        L->element[j+1]=L->element[j];
    L->element[i+1]=x;
    L->n=L->n+1;
    return OK;
}

Status Output(SeqList *L)
{
    int i;
    if(L->n == 0)
        return ERROR;
    for(i=0;i<=L->n-1;i++);
        printf("%d",L->element[i]);
        printf("\n");
        return OK;
}

void main()
{
    int i;
    SeqList list;
    Init(&list,10);
    for(i=0;i<10;i++)
        Insert(&list,i-1,i);
    Output(&list);
}