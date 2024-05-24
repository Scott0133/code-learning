//顺序栈的表示
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

void InitStack_Test();
void InitStack(struct SqStack *S);
int StackEmpty(struct SqStack S);
int StackLength(struct SqStack S);
int ClearStack(struct SqStack S);
int DestroyStack(struct SqStack *S);
int Push(struct SqStack *S,int e);
int Pop(struct SqStack *S,int *e);
void PrintStack(struct SqStack S);

int main()
{
    struct SqStack S;

    struct SqStack S2;
    S2.base = (int*)malloc(MAXSIZE*sizeof(int));
    S2.top = S2.base;
    S2.stacksize = MAXSIZE;

    InitStack(&S);
    Push(&S,2);
    Push(&S,3);
    Push(&S,4);
    Push(&S,5);
    int e;
    Pop(&S,&e);
    printf("Poped element is %d\n",e);
    Pop(&S,&e);
    printf("Poped element is %d\n",e);
    PrintStack(S);
    printf("Stack Length is %d\n", StackLength(S));
}

void InitStack(struct SqStack *S) {                         //顺序栈初始化
    S->base = (int*)malloc(MAXSIZE*sizeof(int));
    S->top = S->base;
    S->stacksize = MAXSIZE;
}
int StackEmpty(struct SqStack S) {
    if (S.top == S.base)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
int StackLength(struct SqStack S)
{
    return S.top - S.base;
}
int ClearStack(struct SqStack S) {
    if (S.base)
    S.top = S.base;
    return OK;
}
int DestroyStack(struct SqStack *S) {
    if (S->base) {
        free (S->base);
        S->stacksize = 0;
        S->base = S->top = NULL;
    }
    return OK;
}
int Push(struct SqStack *S,int e) {
    if (S->top - S->base == S->stacksize)
        return ERROR;
    *(S->top) = e;
    S->top ++;
}
int Pop(struct SqStack *S,int *e) {
    if (S->top == S->base)
        return ERROR;
    S->top--;
    *e = *(S->top);
    return OK;
}
void PrintStack(struct SqStack S) {
    int *p;
    p = S.top - 1;
    printf("--top--\n");
    while (p >= S.base) {
        printf("%d\n", *p);
        p--;
    }
    printf("--base--\n");
}