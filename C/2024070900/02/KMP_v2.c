//KMP_v2，优化next[]
//起始下标为1，bugmaybe
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
int Index_KMP(SString S, SString T, int next[]);
int KMP_v2(SString S, SString T, int nextval[]);
//int Return_Nextval(int *next[]);

int main()
{
    SString S;
    SString T;
    char s[] = "abbabbabababaababaab";
    char t[] = "ababaa";
    int next[] = {-1,0,1,1,2,3,4};                            //手算next数组(bug)，数组下标从1开始
    // int next[] = {0,1,1,2,3,4};                               //若next数组起始下标为0
    CopyString(&S, s);
    CopyString(&T, t);
//
    int nextval[7];                                        //求nextval数组，数组下标从1开始
    nextval[1] = 0;
    for (int j=2; j<=T.length-1; j++)
    {
        if (T.ch[next[j]] == T.ch[j])           //若字符相等
            nextval[j] = nextval[next[j]];      //赋值
        else
            nextval[j] = next[j];               //赋值
    }
//

// // BUG
//     int nextval_2[6];                             //起始下标为0
//     nextval_2[1] = 0;
//     for (int j=2; j<=T.length-1; j++)
//     {
//         if (T.ch[next[j]] == T.ch[j])           //若字符相等
//             nextval_2[j] = nextval_2[next[j]];      //赋值
//         else
//             nextval_2[j] = next[j];               //赋值
//     }
    
// //
    int index = Index_KMP(S, T, next);
    int index2 = KMP_v2(S, T, nextval);
    printf("%d\n", index);
    printf("%d\n", index2);
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
            j = next[j];              //若不匹配，模式串右移
        }
    }
    if (j>=T.length)
        return i-T.length + 1;
    else
        return 0;
}

int KMP_v2(SString S, SString T, int nextval[])
{
    Index_KMP(S, T, nextval);
}