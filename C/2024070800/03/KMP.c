//起始下标为1
//串的顺序存储，基于静态数组
#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 2
#define ERROR -1
#define MAXLEN 255

typedef struct {
    char ch[MAXLEN];
    int length;
}SString;

void CopyString(SString *S, char src[]);
int StrLength(SString S);                                   //返回串S的元素个数
int Index_KMP(SString S, SString T, int next[]);                            //朴素模式匹配算法

int main()
{
    SString S;
    SString T;
    char s[] = "scott0133";
    char t[] = "ott";
    int next[] = {0,1,1};                            //手算next数组
    CopyString(&S, s);
    CopyString(&T, t);
    int index = Index_KMP(S, T, next);
    printf("%d\n", index);
}

void CopyString(SString *S, char src[]) {       //S为目标串的结构体成员，src为源串
    int i;
    S->ch[0] = '1';                             //S->ch[0]弃用，并置1
    for (i=1; src[i-1] != '\0'; i++) 
    {
        S->ch[i] = src[i-1];
    }
    S->ch[i] = '\0';                     // 添加字符串结尾的空字符
    S->length = i;
}

int StrLength(SString S)
{
    return S.length;
}

int Index_KMP(SString S, SString T, int next[])
{
    int i = 1;
    int j = 1;
    while (i<=S.length && j<T.length)
    {
        if (j == 0 || S.ch[i] == T.ch[j])
        {
            ++i; ++j;
        }
        else
        {
            j = next[j-1];              //若不匹配，模式串右移
        }
    }
    if (j>=T.length)
        return i-T.length + 1;
    else
        return 0;
}