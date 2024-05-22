//按值调用，不能得到i=2
#include<stdio.h>
const int a = 1;
void increment(a);

int main()
{
    int i = 1;
    increment(i);
    printf("now i is %d\n",i);

    return 0;
}

void increment(a)
{
    a = a + 1;
    printf("now a is %d\n",a);
}