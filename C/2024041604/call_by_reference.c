//可传递a=11，按引用调用
#include<stdio.h>
void Increment(int *p);
int main()
{
    int a;
    a = 10;
    Increment(&a);      //int* p = &a;
    printf("a = %d",a);

    return 0;
}

void Increment(int *p)
{
    *p = (*p) + 1;
    printf("now *p is %d\n",*p);
}