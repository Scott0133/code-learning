#include<stdio.h>
#include<stdlib.h>
#define ERROR -1
#define TRUE 1
typedef int ElemType;

ElemType main()
{
    ElemType M = 2;      //矩阵行数
    ElemType N = 4;      //矩阵列数
    ElemType i = 1;      //矩阵元素行号
    ElemType j = 2;      //矩阵元素列号

    ElemType b[2][4] = {{1,2,3,4},{5,6,7,8}};
    //printf("b[0][0] is %d\n", b[0][0]);
    ElemType *start = &b[0][0];
    ElemType step = (i*N+j)*sizeof(ElemType);
    ElemType *tag_addr = (int *)((char *)start + step);        //!!使用强制类型转换，否则start+step = 96
    printf("start is %d\n", start);
    printf("fin_addr is %d\n", tag_addr);
    printf("&b[1][2] is %d\n", &b[1][2]);
    printf("&b[1][3] - &b[1][2] = %d\n", &b[1][3] - &b[1][2]);
    //printf("%d\n", (start + 6));
}