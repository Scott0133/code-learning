// 10.3 直接插入排序算法————不断将待排序元素插入到有序序列中
// 使用InsertItem临时存储每趟插入元素
// 稳定，最好时间复杂度O(n)，最坏时间复杂度O(n²)
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

void InsertSort(List *list);
void Print(List list); // 打印D[i].key

int main()
{
    List *list = (List *)malloc(sizeof(List)); // 使用动态内存分配
    // 初始化结构体数据元素结构体数组，表10.2
    list->D[0].key = 24;
    list->D[1].key = 29;
    list->D[2].key = 45;
    list->D[3].key = 73;
    list->D[4].key = 24; // 相同关键字
    list->D[5].key = 89;
    list->D[6].key = 90;
    list->D[7].key = 11;
    list->n = 8;

    InsertSort(list);
    Print(*list);
    free(list);

    return 0;
}

void InsertSort(List *list)
{
    int i, j; // i为待插入元素下标
    Entry InsertItem; // 每一趟待插入元素
    for (i=0; i<list->n; i++) {
        InsertItem = list->D[i];
        for (j=i-1; j>=0; j--) { // 不断将有序序列中元素向后移动，为待插入元素空出一个位置（插入的元素在末尾不移动）
            if (InsertItem.key < list->D[j].key) {
                list->D[j+1] = list->D[j];
            } else { // 插入的元素在末尾
                break;
            }
        }
        list->D[j+1] = InsertItem; // 将待插入元素有序存放至有序序列中
    } 
}
void Print(List list)
{
    for (int i=0; i<list.n; i++) {
        printf("%d ", list.D[i].key);
    }
}