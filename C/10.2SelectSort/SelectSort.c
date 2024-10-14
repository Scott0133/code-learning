// 10.2 简单选择排序算法————每一趟排序，找到待排序序列中关键字最小的数据元素
// 不稳定，最好/平均/最坏时间复杂度O(n²)

#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define MaxSize 100
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

int FindMin(List list, int startIndex); // 在startIndex至表尾找到最小关键字元素下标
void Swap(Entry *D, int i, int j); // 交换顺序表中两个元素位置
void SelectSort(List *list); // 简单选择排序
void Print(List list); // 打印D[i].key

int main()
{
    /*
    用注释代码动态分配内存（malloc）和直接初始化各有利弊：
    动态分配内存（注释段代码）:
    优点: 内存管理更加灵活，适合处理需要动态调整大小的数据结构。对于大规模或未知规模的数据结构尤其有用。
    缺点: 需要手动管理内存，需要在不再使用数据时释放内存（free），否则可能导致内存泄漏。

    直接初始化（当前代码）:
    优点: 简单直接，不需要显式地管理内存。适合处理小规模和固定大小的数据结构。
    缺点: 内存大小固定，灵活性较差，不适用于需要动态调整大小的数据结构。
    */
    // List list; // 直接初始化代码
    List *list = (List *)malloc(sizeof(List)); // 使用动态内存分配
    // 初始化结构体数据元素结构体数组，表10.1
    list->D[0].key = 24;
    list->D[1].key = 29;
    list->D[2].key = 45;
    list->D[3].key = 73;
    list->D[4].key = 24; // 相同关键字
    list->D[5].key = 89;
    list->D[6].key = 90;
    list->D[7].key = 11;
    list->n = 8;

    SelectSort(list);
    Print(*list);
    free(list);

    return 0;

}

int FindMin(List list, int startIndex)
{
    int i;
    int minIndex = startIndex;
    for (i=startIndex+1; i<list.n; i++) { // 除开待交换元素，找到数组中最小元素
        if (list.D[i].key < list.D[minIndex].key) { // 将当前元素大小与待排序元素比较
            minIndex = i;
        }
    }
    return minIndex; // 返回最小元素下标
}
void Swap(Entry *D, int i, int j)
{
    Entry temp; // 声明临时数据元素结构体，存储待交换的结构体地址
    if (i == j) { // 下标相等，不交换
        return ;
    }
    temp = *(D + i); // temp指向第一个元素的地址
    *(D + i) = *(D + j);
    *(D + j) = temp;
}
void SelectSort(List *list)
{
    int minIndex = 0;
    int startIndex = 0;
    while (startIndex < list->n-1) { // 找到待排序序列中关键字最小的数据元素
        minIndex = FindMin(*list, startIndex);
        Swap(list->D, startIndex, minIndex);
        startIndex++;
    }
}
void Print(List list)
{
    for (int i=0; i<list.n; i++) {
        printf("%d ", list.D[i].key);
    }
}