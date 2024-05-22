#include<stdio.h>
void bianli();
void init();
const int number = 10;
int a[10];
int main()
{
    init();
    bianli();
    return 0;
}

void init()
{
    int i;
    for( i=0; i<number; i++)
        a[i] = 0;
}

void bianli()
{
    int i;
    for( i=0; i<number; i++)
        printf("a[%d]=%d\n",i,a[i]);
}