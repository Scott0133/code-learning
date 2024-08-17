// merge_sort（归并排序，稳定）
// 归并：把两个或多个[已有序]的序列合并成一个
// 对比i、j所指元素，选择更小的一个放入k所指位置

#include<stdio.h>
#include<stdlib.h>

void Merge(int A[], int low, int mid, int high);
void MergeSort(int A[], int low, int high);
void Print(int A[], int len);

int main()
{
    int A[] = {49, 38, 65, 97, 76, 13, 27}; // 对A数组进行归并排序
    int n = sizeof(A) / sizeof(A[0]);
    int low = 0;
    int high = n - 1;
    MergeSort(A, low, high);
    Print(A, n-1);
    return 0;
}
// A[low...mid]和A[mid+1...high]各自有序，将两个部分归并（第一次归并为两个单独元素）
void Merge(int A[], int low, int mid, int high) // 二路归并
{
    
    int B_len = high + 1; // 辅助数组长度
    int *B = (int *)malloc(B_len*sizeof(int)); // 定义辅助数组B

    int i, j, k;
    for (k=low; k<=high; k++) {
        B[k] = A[k]; // 将A中所有元素复制到B中
    }
    for (i=low, j=mid+1, k=i; i<=mid && j<=high; k++) {
        if (B[i] <= B[j]) {
            A[k] = B[i++]; // 将较小值复制到B中
        } else {
            A[k] = B[j++];
        }
    } // for
    while (i <= mid) { // 检查左边的序列是否处理完
        A[k++] = B[i++];
    }
    while (j <= high) { // 检查右边的序列是否处理完
        A[k++] = B[j++];
    }
}
// 归并排序主流程
void MergeSort(int A[], int low, int high)
{
    if (low < high) {
        int mid = (low + high) / 2; // 从中间划分
        MergeSort(A, low, mid); // 对左半部分归并排序
        MergeSort(A, mid+1, high); // 对右半部分归并排序
        Merge(A, low, mid, high); // 归并
    }
}
void Print(int A[], int len)
{
    for (int i=0; i<len; i++) {
        printf("%d ", A[i]);
    }
}