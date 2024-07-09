//实现Strcpy()，字符数组起始地址为0

#include<stdio.h>
#define TRUE 1
#define FALSE -1
#define MAXLEN 100      //字符数组最大长度为100

typedef struct {        //定义字符数组结构体
    int length;
    char ch[MAXLEN];
}SString;

int Strcopy(SString *S, char src[]);     //实现源字符数组传入现有数组S.ch

int main()
{
    SString S;
    char src[] = "loak";        //源字符数组
    Strcopy(&S, src);

    printf("S.ch is %s\n", S.ch);
    printf("S.length is %d\n", S.length);

    return 0;
}

int Strcopy(SString *S, char src[])
{
    int i = 0;
    while (src[i] != '\0')
    {
        S->ch[i] = src[i];
        i++;
    }
    S->ch[i] = '\0';      //为字符数组添加'\0'结尾
    S->length = i;          //传入字符数组大小
    return TRUE;
}