#include<stdio.h>
#include<stdlib.h>
#define OK 1;
#define ERROR 2;
//-------------------------------------------------------------------------------------------
typedef struct ElemType {
    char num[8];
    char name[8];
    int score;
}ElemType;

typedef struct LNode {
    ElemType data;                      //两个结构体数据类型，data存储数据，*next为指向结构体LNode的指针
    struct LNode *next;
}LNode,*LinkList;                       //LNode为创建的链表结点名，*LinkList为指向结点的一个指针，都为类型



void InitList_L(LinkList *L) {               //初始化链表,LinkList &L为C++指针引用，相当于LinkList *L
    (*L) = (LinkList)malloc(sizeof(LNode));
    (*L)->next = NULL;                       //头节点的指针域为空
    return OK;
}
/*
void InitList_L(LinkList &L) {        
    L = (LinkList)malloc(sizeof(LNode));
    L->next = NULL;                       
    return OK;
}
*/

int DestroyList_L(LinkList *L) {            //销毁链表
    LNode *p;
    while((*L) == NULL){
        p = (*L);
        (*L) = (*L)->next;
        free(p);
    }
    return OK;
}
/*
int DestroyList_L(LinkList &L) {            //销毁链表
    LNode *p;
    while(L == NULL){
        p = L;
        L = L->next;
        free(p);
    }
    return OK;
}
*/

int ListEmpty(LinkList L) {                 //判断链表是否为空
    if (L->next)            //非空
        return 0;
    else
        return 1;
}

int ClearList(LinkList L) {                //将L置为空表
    LNode *p,*q;
    p = L->next;
    while(p) {              //没到表尾
        q = p->next;
        free(p);
        p = q;
    }
    L->next = NULL;
    return OK;
}

int ListLength_L(LinkList L) {              //返回L中数据元素个数
    LNode *p;
    p = L->next;
    int i = 0;
    while(p) {
        i++;
        p = p->next;
    }
    return i;
}

int GetElem_L(LinkList L,int i,ElemType *e) {   //获取线性表L中某个数据元素内容，通过变量e返回
    LNode *p;
    int j = 1;
    p = L->next;
    while(p&&j<i) {
        p = p->next;
        ++j;
    }
    if(!p||j>i)
        return ERROR;
    (*e) = p->data;
    return OK;
}
/*
int *LocateElem_L(LinkList L,ElemType e) {
    LNode *p;
    p = L->next;
    int j = 1;
    wihle (p && p->data != e) {
        p = p->next;
        j++;
    }
    if (p)
    return j;
        return 0;
}
*/

int ListInsert_L(LinkList L,int i,ElemType e) {
    LNode *p;LNode *s;
    p = L;
    int j = 0;
    while(p && j < i-1) {
        p = p->next;
        ++j;
    }
    if (!p || j > i-1)
    return ERROR;
    s = (LNode*)malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;
    return OK;
}