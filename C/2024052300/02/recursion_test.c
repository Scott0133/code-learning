//递归测试，实现累加。
#include<stdio.h>

int recursion(int n);

int main()
{   
    int result;
    result = recursion(3);          //result = 7
    printf("result is %d",result);

    return 0;
}

int recursion(int n)
{
    if (n == 0)
    {
        return 0;
    }
    else
    {
        return n + recursion(n-1);
    }
}

/*递归算法快速计算步骤：
(从上至下push)
第一次执行：return 3 + recursion(2)
第二次执行：return 2 + recursion(1)
第三次执行：return 1 + recursion(0)
(从下至上pop)
第四次执行：return 1 + 0    [1 + recursion(0)]=>[recursion(1)]
第五次执行：return 2 + 1    [2 + recursion(1)]=>[recursion(2)]
第六次执行：return 3 + 3    [3 + recursion(2)]=>[recursion(3)]=>main中的recursion(3)
*/