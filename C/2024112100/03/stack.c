// 顺序栈的实现
    // 辅助数据结构：一维数组
#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
typedef int ElemType;

typedef struct stack {
    int top;
    int MaxSize;
    ElemType *element;
} Stack;

void Init_Stack(Stack *S, int maxsize);
void Destroy(Stack *S);
int Is_Empty(Stack S);
int Is_Full(Stack S);
int Push(Stack *S, ElemType x);
int Get_Top(Stack *S, ElemType *e);
int Pop(Stack *S);
void Clear(Stack *S);
int Print_Stack(Stack S);

int main()
{
    Stack S;
    Init_Stack(&S, 10);
    Push(&S, 10);
    Push(&S, 20);
    Push(&S, 30);
    Print_Stack(S);
    return 0;
}

void Init_Stack(Stack *S, int maxsize)
{
    S->top = -1; // 初始栈指针指向-1
    S->MaxSize = maxsize;
    S->element = (ElemType *)malloc(S->MaxSize*sizeof(ElemType));
}
void Destroy(Stack *S)
{
    if (S->element) {
        free(S->element);
        S->element = NULL;
    }
    S->MaxSize = 0;
    S->top = -1;
}
int Is_Empty(Stack S)
{
    if (S.top == -1) {
        return TRUE;
    } else {
        return FALSE;
    }
}
int Is_Full(Stack S)
{
    if (S.top == S.MaxSize - 1) {
        return TRUE;
    } else {
        return FALSE;
    }
}
int Push(Stack *S, ElemType x)
{
    if (Is_Full(*S)) {
        return FALSE;
    }
    S->top++;
    S->element[S->top] = x;
    return TRUE;
}
int Get_Top(Stack *S, ElemType *e)
{
    if (Is_Empty(*S)) {
        return FALSE;
    }
    *e = S->element[S->top];
    return TRUE;
}
int Pop(Stack *S)
{
    if (Is_Empty(*S)) {
        return FALSE;
    }
    S->top--;
    return TRUE;
}
void Clear(Stack *S)
{
    S->top = -1;
}
int Print_Stack(Stack S)
{
    if (Is_Empty(S)) {
        printf("NULL");
        return FALSE;
    }
    int p = S.top;
    while (p != -1) {
        printf("%d\n", S.element[p]);
        p--;
    }
    return TRUE;
}