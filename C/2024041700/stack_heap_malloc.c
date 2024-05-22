#include<stdio.h>
#include<stdlib.h>
int main()
{
    int a;  //在stack上
    int* p;
    p = (int*)malloc(sizeof(int));  //使用malloc()在heap上分配内存
    *p = 10;
    free(p);

    return 0;

}