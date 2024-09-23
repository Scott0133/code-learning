// 优先权队列的实现
#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define OverFlow 2 // 上溢
#define UnderFlow 3 // 下溢
#define NotPresent 4 // 元素不存在
#define Duplicate 5 // 元素重复

typedef int BOOL;
typedef int ElemType;

typedef struct priorityQueue { // 优先权队列结构体
    ElemType *elements; // 存储元素的数组
    int n; // 优先权队列中元素的数量
    int maxSize; // 优先权队列的容量
}PriorityQueue;

void AdjustUp(ElemType heap[], int current);
void AdjustDown(ElemType heap[], int current, int border);
void CreatePQ(PriorityQueue *PQ, int mSize);
void Destroy(PriorityQueue *PQ);
BOOL IsEmpty(PriorityQueue *PQ);
BOOL IsFull(PriorityQueue *PQ);
int Size(PriorityQueue *PQ);
void Append(PriorityQueue *PQ, ElemType x);
void Serve(PriorityQueue *PQ, ElemType *x);
void PrintArr(PriorityQueue *PQ);

int main()
{
    int x; // 临时返回值
    int mSize = 100;
    PriorityQueue PQ;

    CreatePQ(&PQ, mSize); 
    Append(&PQ, 71); // 插入元素形成小根堆
    Append(&PQ, 74);
    Append(&PQ, 2);
    Append(&PQ, 72);
    Append(&PQ, 54);
    Append(&PQ, 93);
    Append(&PQ, 52);
    Append(&PQ, 28);
    PrintArr(&PQ);

    Serve(&PQ, &x); // 取出优先级最高的元素，利用参数x返回
    Serve(&PQ, &x);
    printf("\n");
    PrintArr(&PQ);

    return 0;
}


void AdjustUp(ElemType heap[], int current)
{
    int p = current;
    ElemType temp;
    while (p > 0) {
        if (heap[p] < heap [(p-1) / 2]) { // 若p指向元素小于其双亲结点，则与双亲结点交换
            temp = heap[p];
            heap[p] = heap[(p-1) / 2];
            heap[(p-1) / 2] = temp;
            p = (p-1) / 2; // 将p向上移动至当前考察元素的双亲结点位置
        } else { // 若p指向的元素不小于其双亲结点，则调整完毕
            break;
        }
    }
}
void AdjustDown(ElemType heap[], int current, int border)
{
    int p = current;
    int minChild;
    ElemType temp;
    while (2*p+1 <= border) { // 若p不是叶子结点则调整
        if ((2*p+2 <= border) && (heap[2*p+1] > heap[2*p+2])) {
            minChild = 2*p+2; // 右孩子存在，且较大，则minChild指向p的右孩子
        } else {
            minChild = 2*p+1; // 右孩子不存在，或较大，则minChild指向p的左孩子
        }
        if (heap[p] <= heap[minChild]) {
            break; // 若当前节点不大于其最小的孩子，则调整结束
        } else { // 否则将p和其最小的孩子交换
            temp = heap[p];
            heap[p] = heap[minChild];
            heap[minChild] = temp;
            p = minChild; // 设置下轮循环待考察的元素的位置（即当前下移元素的位置）
        }
    }
}
void CreatePQ(PriorityQueue *PQ, int mSize) // 创建一个空的优先权队列
{
    PQ->maxSize = mSize;
    PQ->n = 0;
    PQ->elements = (ElemType *)malloc(mSize*sizeof(ElemType));
}
void Destroy(PriorityQueue *PQ) // 销毁一个优先权队列，释放其占用的内存空间
{
    free(PQ->elements);
    PQ->n = 0;
    PQ->maxSize = 0;
}
BOOL IsEmpty(PriorityQueue *PQ) // 判断优先权队列是否为空
{
    if (PQ->n == 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}
BOOL IsFull(PriorityQueue *PQ) // 判断优先权队列是否已满
{
    if (PQ->n == PQ->maxSize) {
        return TRUE;
    } else {
        return FALSE;
    }
}
int Size(PriorityQueue *PQ) // 获取当前优先权队列中元素的数量
{
    return PQ->n;
}
void Append(PriorityQueue *PQ, ElemType x) // 在优先权队列中增加一个新元素x
{
    if (IsFull(PQ)) return;
    PQ->elements[PQ->n] = x;
    PQ->n++;
    AdjustUp(PQ->elements, PQ->n-1);
}
void Serve(PriorityQueue *PQ, ElemType *x) // 取出优先级最高的元素，利用参数x返回，并在优先权队列中删除该元素
{
    if (IsEmpty(PQ)) {
        return;
    }
    *x = PQ->elements[0];
    PQ->n--;
    PQ->elements[0] = PQ->elements[PQ->n];
    AdjustDown(PQ->elements, 0, PQ->n-1);
}
void PrintArr(PriorityQueue *PQ)
{
    for (int i=0; i<PQ->n; i++) {
        printf("%d ", PQ->elements[i]);
    }
}