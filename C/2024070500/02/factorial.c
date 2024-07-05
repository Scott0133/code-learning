//factorial
#include<stdio.h>
#define ERROR -1

int Factorial(int n);
int Fib(int x);

int main()
{
    int num, num2;
    num =  Factorial(5);
    num2 = Fib(4);
    printf("Factorial(5) = %d\n", num);
    printf("Fib(4) = %d\n", num2);
    return 0;
}

int Factorial(int n)
{

    if (n == 1 || n == 0)
    {
        return 1;
    }
    else
    {
        return n * Factorial(n - 1);
    }
}

int Fib(int x)
{
    if (x == 1)
        return 1;
    else if (x == 0)
        return 0;
    else
        return Fib(x - 1) + Fib(x - 2);
}