// 单链表基本运算（带头结点）

#include<stdio.h>
#include<stdlib.h>
typedef int Elemtype;
#define ERROR 0
#define OK 1
#define OverFlow 2 // 上溢
#define UnderFlow 3 // 下溢
#define NotPresent 4 // 元素不存在
#define Duplicate 5 // 元素重复
typedef struct node { // 单链表结点结构体
    Elemtype element; // 定义数据域
    struct node *link; // 定义指针域
} Node;
typedef struct headerList { // 头结点链表结构体
    Node *head; // 头结点指针
    int n; // 链表大小
} HeaderList;

int Init(HeaderList *L); // 初始化
int Insert(HeaderList *L, int i, Elemtype x); // 插入
int Delete(HeaderList *L, int i); // 删除
int Output(HeaderList *L); // 单链表输出

int main()
{
    int i;
    int x;
    HeaderList L;
    Init(&L);
    for (i=0; i<10; i++) {
        Insert(&L, i-1, i); //插入元素0~9
    }
    printf("the list is: ");
    Output(&L);
    Delete(&L, 3); // 删除数组下标3的元素
    printf("\nnow the list is: ");
    Output(&L);

    return 0;
}

int Init(HeaderList *L) // 链表初始化
{
    L->head = (Node*)malloc(sizeof(Node)); // 为头结点分配空间
    if (!L->head) {
        return ERROR;
    }
    L->head->link = NULL; // 设置单链表为空表
    L->n = 0;
    return OK;
}
int Insert(HeaderList *L, int i, Elemtype x) // 任意位置插入元素x
{
    Node *p, *q; // 临时结构体指针变量p，q
    int j;
    if (i<-1 || i>L->n-1) {
        return ERROR;
    }
    p = L->head; // 指针p指向头结点
    for (j=0; j<i+1; j++) { // 从头结点的下一个结点开始查找元素
        p = p->link;
    }
    q = (Node *)malloc(sizeof(Node)); // 生成新结点q
    q->element = x; // 将x赋值给q->element
    q->link = p->link; // q的下一结点指向p的下一结点
    p->link = q; // p的下一结点指向q
    L->n++; // 表长加一
    return OK;
}
int Delete(HeaderList *L, int i) // 单链表删除
{
    int j;
    Node *p, *q; // 定义临时结构体指针p，q
    if (!L->n) { // 单链表为空
        return ERROR;
    }
    if (i<0 || i>L->n-1) { // i越界
        return ERROR;
    }
    q = L->head; // q指向头结点
    for (j=0; j<i; j++) {
        q = q->link;
    }
    p = q->link;
    q->link = p->link;
    free(p);
    L->n--;
    return OK;
}
int Output(HeaderList *L) // 单链表输出
{
    Node *p; // 定义临时结构体指针p
    if (!L->n) { // 表为空
        return ERROR;
    }
    p = L->head->link; // p指向首个元素
    while (p != NULL) // 当p的值不为NULL时
    {
        printf("%d ", p->element);
        p = p->link;
    }
    return OK;
}