#include<stdio.h>
#include<stdlib.h>
#include "mydef.h"
#define SIZE 100

typedef struct LNode {
    int data;
    struct LNode *next;
}LNode, *Linklist;

void InitList(Linklist *L);

int main()
{
    Linklist L;
    InitList(&L);
    return 0;
}

void InitList(Linklist *L)
{
    (*L) = (LNode *)malloc(sizeof(LNode));
    (*L)->next = NULL;

}