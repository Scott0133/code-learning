// 堆栈的顺序表示

#include<stdio.h>
#include<stdlib.h>
#define FALSE 0
#define TRUE 1
#define OverFlow 2 // 上溢
#define UnderFlow 3 // 下溢
#define NotPresent 4 // 元素不存在
#define Duplicate 5 // 元素重复
typedef int Elemtype;
typedef struct stack { // 堆栈结构体的定义
    int top; // top为当前栈顶位置下标
    int maxSize; // maxSize-1为堆栈的最大栈顶位置下标
    Elemtype *element; // element为存储堆栈元素的一维数组首地址的指针
} Stack;

void Create(Stack *S, int mSize); // 创建一个能容纳mSize个单元的空堆栈
void Destroy(Stack *S); // 销毁一个已存在的堆栈，即释放堆栈占用的数组空间
int IsEmpty(Stack *S); // 判断堆栈是否为空，若为空返回TRUE，否则返回FALSE
int IsFull(Stack *S); // 判断堆栈是否已满，若是，则返回TRUE，否则返回FALSE
int Top(Stack *S, Elemtype *x); // 获取栈顶元素，通过x返回。返回栈顶元素
int Push(Stack *S, Elemtype x); // 在栈顶插入元素x（入栈）。若操作成功，则返回TRUE，否则返回FALSE
int Pop(Stack *S); // 删除栈顶元素（出栈）。若操作成功，则返回TRUE，否则返回FALSE
void Clear(Stack *S); // 清除堆栈中全部元素，但并不释放空间
void Print(Stack S); // 打印栈中元素

int main()
{
    Stack S; // 创建结构体变量S
    int x; // 返回变量
    Create(&S, 10); // 创建10大小的空堆栈
    printf("%d\n", IsEmpty(&S)); // 判断堆栈是否为空
    Push(&S, 1);
    Push(&S, 2);
    Push(&S, 3);
    Push(&S, 4);
    printf("Top element is %d\n", Top(&S, &x));
    Pop(&S);
    Print(S);

    return 0;
}

void Create(Stack *S, int mSize)
{
    S->maxSize = mSize;
    S->element = (Elemtype *)malloc(mSize*sizeof(Elemtype));
    S->top = -1;
}
void Destroy(Stack *S)
{
    S->maxSize = 0;
    free(S->element);
    S->top = -1;
}
int IsEmpty(Stack *S)
{
    return S->top == -1;
}
int IsFull(Stack *S)
{
    return S->top == S->maxSize - 1;
}
int Top(Stack *S, Elemtype *x)
{
    if (IsEmpty(S)) {
        return FALSE;
    }
    *x = S->element[S->top];
    return *x;
}
int Push(Stack *S, Elemtype x)
{
    if (IsFull(S)) {
        return FALSE;
    }
    S->top++;
    S->element[S->top] = x;
    return TRUE;
}
int Pop(Stack *S)
{
    if (IsEmpty(S)) {
        return FALSE;
    }
    S->top--;
    return TRUE;
}
void Clear(Stack *S)
{
    S->top = -1;
}
void Print(Stack S)
{
    while (S.top != -1) {
        printf("%d\n", S.element[S.top]);
        S.top--;
    }
}