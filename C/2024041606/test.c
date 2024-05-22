#include<stdio.h>
int A[] = {1,2,3,4,5};
void fun(int* p,int* q);     //通过指针传递数值
int main()
{
    int a = 1;
    int b = 2;

    if (sizeof(A)==sizeof(&A[0]));      //A == &A[0]
    {
        printf("1\n");
    }
    if (sizeof(A[0])==sizeof(*A));      //A[0] == *A
    {    
        printf("1\n");
    }

    fun(&a,&b);
    //printf("now a is %d\n",a);

    return 0;
}

void fun(int* p, int* q)
{
    *p = *(p + 1);
    printf("now a is %d\n",*p);
    *q = *q + 1;
    printf("now b is %d\n",*q);
    *q = (*q) + 1;              //运算符优先级*大于+
    printf("now b is %d\n",*q);
}

