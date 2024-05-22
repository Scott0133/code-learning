//指针与数组,A、&A和&A[0]
#include<stdio.h>
int B[5] = {11,22,33,44,55};
int A[5] = {10,20,30,40,50};

int main()
{

    printf("%d\n",A);       //数组的首地址，值与&A相同，但含义不同
    printf("%d\n",&A);      //数组对象的首地址!
    printf("%d\n",&A[0]);   //与 A 相同， A == &A[0]
    printf("%d\n",A[0]);    //10
    printf("%d\n",*A);      //10

    int *p;     //指向指针的指针 int* p = B
    p = &B[0];      //若使用p = &B会有warning，&B为整个数组的首地址
    p = p + 1;
    printf("the address of B is %d\n",B);
    printf("the address of B[0] is %d\n",&B[0]);
    printf("the address of B[1] is %d\n",p);
    printf("the value of B[1] is %d\n",*p);
    return 0;
    
}
