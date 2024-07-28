//stack
#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAXSIZE 100 //最大栈容量

typedef struct { // 定义顺序栈
    int stacksize; // 栈数据
    int *top; //栈顶指针
    int *base; //栈底指针
}SqStack;

void InitStack(SqStack *S);
int Push(SqStack *S, int x); // 入栈
int Pop(SqStack *S, int *e); // 出栈，变量e返回

int main()
{
    // SqStack S;
    // InitStack(&S);
    // int e; //记录出栈变量
    // Push(&S, 2);
    // Push(&S, 3);
    // Pop(&S, &e);
    return 0;
}

void InitStack(SqStack *S)
{
    //SqStack *S = (SqStack *)malloc(MAXSIZE*sizeof(SqStack));
    //为栈分配内存
    S->base = (int *)malloc(MAXSIZE*sizeof(int)); // 为栈底指针分配MAXSIZE空间
    S->top = S->base;
    S->stacksize = MAXSIZE;
}

int Push(SqStack *S, int x)
{
    if (S->top - S->base == S->stacksize) //栈溢出
    {
        return FALSE;
    }
    *S->top = x;
    S->top = S->top + 1;
    return TRUE;
}

int Pop(SqStack *S, int *e)
{
    if (S->top == S->base) //栈空
    {
        return FALSE;
    }
    S->top = S->top - 1;
    *e = *S->top;
    return TRUE;
}
