// 循环队列（模运算实现）

#include<stdio.h>
#include<stdlib.h>
#define FALSE 0
#define TRUE 1
#define OverFlow 2 // 上溢
#define UnderFlow 3 // 下溢
#define NotPresent 4 // 元素不存在
#define Duplicate 5 // 元素重复
typedef int Elemtype;
typedef struct queue {
    int front;
    int rear;
    int maxSize; // 队列实际容量为maxSize-1
    Elemtype *element;
} Queue;

void Create(Queue *Q, int mSize); // 创建一个能容纳mSize个单元的空队列
void Destroy(Queue *Q); // 销毁一个已存在的队列，即释放队列占用的数组空间
int IsEmpty(Queue *Q); // 判断队列是否为空，若是则返回TRUE，否则返回FALSE
int IsFull(Queue *Q); // 判断队列是否已满，若是则返回TRUE，否则返回FALSE
int Front(Queue *Q, Elemtype *x); // 获取队头元素，通过x返回。
int EnQueue(Queue *Q, Elemtype x); // 在队列Q的队尾插入元素x（入队）。操作成功返回TRUE，否则返回FALSE
int DeQueue(Queue *Q); // 从队列Q中删除队头元素（出队）。操作成功返回TRUE，否则返回FALSE
void Clear(Queue *Q); // 清除队列中全部元素，使队列恢复初始状态（Q->FRONT = Q->REAR = 0），但不释放空间
void Print(Queue Q); // 打印队列元素


int main()
{
    Queue Q; // 声明结构体变量Q
    Create(&Q, 5); // 初始化循环队列大小为5
    EnQueue(&Q, 20); //依次入队20、30、40、50
    EnQueue(&Q, 30);
    EnQueue(&Q, 40);
    EnQueue(&Q, 50);
    DeQueue(&Q);
    DeQueue(&Q);
    DeQueue(&Q);
    EnQueue(&Q, 60);
    EnQueue(&Q, 70);
    Print(Q);

    return 0;
}

void Create(Queue *Q, int mSize)
{
    Q->maxSize = mSize;
    Q->element = (Elemtype *)malloc(mSize*sizeof(Elemtype));
    Q->front = Q->rear = 0;
}
void Destroy(Queue *Q)
{
    Q->maxSize = 0;
    free(Q->element);
    Q->front = Q->rear = -1;
}
int IsEmpty(Queue *Q)
{
    return Q->front == Q->rear; // front和rear相等为空
}
int IsFull(Queue *Q)
{
    return (Q->rear+1) % Q->maxSize == Q->front; // rear在front的后面，则循环队列已满
}
int Front(Queue *Q, Elemtype *x)
{
    if (IsEmpty(Q)) {
        return FALSE;
    }
    *x = Q->element[(Q->front+1) % Q->maxSize];
    return TRUE;
}
int EnQueue(Queue *Q, Elemtype x)
{
    if (IsFull(Q)) {
        return FALSE;
    }
    Q->rear = (Q->rear+1) % Q->maxSize; // 入队front指针移动
    Q->element[Q->rear] = x;
    return TRUE;
}
int DeQueue(Queue *Q)
{
    if (IsEmpty(Q)) {
        return FALSE;
    }
    Q->front = (Q->front+1) % Q->maxSize; // 出队rear指针移动
    return TRUE;
}
void Clear(Queue *Q)
{
    Q->front = Q->rear = 0;
}
void Print(Queue Q)
{
    Q.front++; // front指向元素置空
    while (Q.rear != Q.front) {
        printf("%d ", Q.element[Q.front]); // 从队首到队尾-1依次列出元素
        Q.front = (Q.front+1) % Q.maxSize;
        if (Q.front == Q.rear) {
            printf("\nThe rear element is %d", Q.element[Q.rear]); // 队尾元素
        }
    }
}