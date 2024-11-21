// 循环队列的实现
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
    ElemType *element; // 一维数组的数据类型为ElemType
} Queue;

void Init_Queue(Queue *Q, int maxsize);
void Destroy(Queue *Q);
int Is_Empty(Queue Q);
int Is_Full(Queue Q);
int Get_Front(Queue *Q, ElemType *x); // 获取队列头元素
int EnQueue(Queue *Q, ElemType x);
int DeQueue(Queue *Q);
void Clear(Queue *Q); // 清除队列全部元素，使队列恢复初始状态，但不释放空间
void Print_Queue(Queue Q);

int main()
{
    Queue Q;
    Init_Queue(&Q, 5);
    EnQueue(&Q, 10);
    EnQueue(&Q, 20);
    EnQueue(&Q, 30);
    DeQueue(&Q);
    Print_Queue(Q);
    return 0;
}

void Init_Queue(Queue *Q, int maxsize)
{
    Q->MaxSize = maxsize;
    Q->element = (ElemType *)malloc(Q->MaxSize*sizeof(ElemType));
    Q->front = Q->rear = 0;
}
void Destroy(Queue *Q)
{
    if (Q->element) {
        free(Q->element);
        Q->element = NULL;
    }
    Q->MaxSize = 0;
    Q->front = Q->rear = -1;
}
int Is_Empty(Queue Q)
{
    if (Q.front == Q.rear) {
        return TRUE;
    } else {
        return FALSE;
    }
}
int Is_Full(Queue Q)
{
    if ((Q.rear+1)%Q.MaxSize == Q.front) {
        return TRUE;
    } else {
        return FALSE;
    }
}
int Get_Front(Queue *Q, ElemType *x) // 会有潜在的front越界问题
{
    if (Is_Empty(*Q)) {
        return FALSE;
    }
    *x = Q->element[(Q->front+1) % Q->MaxSize];
    return TRUE;
}
int EnQueue(Queue *Q, ElemType x)
{
    if (Is_Full(*Q)) {
        return FALSE;
    }
    Q->rear = (Q->rear+1)%Q->MaxSize; // 尾指针移动
    Q->element[Q->rear] = x; // 插入队尾
    return TRUE;
}
int DeQueue(Queue *Q)
{
    if (Is_Empty(*Q)) {
        return FALSE;
    }
    Q->front = (Q->front+1)%Q->MaxSize; // 头指针移动
    return TRUE;
}
void Clear(Queue *Q)
{
    Q->front = Q->rear = 0;
}
void Print_Queue(Queue Q)
{
    int p = Q.front; // 利用p指针代替front指针，避免修改front的值
    while (p != Q.rear) {
        p = (p+1)%Q.MaxSize;
        printf("%d ", Q.element[p]);
    }
}