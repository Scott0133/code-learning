#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100
#define OK 10;
#define TRUE 1;
#define FALSE 2;
#define ERROR 3;

struct SqStack {
    int *base;
    int *top;
    int stacksize;
};

void InitStack(struct SqStack *S);

int main()
{
    struct SqStack S;
    InitStack(&S);
}

void InitStack(struct SqStack *S)
{
    S->base = (int *)malloc(MAXSIZE*sizeof(int));
    S->top = S->base;
    S->stacksize = MAXSIZE;
}