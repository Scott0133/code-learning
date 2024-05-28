//stack v2 info
/*
注：未考虑错误输入情况
重写Print()
*/
#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100
#define OK 10
#define TRUE 1
#define FALSE 2
#define ERROR 3

struct SqStack {
    int *base;
    int *top;
    int stacksize;
};

void InitStack(struct SqStack *S);
int Push(struct SqStack *S, int x);
int Pop(struct SqStack *S, int *e);     //变量*e返回
void Print(struct SqStack S);           //rewrite

int main()
{
    struct SqStack S;
    int e;
    InitStack(&S);
    Push(&S, 10);
    Push(&S, 20);
    Push(&S, 30);
    Push(&S, 40);
    Pop(&S, &e);
    printf("now poped num is %d\n", e);
    Print(S);
}

void InitStack(struct SqStack *S)
{
    S->base = (int *)malloc(MAXSIZE*sizeof(int));
    S->top = S->base;
    S->stacksize = MAXSIZE;
}

int Push(struct SqStack *S, int x)
{
    *(S->top) = x;
    S->top = S->top + 1;
    return OK;
} 

int Pop(struct SqStack *S, int *e)
{
    S->top = S->top - 1;
    *e = *(S->top);
    return OK;
}

void Print(struct SqStack S)
{
    int *top = S.top;
    int *base = S.base;
    printf("top->\n");
    while (top > base)
    {
        printf("%d\n", *(top - 1));
        top = top - 1;
    }
    printf("base↑");
}