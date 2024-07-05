//recursing test
#include<stdio.h>

int func1(int x, int y);
int func2(int x1, int y1);
int func3(int x2, int y2);

int main()
{
    printf("return %d", func1(2, 3));
    return 0;
}

int func1(int x, int y)
{
    func2(3, 4);
    return x + y;
}
int func2(int x1, int y1)
{
    func3(5, 6);
    return x1 + y1;
}

int func3(int x2, int y2)
{
    return x2 + y2;
}