#include<stdio.h>
int func(int n)
{
    int i=0, sum=0;
    while(sum<n)
    sum += ++i;
    return i;
}

int main()
{
    int c;
    int d;
    scanf("%d",&d);
    c = func(d);
    printf("%d",c);
    return 0;
}