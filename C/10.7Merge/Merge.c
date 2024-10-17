// 两路合并排序算法（归并排序）（必须是有序序列），本算法初始时将待排序的n个数据元素看作n个待合并有序序列
// 最好/最坏/平均时间复杂度O(nxlog2n)，空间复杂度O(n)
// 稳定
// 注释by copilot
#include<stdio.h>
#include<stdlib.h>
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

void Print(List list); // 打印D[i].key
void Merge(List *list, Entry *temp, int low, int n1, int n2); // n1、n2是两个子序列长度，low是第一个子序列第一个元素下标
void MergeSort(List *list);

int main()
{
    // 表10.6
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
    MergeSort(list);
    Print(*list);
    free(list);

    return 0;
}

void Print(List list)
{
    for (int i=0; i<list.n; i++) {
        printf("%d ", list.D[i].key);
    }
}

void Merge(List *list, Entry *temp, int low, int n1, int n2){
    int i = low; // i和j分别指向两个序列的第一个元素
    int j = low + n1; // j指向第二个序列的第一个元素

    while (i <= low + n1 - 1 && j <= low + n1 - 1 + n2) { // 当两个子序列均未遍历完
        if (list->D[i].key <= list->D[j].key) { // 若第一个序列的当前元素小于或等于第二个序列的当前元素
            // *temp++ = list->D[i++]; // 将第一个序列的当前元素复制到临时数组，并移动i和temp
            *temp = list->D[i]; // 复制list中的当前元素到temp
            i++; // 将i递增1，指向下一个元素
            temp++; // 将temp指针递增1，指向下一个位置
        } else {
            // *temp++ = list->D[j++]; // 否则，将第二个序列的当前元素复制到临时数组，并移动j和temp
            *temp = list->D[j]; // 复制list中的当前元素到temp
            j++; // 将j递增1，指向下一个元素
            temp++; // 将temp指针递增1，指向下一个位置
        }
    }
    while (i <= low + n1 - 1) { // 若第一个序列仍有剩余元素
        // *temp++ = list->D[i++]; // 将剩余元素复制到临时数组
        *temp = list->D[i]; // 复制list中的当前元素到temp
        i++; // 将i递增1，指向下一个元素
        temp++; // 将temp指针递增1，指向下一个位置
    }
    while (j <= low + n1 - 1 + n2) { // 若第二个序列仍有剩余元素
        // *temp++ = list->D[j++]; // 将剩余元素复制到临时数组
        *temp = list->D[j]; // 复制list中的当前元素到temp
        j++; // 将j递增1，指向下一个元素
        temp++; // 将temp指针递增1，指向下一个位置
    }
}
void MergeSort(List *list){
    Entry temp[MaxSize]; // 临时数组用于存放合并结果
    int low, n1, n2, i; // 用于遍历和计算子序列长度的变量
    int size = 1; // 设初始子序列长度为1

    while (size < list->n) { // 逐步扩大子序列长度，直到覆盖整个序列
        low = 0; // 设置第一个子序列的起始下标
        while (low + size < list->n) { // 保证至少有两个子序列需要合并
            n1 = size; // 第一个子序列的长度
            if (low + size * 2 < list->n) {
                n2 = size; // 第二个子序列的长度
            } else {
                n2 = list->n - low - size; // 剩余元素的长度
            }
            Merge(list, temp + low, low, n1, n2); // 合并两个子序列
            low += n1 + n2; // 更新下一个待合并子序列的起始下标
        }
        for (i = 0; i < low; i++) {
            list->D[i] = temp[i]; // 将合并结果复制回原数组
        }
        size *= 2; // 子序列长度翻倍
    }
}
