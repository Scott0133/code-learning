// 快速排序————划分左右序列，进行递归排序
// 平均情况下最快的内排序算法
// 最好/平均时间复杂度O(nxlog2n)，最坏时间复杂度O(n²)
// 最好/平均空间复杂度O(log2n)，最坏空间复杂度O(n)

// 执行一次partition测试


#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define MaxSize 100
typedef int BOOL;
typedef int KeyType; // 定义排序关键字为整型
typedef char DataType; // data数据为char类型
typedef struct entry { // 数据元素结构体
    KeyType key; // 排序关键字，KeyType应为可比较类型
    DataType data; // data包含数据元素中其他数据项（暂不使用）
} Entry;
typedef struct list { // 定义顺序表结构体
    int n; // 待排序数据元素数量
    Entry D[MaxSize]; // D[]为数据元素结构体的数组
} List;


int Partition(List *list, int low, int high); // 序列划分函数
int QuickSort(List *list, int low, int high); // 快速排序算法
void StartQuickSort(List *list);
void Print(List list); // 打印D[i].key
void Swap(Entry D[], int i, int j); // 更新swap函数风格

int main()
{
    // 表10.4
    List *list = (List *)malloc(sizeof(List)); // 使用动态内存分配
    // 初始化结构体数据元素结构体数组，表10.2
    list->D[0].key = 25;
    list->D[1].key = 84;
    list->D[2].key = 21;
    list->D[3].key = 47;
    list->D[4].key = 15; // 相同关键字
    list->D[5].key = 27;
    list->D[6].key = 68;
    list->D[7].key = 35;
    list->D[8].key = 20;

    list->n = 9;
    // StartQuickSort(list);
    Partition(list, 0, 8);
    Print(*list);
    free(list);
    
    return 0;
}
int Partition(List *list, int low, int high) // 序列划分函数
{
    int i = low;
    int j = high + 1;
    Entry pivot = list->D[low]; // pivot是分割元素
    do {
        do i++; while (i<=high && list->D[i].key<pivot.key);
        do j--; while (list->D[j].key > pivot.key);
        if (i < j) {
            Swap(list->D, i, j);
        }
    } while (i < j); // 终止条件为左右指针越界
    Swap(list->D, low, j); // 将pivot与low位置交换，pivot（j）左边序列小于等于j，右边序列大于j
    return j; // 此时j是分割元素下标
}
int QuickSort(List *list, int low, int high) // 递归处理函数
{
    int k;
    if (low < high) { // 中止条件为当前排序序列少于两个元素
        k = Partition(list, low, high); // 划分
        QuickSort(list, low, k-1); // 划分左子表
        QuickSort(list, k+1, high); // 划分右子表
    }
}
void Print(List list)
{
    for (int i=0; i<list.n; i++) {
        printf("%d ", list.D[i].key);
    }
}
void Swap(Entry D[], int i, int j) // 交换元素位置（地址交换）
{
    Entry temp;
    if (i == j) {
        return;
    }
    temp = D[i];
    D[i] = D[j];
    D[j] = temp;
}
void StartQuickSort(List *list)
{
    QuickSort(list, 0, list->n-1); // 传入参数为List*, low, high
}