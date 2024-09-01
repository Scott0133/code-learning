// 简单字符串匹配算法

#include<stdio.h>
#define MaxSize 256
#define TRUE 1
#define FALSE 0
typedef struct string { // 字符串结构体
    char str[MaxSize];
    int length, maxLength;
} String;

int Index(String S, String P, int pos); // 匹配运算：从主串s的pos位置处向后查找是否存在子串p，若存在则返回子串位置，否则返回-1
int Match(String S, String P, int s_start, int p_start, int *s, int *p_fail); // 简单字符串匹配算法

int main()
{
    String S = {"googoogogle", 11, 20}; // 主串测试用例
    String P = {"gog", 3, 20}; // 模式串测试用例
    int ret = Index(S, P, 0);
    printf("%d", ret);
    
    return 0;
}

int Index(String S, String P, int pos)
{
    int s_start, p_start = 0, s_fail, p_fail;
    for (s_start = pos; s_start <= S.length-P.length; s_start++) {
        if (Match(S, P, s_start, p_start, &s_fail, &p_fail)) {
            return s_start;
        }
    }
    return -1;
}
int Match(String S, String P, int s_start, int p_start, int *s_fail, int *p_fail) // 一趟匹配过程
{
    int i = s_start, j = p_start; // 游标i和j分别指向主串和模式串当前比较的字符
    for (; j<P.length; i++, j++) {
        if (S.str[i] != P.str[j]) {
            *s_fail = i; // s_fail记录主串失配位置
            *p_fail = j; // p_fail记录模式串失配位置
            return FALSE;
        }
    }
    return TRUE;
}
