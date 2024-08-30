// 双向链表

#include<stdio.h>
#include<stdlib.h>
typedef int Elemtype;
#define ERROR 0
#define OK 1
#define OverFlow 2 // 上溢
#define UnderFlow 3 // 下溢
#define NotPresent 4 // 元素不存在
#define Duplicate 5 // 元素重复
typedef struct duNode {
    Elemtype elemtype; // 结点的数据域
    struct duNode *llink; // 创建左右指针域
    struct duNode *rlink;
} DuNode;
typedef struct duList { // 头结点链表结构体
    DuNode *first; // 指向链表的初始结点
    int n; // 链表大小
} DuList;

int Init(DuList *L); // 初始化双向链表
int Insert(DuList *L, int i, int x); // 双向链表的插入
int Delete();

int main()
{

}

int Init(DuList *L)
{
    L->first = (DuNode *)malloc(sizeof(DuNode));
    if (!L->first) {
        return ERROR;
    }
    L->first->llink = NULL; // 初始化左右指针
    L->first->rlink = NULL;
    L->n = 0;
    return OK;
}