//queue(FIFO)
//循环队列

#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 10                  //定义队列中元素最大个数
#define TRUE 1
#define ERROR -1
#define FALSE 2

typedef int ElemType;
typedef struct {
    ElemType data[MAXSIZE];         //用静态数组存放队列元素
    int front,rear;                 //队头指针和队尾指针
}SqQueue;

void InitQueue(SqQueue *Q);
int QueueEmpty(SqQueue Q);
int EnterQueue(SqQueue *Q, ElemType x);
int DeleteQueue(SqQueue *Q, ElemType *e);
int GetHead(SqQueue Q, ElemType *e);        //获得队头元素的值，并用e返回
void PrintQueue(SqQueue Q);                               //打印队列数据

int main()
{
    int e;                  //返回值
    SqQueue Q;
    InitQueue(&Q);
    EnterQueue(&Q, 10);
    EnterQueue(&Q, 20);
    EnterQueue(&Q, 30);
    DeleteQueue(&Q, &e);
    printf("e is %d\n", e);
    EnterQueue(&Q, 40);
    PrintQueue(Q);
    return 0;

}

void InitQueue(SqQueue *Q)
{
    Q->rear = 0;
    Q->front  = 0;
}

int QueueEmpty(SqQueue Q)
{
    if (Q.rear == Q.front)
        return TRUE;
    else
        return FALSE;
} 

int EnterQueue(SqQueue *Q, ElemType x)
{
    if ((Q->rear + 1) % MAXSIZE == Q->front)
        return FALSE;
    Q->data[Q->rear] = x;
    Q->rear = Q->rear + 1;
        return TRUE;
}

int DeleteQueue(SqQueue *Q, ElemType *e)
{
    if (Q->rear == Q->front)
        return FALSE;
    (*e) = Q->data[Q->front];
    Q->front = (Q->front + 1)%MAXSIZE;
        return TRUE;
}

int GetHead(SqQueue Q, ElemType *e)
{
    if (Q.front == Q.rear)
        return FALSE;
    (*e) = Q.data[Q.front];
        return TRUE;
}

void PrintQueue(SqQueue Q)
{
    while (Q.front != Q.rear)
    {
        printf("%d ", Q.data[Q.front]);
        Q.front = Q.front + 1;
    }
}