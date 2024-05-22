//函数指针,两个实例
#include<stdio.h>
int sum(int a, int b)
{
    return a+b;
}

void printhello(char* name)
{
    printf("hello %s",name);
}

int main()
{
    int c;
    int(*p)(int,int);       //声明函数指针，不同于int* p(int,int),后者为返回int*类型的函数
    p = &sum;               //p = &sum == p = sum;
    c = (*p)(2,3);          //(*p)(2,3) == p(2,3);
    printf("%d\n",c);

    int d;
    void (*ptr)(char*);
    ptr = printhello;
    ptr("niko\n");

    return 0;
}