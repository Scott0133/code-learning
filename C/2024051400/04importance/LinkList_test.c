#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
}LNode,*LinkList;

void Change_point(LinkList *p);
void NotChange_point(LinkList p);

int main()
{
    LinkList L;
    L = (LinkList)malloc(sizeof(LNode));
    L->data = 1;
    L->next = NULL;
    printf("L指向地址为:%p\n",L);
    printf("L指向data为:%d\n",L->data);
    printf("存储L的地址为:%p\n",&L);
    NotChange_point(L);
    printf("现在main()函数中L指向data为:%d\n",L->data);
    Change_point(&L);
    printf("现在main()函数中L指向data为:%d\n",L->data);
    return 0;
}

void Change_point(LinkList *L)
{
    printf("L指向地址为:%p\n",L);
    printf("存储L的地址为:%p\n",&L);
    *L = (LinkList)malloc(sizeof(LNode));
    (*L)->data = 2;
    (*L)->next = NULL;
}
void NotChange_point(LinkList L)
{
    printf("函数NotChange_point L (未改)地址为:%p\n",L);
    printf("L指向data为:%p\n",L->data);
    printf("存储L的地址为:%p\n",&L);
    L = (LinkList)malloc(sizeof(LNode));
    L->data = 2;
    L->next = NULL;
    printf("现在L(改)指向的地址为:%p\n",L);
    printf("L指向的data为:%d",L->data);
    printf("存储L的地址为:%p\n",&L);
}