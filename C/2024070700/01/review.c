//recursion
//计算n!
#include<stdio.h>
int fun(int x);

int main()
{
    int num;
    num = fun(5);
    printf("5! is %d\n", num);
    
    return 0;
}

int fun(int x)
{
    if (x == 1 || x == 0)
        return 1;
    else
        return x * fun(x - 1);
}