//函数指针与指针函数


#include<stdio.h>

int (*func_pointer)(int x, int y);         //函数指针，本质为指针，指向一个函数
int add(int x, int y);                     //定义两个函数指针将指向的函数
int sub(int x, int y);

int *Pointer_Func();                       //指针函数，本质为函数，返回值为指针

int main()
{
    printf("%d\n", Pointer_Func());
    
    func_pointer = &add;
    printf("%d\n", (*func_pointer)(2, 3));
    func_pointer = &sub;
    printf("%d\n", (*func_pointer)(3, 2));

    return 0;
}

int *Pointer_Func()
{
    int a = 0;
    int *p = &a;
    return p;
}

int add(int x, int y)
{
    return x + y;
}

int sub(int x, int y)
{
    return x - y;
}

