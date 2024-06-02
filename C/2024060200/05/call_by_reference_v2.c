//按引用调用
#include<stdio.h>
void fun(int *p);

int main()
{
    int num = 0;
    int *a = &num;
    fun(a);
    printf("Now num is %d\n", num);
    return 0;
}

void fun(int *p)
{
    int a = 1;
    int b = 2;
    *p = a + b;
}

int fun2(int q)
{
    q = 1;
}