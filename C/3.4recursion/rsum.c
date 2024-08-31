// 递归小例
#include<stdio.h>
void rsum(int matix[], int n);
void sum(int matix[], int n);
int main()
{
    int matix[] = {1,2,3,4,5}; // 测试数组
    int n = sizeof(matix) / sizeof(matix[0]);
    rsum(matix, n);
    sum(matix, n);
    return 0;
}

void rsum(int matix[], int n) // 逆序打印数组元素
{
    n = n - 1;
    if (n >= 0) {
        printf("%d ", matix[n]);
        rsum(matix, n); // rsum，尾递归
    }
}
void sum(int matix[], int n) // 消除递归的逆序打印
{
    int i;
    for (i=n-1; i>=0; i--) {
        printf("%d", matix[i]);
    }
}
