//朴素模式匹配算法，起始下标为0
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define TRUE 1
#define FALSE 2
#define ERROR -1
#define MAXLEN 255

typedef struct {
    char ch[MAXLEN];
    int length;
}SString;

int Index(SString S, SString T);
int StrLength(SString S);

int main()
{
    SString S;
    SString T;
    char s[] = "asdasdasdasd";
    char t[] = "das";
    strcpy(S.ch, s);
    strcpy(T.ch, t);
    S.length = strlen(S.ch);
    T.length = strlen(T.ch);

    int ret = Index(S, T);
    printf("Index is %d\n", ret);

    return 0;
}

int Index(SString S, SString T)
{
    int i = 0;
    int j = 0;
    while (i<S.length && j<T.length)
    {
        if (S.ch[i] == T.ch[j])         //若主串中子串S.ch[i]与匹配串T.ch[j]字符相同，则比较下一个
        {
            ++i; ++j;
        }
        else
        {
            i = i - j + 1;              //若不同，则主串指向下一个子串起始位置
            j = 0;                      //匹配串指针后退重新匹配
        }
    }
    if (j+1>T.length)
        return i-T.length;
    else
        return 0;
}
