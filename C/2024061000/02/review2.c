//回顾stack

#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100
struct SqStack {
    int *base;
    int *top;
    int stacksize;
};

void InitSqStack(struct SqStack *S);
void Push(struct SqStack *S, int x);
void Pop(struct SqStack *S, int *e);
void PrintStack(struct SqStack S);

int main()
{
    struct SqStack S;
    int e;
    InitSqStack(&S);
    Push(&S, 10);
    Push(&S, 20);
    Push(&S, 30);
    Push(&S, 40);
    Push(&S, 50);
    Pop(&S, &e);
    printf("now poped num is %d\n", e);
    Pop(&S, &e);
    printf("now poped num is %d\n", e);
    PrintStack(S);
}

void InitSqStack(struct SqStack *S)
{
    S->base = (int *)malloc(MAXSIZE*sizeof(int));
    S->top = S->base;
    S->stacksize = MAXSIZE;
}

void Push(struct SqStack *S, int x)
{
    *(S->top) = x;
    S->top++;
}

void Pop(struct SqStack *S, int *e)
{
    S->top--;
    *e = *(S->top);
}

void PrintStack(struct SqStack S)
{        
    printf("↓---top---\n");
    while(S.base != S.top)
    {
        printf("%d\n", *(S.top - 1));
        S.top--;
    }
    printf("↑---base---");
}