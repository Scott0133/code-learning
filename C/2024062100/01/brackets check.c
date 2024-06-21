//brackets check
//顺序栈v2
#define MaxSize 10
#define TRUE 1
#define FALSE 2
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
    char data[MaxSize];
    int top;
}SqStack;

void InitStack(SqStack *S);
int StackEmpty(SqStack S);
int Push(SqStack *S, char x);
int Pop(SqStack *S, char *x);
int bracketCheck(char str[], int length);

int main()
{
    char str1[] = "()[]";
    int length = strlen(str1);
    bracketCheck(str1, length);
    
}

void InitStack(SqStack *S)
{
    S->top = -1;
}

int StackEmpty(SqStack S)
{
    if (S.top == -1)
        return TRUE;
    else
        return FALSE;
}

int Push(SqStack *S, char x)
{
    if (S->top == MaxSize-1)
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

int bracketCheck(char str[], int length)
{
    SqStack S;
    InitStack(&S);
    int i;
    for (i=0; i<length; i++)
    {
        if (str[i] == '(' || str[i] == '[' || str[i] == '{')
        {
            Push(&S, str[i]);
        } else {
            if (StackEmpty(S) == TRUE)
                return FALSE;
        char topElem;
        Pop(&S, &topElem);
        if (str[i] == ')' && topElem != '(')
            return FALSE;
        if (str[i] == ']' && topElem != '[')
            return FALSE;
        if (str[i] == '}' && topElem != '{')
            return FALSE;
        }
    }
    return StackEmpty(S);
}