//数组作为函数参数
#include<stdio.h>
int SumOfElements(int A[], int size)        //这里的A[]编译器将其隐式转换为*A，作为指向整数的指针，因此可替用*A
{
    int i, sum = 0;
    for (i=0; i<size; i++)
    {
        sum += A[i];    //A[i] is *(A+i)
    }
    return sum;
}

int main()
{
    int A[] = {1,2,3,4,5};
    int size = sizeof(A)/sizeof(A[0]);      //个数 = 数组占内存的大小/每个元素占内存的大小
    printf("%d %d %d\n", size, sizeof(A), sizeof(A[0]));
    int total = SumOfElements(A, size);
    printf("sum = %d", total);
}