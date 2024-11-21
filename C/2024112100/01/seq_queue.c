// 普通队列的实现（会产生假溢出）
// 队列的顺序表示
    // 辅助数据结构：一维数组

#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0

typedef int ElemType;
typedef struct queue {
    int front;
    int rear;
    int MaxSize;
    int size; // 设定一个计数器，当计数器达到MaxSize为队列满
    ElemType *element; // 一维数组的数据类型为ElemType
} Queue;

int Init_Queue(Queue *Q, int maxsize); // 初始化数组
int EnQueue(Queue *Q, ElemType x); // 入队
int DeQueue(Queue *Q); // 出队
int Is_Full(Queue Q);
int Is_Empty(Queue Q);
void Print_Queue(Queue Q); // 打印顺序队列

int main()
{
    Queue Q;
    Init_Queue(&Q, 100);
    EnQueue(&Q, 10);
    EnQueue(&Q, 20);
    EnQueue(&Q, 30);
    DeQueue(&Q);
    Print_Queue(Q);

    free(Q.element);
    return 0;
}

int Init_Queue(Queue *Q, int maxsize)
{
    Q->MaxSize = maxsize;
    Q->element = (ElemType *)malloc(Q->MaxSize*sizeof(ElemType)); // 为一维数组分配空间
    Q->size = 0; // 队列的数据元素个数
    Q->front = Q->rear = 0;
    return TRUE;
}
int EnQueue(Queue *Q, ElemType x) // 插入首元素的下标从1开始
{
    if (Is_Full(*Q)) { // 若队列已满
        return FALSE;
    }
    Q->rear = Q->rear + 1;
    Q->element[Q->rear] = x;
    Q->size++;
    return TRUE;
}
int DeQueue(Queue *Q)
{
    if (Is_Empty(*Q)) {
        return FALSE;
    }
    Q->front = Q->front + 1;
    return TRUE;
}
int Is_Full(Queue Q)
{
    if (Q.MaxSize == Q.size) {
        return TRUE;
    } else {
        return FALSE;
    }
}
int Is_Empty(Queue Q)
{
    if (Q.size == 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}
void Print_Queue(Queue Q)
{
    if (Is_Empty(Q)) {
        return ;
    }
    int p = Q.front;
    while (p != Q.rear) {
        p++;
        printf("%d ", Q.element[p]);
    }
}