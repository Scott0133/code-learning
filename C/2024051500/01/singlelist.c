#include<stdio.h>
#include<stdlib.h>

typedef int ElemType;


typedef struct Node {
    ElemType data;           //结点的数据域
    struct Node *next;       //结点的指针域
}Node;

typedef struct HeaderList {
    Node *head;              //头指针
    int n;                   //链表中元素个数
}HeaderList;

int Init(HeaderList *h);