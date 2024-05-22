//递归的工作原理————累加的实现

#include<stdio.h>

int fun(int a);

int main()
{
    printf("fun(3) is %d",fun(100));
}

int fun(int a)
{
    if (a == 1)
    {
    return 1;
    }
    else
    {
    return a + fun(a - 1);
    }
}