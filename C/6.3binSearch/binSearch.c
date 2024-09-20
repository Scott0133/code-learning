// 对半搜索（折半查找）的递归算法
// 要求线性表是有序表并采用顺序存储结构
#include<stdio.h>
#include<stdlib.h>
#define MAX 100
#define TRUE 1
#define FALSE 0
#define OverFlow 2 // 上溢
#define UnderFlow 3 // 下溢
#define NotPresent 4 // 元素不存在
#define Duplicate 5 // 元素重复
typedef int ElemType;

typedef struct { // 定义listSet类型
    int n; // 动态集中数据元素个数
    int maxLength; // 动态集的最大允许长度
    ElemType *element;  // 动态集存储空间首地址
} listSet;

int binSearch(listSet L, ElemType x, int low, int high);

int main()
{
    listSet L; // 定义类型
    L.maxLength = MAX;
    L.element = (ElemType *)malloc(L.maxLength*sizeof(ElemType)); // 分配数据空间
    L.element[0] = 1;
    L.element[1] = 5;
    L.element[2] = 10;
    L.element[3] = 12;
    L.element[4] = 13;
    L.element[5] = 45;
    L.element[6] = 54;
    L.element[7] = 89;
    L.element[8] = 90;
    L.element[9] = 95;
    L.n = 10;
    int low = 0;
    int high = 9;
    int ret = binSearch(L, 54, low, high);
    printf("m in element[m] is %d\n", ret);

    return 0;
}

int binSearch(listSet L, ElemType x, int low, int high)
{
    if (low <= high) {
        int m = (low + high) / 2;
        if (x < L.element[m]) {
            return binSearch(L, x, low, m-1);
        } else if (x > L.element[m]) {
            return binSearch(L, x, m+1, high);
        } else {
            return m; // 搜索成功
        }
    }
    return -1; // 搜索失败
}

