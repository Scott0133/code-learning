#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define TRUE 1
#define FALSE 2
#define MAXSIZE 20

typedef struct {
    int data[MAXSIZE];
    int top;
}SqStack;

void InitStack(SqStack *S);
int StackEmpty(SqStack S);
int Push(SqStack *S, char x);
int Pop(SqStack *S, char *x);
int Check(SqStack *S, char *x, char str[], int expression);


int main()
{
    char str[] = "A+B*(C-D)-E/F";
    SqStack S;
    InitStack(&S);
}

void InitStack(SqStack *S)
{
    S->top = -1;
}

int Push(SqStack *S, char x)
{
    if (S->top == MAXSIZE - 1)
        return FALSE;
    S->top = S->top + 1;
    S->data[S->top] = x;
    return TRUE;
}

int Pop(SqStack *S, char *x)
{
    if (S->top == 1)
        return FALSE;
    (*x) = S->data[S->top];
    S->top = S->top - 1;
    return TRUE;
}

int Pop_All(SqStack *S, char *x)
{
    while(S->top != 1)
    {
        (*x) = S->data[S->top];
        S->top = S->top - 1;
    }
    return TRUE;
}

int Check(SqStack *S, char *x, char str[], int expression)
{
    int i;
    int j;
    for (i=0; i<strlen(str); i++)
    {
        if (str[i] = 'A','B','C','D','E','F')
            Pop(&S, &x);
        if (str[i] = '(')
            Push(&S, str[i]);
        if (str[i] = '+','-','*','/')
            for (j=0; j<i; j++)
            {
                if (str[i] = '+' || '-')
                    Pop_All(&S, &x);
            }
    }

}