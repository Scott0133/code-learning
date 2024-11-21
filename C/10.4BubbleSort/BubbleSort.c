// 冒泡排序————每次从前往后不断交换相邻逆序
// 稳定，最好时间复杂度O(n)，平均/最坏时间复杂度O(n²)

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

void BubbleSort(List *list);
void Swap(Entry *D, int i, int j); // 交换顺序表中两个元素位置
void Print(List list); // 打印D[i].key
void Swap2(Entry D[], int i, int j); // 更新swap函数风格

int main()
{
    // 表10.3
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

    BubbleSort(list);
    Print(*list);
    free(list);

    return 0;
}

void BubbleSort(List *list)
{
    int i, j; // i标识[每趟排序范围最后一个元素下标]，每趟排序元素下标范围是0~i
    for (i=list->n-1; i>0; i--) { // 每趟排序数组从后往前有序
        BOOL isSwap = FALSE; // 标记一趟排序中是否发生元素交换
        for (j=0; j<i; j++) {
            if (list->D[j].key > list->D[j+1].key) { //相邻元素关键字若为逆序
                Swap2(list->D, j, j+1); // 交换相邻元素
                isSwap = TRUE; //更新标志
            }
        }
        if (!isSwap) break; // 若本次没有发生元素交换，排序完成
    }
}
/*
直接使用void Swap(Entry D, int i, int j)是行不通的，因为这意味着 D 是结构体实例，而不是指向数组的指针。
可以这样设计：
void Swap(Entry D[], int i, int j) {
    Entry temp;
    if (i == j) {
        return;
    }
    temp = D[i];
    D[i] = D[j];
    D[j] = temp;
}
*/
void Swap(Entry *D, int i, int j) // 交换两个元素的地址
{
    Entry temp; // 声明临时数据元素结构体，存储待交换的结构体地址
    if (i == j) { // 下标相等，不交换
        return ;
    }
    temp = *(D + i); // temp指向第一个元素的地址
    *(D + i) = *(D + j);
    *(D + j) = temp;
}
void Print(List list)
{
    for (int i=0; i<list.n; i++) {
        printf("%d ", list.D[i].key);
    }
}
void Swap2(Entry D[], int i, int j) // 使用Swap2更清晰明了
{
    Entry temp;
    if (i == j) {
        return;
    }
    temp = D[i];
    D[i] = D[j];
    D[j] = temp;
}