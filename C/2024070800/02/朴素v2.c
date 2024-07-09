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
int Index(SString S, SString T);                            //朴素模式匹配算法

int main()
{
    SString S;
    SString T;
    char s[] = "scott0133";
    char t[] = "ott";
    CopyString(&S, s);
    CopyString(&T, t);
    int index = Index(S, T);
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

int Index(SString S, SString T)
{
    int i = 1;
    int j = 1;
    while (i<=S.length && j<T.length)
    {
        if (S.ch[i] == T.ch[j])         //若主串中子串S.ch[i]与匹配串T.ch[j]字符相同，则比较下一个
        {
            ++i; ++j;
        }
        else
        {
            i = i - j + 2;              //若不同，则主串指向下一个子串起始位置
            j = 1;                      //匹配串指针后退重新匹配
        }
    }
    if (j>=T.length)
        return i-T.length + 1;
    else
        return 0;
}