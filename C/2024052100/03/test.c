//递归测试————使用递归打印长横线
#include<stdio.h>

int fun(int q);

int main()
{
    printf("%d", fun(5));       //fun(5) = 16
}

int fun(int q)
{
    if (q == 0)
    {
        return 1;
    }
    else
    {
        printf("--==--");
        (q + fun(q - 1));
        printf("//--==--");       //8?
    }

}