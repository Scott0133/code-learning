// 单链表基本运算实现（不带头结点）

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
typedef struct singleList { // 单链表结构体
    Node *first; // 头指针
    int n; // 单链表中元素个数
} SingleList;

int Init(SingleList *L); // 单链表初始化
int Find(SingleList L, int i, Elemtype *x); // 单链表查找
int Insert(SingleList *L, int i, Elemtype x); // 单链表插入
int Delete(SingleList *L, int i); // 单链表删除
int Output(SingleList *L); // 单链表输出
void Destroy(SingleList *L); // 单链表撤销

int main()
{
    int i;
    int x;
    SingleList  L;
    Init(&L); // 初始化线性表
    for (i=0; i<9; i++) {
        Insert(&L, i-1, i); // 线性表中插入0-8
    }
    printf("the linklist is:");
    Output(&L);
    Delete(&L, 0); // 删除头结点
    printf("\nnow the linklist is:");
    Output(&L);
    Find(L, 0, &x);
    printf("\nthe value is:");
    printf("%d ",x);
    Destroy(&L); // 删除链表所有结点
    Output(&L);
}

int Init(SingleList *L) // 初始化单链表
{
    L->first = NULL; // 初始化头first指向NULL
    L->n = 0; // 初始化表长为0
    return OK;
}
int Find(SingleList L, int i, Elemtype *x) // 查找链表中数组下标i的元素，通过*x返回
{
    Node *p; // 定义临时结构体指针p
    int j;
    if (i<0 || i>L.n-1) { // 对i进行越界检查
        return ERROR;
    }
    p = L.first;
    for (j=0; j<i; j++) {
        p = p->link; // 从头结点开始查找元素
    }
    *x = p->element; // 通过*x返回元素
    return OK;
}
int Insert(SingleList *L, int i, Elemtype x) // 单链表插入，插入在链表任意处
{
    Node *p, *q; // 定义两个临时结构体指针p,q
    int j;
    if (i<-1 || i>L->n-1) { // 判断越界
        return ERROR;
    }
    p = L->first; // 指针p指向头结点
    for (j=0; j<i; j++) { // 从头结点开始查找元素
        p = p->link;
    }
    q = (Node *)malloc(sizeof(Node)); // 生成新结点q
    q->element = x; // 将x赋值给q->element
    if (i > -1) { // （i=-1，则插入在头结点之前，i>-1 将q所指向结点插入p所指向结点之后）
        q->link = p->link; // 新结点插入在p所指结点之后
        p->link = q;
    } else {
        q->link = L->first; // 新结点插入在头结点之前，成为新的头结点
        L->first = q;
    }
    L->n++; // 表长加一
    return OK;
}
int Delete(SingleList *L, int i) // 单链表元素删除，i为删除元素的下标
{
    int j;
    Node *p, *q; // 定义临时结构体指针p，q
    if (!L->n) { // 单链表为空
        return ERROR;
    }
    if (i<0 || i>L->n-1) { // i越界
        return ERROR;
    }
    q = L->first; // p，q都指向表头
    p = L->first;
    for (j=0; j<i-1; j++) { // 查找元素的直接前驱
        q = q->link;
    }
    if (i == 0) {
        L->first = L->first->link; //删除的是头结点
    } else {
        p = q->link; // p指向q的下一结点（p为释放的结点）
        q->link = p->link; // 从单链表中删除p所指向结点
    }
    free(p); // 释放p所指结点存储空间
    L->n--; // 表长减一
    return OK;
}
int Output(SingleList *L) // 单链表输出
{
    Node *p; // 定义临时结构体指针p
    if (!L->n) { // 表为空
        return ERROR;
    }
    p=L->first;
    while (p) // 当p的值不为NULL时
    {
        printf("%d ", p->element);
        p = p->link;
    }
    return OK;
}
void Destroy(SingleList *L) // 单链表撤销（删除链表中所有结点）
{
    Node *p;
    while (L->first) // 当L有first结点时
    {
        p = L->first->link; // 保存后继结点地址，防止“断链”
        free(L->first); // 释放first所指结点存储空间
        L->first = p; // first和p指向同一结点
    }
}