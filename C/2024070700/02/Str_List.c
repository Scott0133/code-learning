//串的顺序存储，基于静态数组
#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 2
#define ERROR -1
#define MAXLEN 255
//以静态数组实现串（定长顺序存储）
typedef struct {
    char ch[MAXLEN];
    int length;
}SString;

void CopyString(SString *S, char src[]);
int StrLength(SString S);                                   //返回串S的元素个数
int SubString(SString *Sub, SString S, int pos, int len);//用Sub返回主串S的第pos个字符起长度为len的子串
int StrCompare(SString S, SString T);
int Index(SString S, SString T);

//以动态数组实现串（堆分配存储）
/*
typedef struct {
    char *ch;
    int length;
}HString;

HString S;
S.ch = (char *)malloc(MAXLEN * sizeof(char));
S.length = 0;
*/

//以链表形式存储串
/*
typedef struct StringNode {
    char ch;                    // or char ch[4]，每个结点多个字符。
    struct StringNode *next;
}StringNode, *String;
*/

int main()
{
    SString S;
    SString Sub;
    SString T;

    char src[] = "MicrosoftCopilot";  //定义源串
    char t[] = "ot";

    CopyString(&S, src);
    CopyString(&T, t);


    printf("S.ch: %s\n", S.ch);                         //S.ch为目标串
    printf("S.length = %d\n", StrLength(S));

    SubString(&Sub, S, 5, 4);
    printf("StrCompare(S, T) = %d\n", StrCompare(S, T));
    printf("Sub.ch = %s\n", Sub.ch);
    printf("index is %d\n", Index(S, T));       //bug maybe
    
    return 0;
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

int SubString(SString *Sub, SString S, int pos, int len)
{
    if (pos + len - 1 > S.length)
        return FALSE;
    for (int i=pos; i<pos+len; i++)
    {
        Sub->ch[i - pos + 1] = S.ch[i+1];
    }
    Sub->length = len;
    return TRUE;
}

int StrCompare(SString S, SString T)     //若S>T，则返回值>0，若S<T，则返回值<0
{
    for (int i=1; i<=S.length && i<=T.length; i++)
    {
        if (S.ch[i+1] != T.ch[i])
        {
            return S.ch[i+1] - T.ch[i];
        }
    }
    return S.length - T.length;
}

int Index(SString S, SString T)     //定位主串S与子串T第一次相同的位置
{
    int i = 1;
    int n = StrLength(S);
    int m = StrLength(T);
    SString Sub1;                //暂存子串
    while (i <= n - m + 1)
    {
        SubString(&Sub1, S, i, m);
        if (StrCompare(Sub1, T) != 0)
        {
            ++i;
        }
        else
        {
            return i+2;   //返回子串在主串中的位置
        }
    }
    return ERROR;       //S中不存在与T相同子串
}