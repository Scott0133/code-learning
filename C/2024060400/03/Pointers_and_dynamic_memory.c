//栈（stack）是数据结构的实现
//堆（heap）不是数据结构的实现
#include<stdio.h>
#include<stdlib.h>
int main()
{
    int a;      //goes on stack
    
    int *p;
    p = (int *)malloc(sizeof(int));
    *p = 10;
    free(p);
    p = (int *)malloc(sizeof(int));
    *p = 20;
    free(p);

    int *p2 = (int *)malloc(3*sizeof(int));     //p2可视为一个数组，动态分配数组
    *p2 = 1;            //OR p2[0]
    *(p2 + 1) = 2;      //OR p2[1]
    *(p2 + 2) = 3;      //OR p2[2]

    printf("p2[0] is %d\n", *p2);
    printf("p2[1] is %d\n", *(p2+1));
    printf("p2[2] is %d\n", *(p2+2));
    return 0;
}