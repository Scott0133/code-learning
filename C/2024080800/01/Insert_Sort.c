// 插入排序（基于顺序表）
// 折半插入排序（比较关键字的次数减少）（基于顺序表）
// 将待排序的记录按关键字大小插入到前面已排好序的子序列中，直到全部记录插入完成

#include<stdio.h>
#define MAXLENGTH 20

void Insert_Sort(int Arr[], int n); // 插入排序（不带哨兵结点）
void Insert_Sort_Half(int Arr[], int n); // 折半插入排序（带哨兵结点）
void Print(int Arr[], int n);

int main()
{
    int Arr[MAXLENGTH];
    int Arr_[] = {3,51,62,32,43,11,26,42,94,33}; // 定义测试数组
    int length = sizeof(Arr_)/sizeof(Arr_[0]); // 计算元素个数
    for (int i=1; i<length+1; i++)
    {
        Arr[i] = Arr_[i-1]; // 初始化数组Arr_
    }


    //Insert_Sort(Arr, length);
    Insert_Sort_Half(Arr, length);
    Print(Arr, length);
}

void Insert_Sort(int Arr[], int n) // n为数据元素个数
{
    int i, j, temp;
    for (i=1; i<n; i++) // 将各元素插入已排好序列中
    {
        if (Arr[i] < Arr[i-1]) { // 若Arr[i]关键字小于前驱
            temp = Arr[i]; // 用temp暂存Arr[i]
            for (j=i-1; j>=0 && Arr[j]>temp; --j) { // 检查所有前面已排好序的元素
                Arr[j+1] = Arr[j]; // 所有大于temp的元素都向后移位
            }
            Arr[j+1] = temp; // 将temp复制到插入位置
        }
    }
}

void Insert_Sort_Half(int Arr[], int n) // 折半插入排序
{
    int i, j, low, high, mid;
    for (i=2; i<=n; i++) { // 将Arr[2]到Arr[n]插入到前面已排序序列
        Arr[0] = Arr[i]; // 将Arr[i]暂存到Arr[0]
        low = 1; high = i-1; // 设置折半查找范围
        while (low <= high) { // 折半查找（递增）
            mid = (low + high) / 2; // 取中间值
            if (Arr[mid] > Arr[0]) {
                high = mid - 1; // 查找左子表
            } else {
                low = mid + 1; // 查找右子表
            }
        }
        for (j=i-1; j>=high+1; --j) {
            Arr[j+1] = Arr[j]; // 统一右移值，空出插入位置
        }
        Arr[high+1] = Arr[0]; // 插入值
    }
}

void Print(int Arr[], int n)
{
    int i;
    for (i=1; i<=n; i++)
    {
        printf("%d ", Arr[i]);
    }
}