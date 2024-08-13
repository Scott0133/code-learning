// quick_sort
// 快速排序

#include<stdio.h>
#define TRUE 0
#define FALSE 1

int Quick_Sort(int A[], int low, int high); // 快速排序
int Partition(int A[], int low, int high); // 快速排序分离函数
void Print(int A[], int length); 

int main()
{
    int A[] = {49, 38, 65, 97, 76, 13, 27, 49}; // 定义初始化测试数组
    int length = sizeof(A) / sizeof(A[0]); // 数组长度
    int low = 0;
    int high = length - 1;
    Quick_Sort(A, low, high);
    Print(A, length);

    return 0;
}

int Quick_Sort(int A[], int low, int high)
{
    if (low < high) { // 递归跳出的最终条件
        int povitpos = Partition(A, low, high); // 将枢轴元素存放最终位置赋值给povitpos
        Quick_Sort(A, povitpos+1, high); // 划分右子表
        Quick_Sort(A, low, povitpos-1); // 划分左子表

    }
    return TRUE;
}
// 用第一个元素将表划分为左右两个部分
int Partition(int A[], int low, int high)
{
    int pivot; // 定义枢轴
    pivot = A[low]; // 将数组A的第一个数作为枢轴
    while (low < high) { // 循环条件：找到所有枢轴
        while (low < high && A[high] >= pivot) { // 比枢轴小的数移动到左端
            --high; 
        }
        A[low] = A[high];
        while (low < high && A[low] <= pivot) { // 比枢轴大的数移动到右端
            ++low;
        }
        A[high] = A[low];
    }
    A[low] = pivot; // 枢轴元素存放到最终位置
    return low; // 返回枢轴元素存放的最终位置
}

void Print(int A[], int length)
{
    for (int i=0; i<length; i++)
    {
        printf("%d ", A[i]);
    }
}