#include<stdio.h>
#include<stdlib.h>
#define OK 1;
#define ERROR 2;
//-------------------------------------------------------------------------------------------

typedef struct LNode {
    int data;                      //两个结构体数据类型，data存储数据，*next为指向结构体LNode的指针
    struct LNode *next;
}LNode,*LinkList;                       //LNode为创建的链表结点名，*LinkList为指向结点的一个指针，都为类型
                                        //LinkList为链表类型

int InitList_L(LinkList *L);
int DestroyList_L(LinkList *L);
int ListEmpty(LinkList L);
int ClearList(LinkList L);
int ListLength_L(LinkList L);
int GetElem_L(LinkList L,int i,int *e);
int ListInsert_L(LinkList L,int i,int e);

int main()
{
    LinkList L;

    InitList_L(&L);
    ListInsert_L(L,3,3);
    return 0;
}

int InitList_L(LinkList *L) {               //L是二级指针
    (*L) = (LinkList)malloc(sizeof(LNode));
    (*L)->next = NULL;                       //头节点的指针域为空
    return OK;
}

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

int GetElem_L(LinkList L,int position,int *e) {   //获取线性表L中某个数据元素内容，通过变量e返回
    LinkList p = L->next;
    int i = 1;
    if (position < 1 || !p)
        return ERROR;
    while (p && i < position)
    {
        p = p->next;
        i++;
    }
    *e = p->data;

    return OK;
}

LinkList LocateElem_L(LinkList L,int e) {
    LinkList p = L->next;
    while (p && p->data != e) {
        p = p->next;
    }
    if (!p)
        return NULL;
    return p;
}

int ListInsert_Data(LinkList L,int position,int e)     //在表L中指定位置插入数据e
{
    LinkList p = L;
    int i = 0;
    while (p && i < position - 1)
    {
        i++;
        p = p->next;
    }
    if (!p || i > position - 1)
        return ERROR;
    LinkList pnew = (LinkList)malloc(sizeof(LNode));
    pnew->data = e;
    pnew->next = p->next;
    p->next = pnew;

    return OK;
}

int Delete_Data(LinkList L,int position,int *e)         //删除L中指定元素，通过e返回
{
    LinkList p = L;
    int i = 0;

    while (p && i < position - 1)
    {
        i++;
        p = p->next;
    }
    if (i > position - 1 || !p || !p->next)
        return ERROR;
    
    LinkList pfree = p->next;
    *e = pfree->data;
    p->next = pfree->next;
    free(pfree);
    
    return OK;
}
