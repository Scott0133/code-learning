//几种函数调用方式
#include<stdio.h>
void fun(int *p);
int fun2(int q);
int ret(int x);

int main()
{
    int num = 0;
    printf("num is %d\n", num);
    int *a = &num;
    fun(&num);
    printf("Now num is %d\n", num);
    printf("fun2(num) is %d\n",fun2(num));
    printf("ret(100) is %d\n",ret(100));
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

int ret(int x)
{
    return x;
}