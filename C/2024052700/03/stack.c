//用结构体实现stack
//注：stack中的top和base需要记录返回值，所以需要在Insert()和Pop()函数中添加*S返回地址

#include<stdio.h>
#include<stdlib.h>
#define ERROR -1
#define OK 0
#define FALSE 1
#define MAXSIZE 100         //注：语句#define MAXSIZE 100;  会替换为100;;

struct SqStack {
    int *top;
    int *base;
    int stacksize;
};

void InitStack(struct SqStack *S);
int Push(struct SqStack *S, int x);
int Pop(struct SqStack *S, int *popnum);
void Print(struct SqStack S);

int main()
{
    struct SqStack S;
    int popnum;     //Pop()弹出的值

    InitStack(&S);
    Push(&S, 10);
    Push(&S, 20);
    Push(&S, 30);
    Push(&S, 40);
    Push(&S, 50);
    Pop(&S, &popnum);
    printf("now poped num is %d\n", popnum);
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

int Pop(struct SqStack *S, int *popnum)
{
    S->top = S->top - 1;
    (*popnum) = *(S->top);
    return OK;
}

void Print(struct SqStack S)
{
    int *temp = S.top;          //使用临时指针指向top位置的数据
    temp = S.top - 1;
    printf("--top--\n");
    while (temp >= S.base) {
        printf("%d\n", *temp);
        temp--;
    }
    printf("--base--\n");
}

