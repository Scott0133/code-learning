//带头结点的链式队列
#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 2
#define ERROR -1

typedef int ElemType;
typedef struct LinkNode {           //链式队列结点
    ElemType data;
    struct LinkNode *next;
}LinkNode;

typedef struct {                    //链式队列
    LinkNode *front, *rear;         //队列的头指针尾指针
}LinkQueue;

void InitQueue(LinkQueue *Q);
int IsEmpty(LinkQueue Q);
void EnterQueue(LinkQueue *Q, ElemType x);
int DeleteQueue(LinkQueue *Q, ElemType *e);

int main()
{
    int e;
    LinkQueue Q;
    InitQueue(&Q);
    EnterQueue(&Q, 10);
    EnterQueue(&Q, 20);
    EnterQueue(&Q, 30);
    DeleteQueue(&Q, &e);
    EnterQueue(&Q, 40);

}

void InitQueue(LinkQueue *Q)
{
    Q->front = Q->rear = (LinkNode *)malloc(sizeof(LinkNode));
    Q->front->next = NULL;
}

int IsEmpty(LinkQueue Q)
{
    if (Q.front == Q.rear)
        return TRUE;
    else
        return FALSE;
}

void EnterQueue(LinkQueue *Q, ElemType x)
{
    LinkNode *s = (LinkNode *)malloc(sizeof(LinkNode));
    s->data = x;
    s->next = NULL;
    Q->rear->next = s;
    Q->rear = s;
}

int DeleteQueue(LinkQueue *Q, ElemType *e)
{
    if (Q->front == Q->rear)
        return FALSE;
    LinkNode *p = Q->front->next;
    (*e) = p->data;
    Q->front->next = p->next;
    if (Q->rear == p);
        Q->rear = Q->front;
    free(p);
    return TRUE;
}