//指针初探
#include<stdio.h>
int main()
{
    int i = 5;                              //初始化i = 5
    int *p;                                 //声明一个p指针
    p = &i;                                 //初始化p指针为i的地址

    printf("address of p is %d\n",p);       //6422044，p指向i的内存中的地址
    printf("address of &p is %d\n",&p);     //6422032，p在内存中的地址
    printf("address of i is %d\n",&i);      //6422044，i在内存中的地址
    printf("the value of *p is %d\n",*p);   //5
    printf("the value of i is %d\n",i);     //5

    *p = 6;
    printf("the value of *p is %d\n",*p);   //6
    printf("the value of i is %d\n",i);     //6 

    printf("address of p+1 is %d\n",p+1);       //i是int型，占4字节，6422048
    printf("the value of *(p+1) is %d\n",*(p+1));   //未声明p+1的指针，*(p+1)为内存值

    if(*p == i)
        {
            printf("1");
        }
    else 
        {
            printf("2");
        }
    return 0;
}