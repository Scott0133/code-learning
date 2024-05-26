#include<stdio.h>
#include<stdlib.h>
#define TRUE 0;
#define FALSE 1;
#define ERROR -1;
typedef int ElemType;
typedef struct LNode {
    ElemType data;
    struct LNode *next;
}LNode, *LinkList;

//-----------------------------------------------------------------------------------
int Insert(LinkList *L, int i, ElemType e);     //在第i个位置插入结点e（带头结点）
int InitLinklist(LinkList *L);                  //初始化链表
int Empty(LinkList L);                          //判断链表是否为空
int Delete(LinkList *L, int i, ElemType *e);    //在第i个位置删除结点e，并传回e的值
LNode *LocateElem(LinkList L,ElemType e);       //按值查找，找到数据域==e的结点，return结构体指针的地址
int GetLength(LinkList L);                      //返回链表长度
void Print();                                   //顺序打印链表
int ReturnData_Pos(LinkList L, int x);          //返回链表元素位置，未找到则返回-1
//-----------------------------------------------------------------------------------

int main()
{
    LinkList L;
    int e;                  //声明e作为Delete()的返回值
    InitLinklist(&L);
    Insert(&L,1,10);
    Insert(&L,2,11);
    Insert(&L,3,12);
    Insert(&L,4,13);
    Insert(&L,5,14);
    //Delete(&L,2,&e);
    printf("now deleted element is %d\n", e);
    Print(L);
    printf("\npos is %d" ,ReturnData_Pos(L, 2));
}

int Insert(LinkList *L, int i, ElemType e)
{
    if(i<1)
        return FALSE;
    LNode *p = (*L);
        int j = 0;
        while (p != NULL && j<i-1)
        {
            p = p->next;
            j++;
        }
        if (p == NULL)
            return FALSE;
    LNode *temp = (LNode *)malloc(sizeof(LNode));          //申请新结点空间
    temp->data = e;
    temp->next = p->next;
    p->next = temp;
    return TRUE;
}
int InitLinklist(LinkList *L)
{
    (*L) = (LNode *)malloc(sizeof(LNode));
    if ((*L) == NULL)
        return FALSE;
    (*L)->next = NULL;
    return TRUE;
}
int Empty(LinkList L)
{
    if (L->next = NULL) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}
int Delete(LinkList *L, int i, ElemType *e)
{
    if (i<1)
        return FALSE;
    LNode *p = (*L);
        int j = 0;
        while (p != NULL && j<i-1)
        {
            p = p->next;
            j++;
        }
        if (p == NULL || p->next == NULL)
            return FALSE;
    LNode *q = p->next;
    (*e) = q->data;
    p->next = q->next;
    free(q);
    return TRUE;
}
LNode *LocateElem(LinkList L,ElemType e)
{
    LNode *p = L->next;
    while (p != NULL && p->data != e)
    {
        p = p->next;
    }
        return p;
}
int GetLength(LinkList L)
{
    int len = 0;
    LNode *p = L;
    while (p->next != NULL)
    {
        p = p->next;
        len++;
    }
    return len;
}
void Print(LinkList L)
{
    LNode *temp = L->next;
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
}
int ReturnData_Pos(LinkList L, int x)
{
    int i = 1;
    LNode *p = L->next;
    while (p->data != x)
    {
        p = p->next;
        i++;
        if(p->next == NULL)
            return ERROR;
    }
    return i;
}