// 顺序搜索无序表的实现
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

int Search(listSet L, ElemType x);

int main()
{
    listSet L; // 定义类型
    L.maxLength = MAX;
    L.element = (ElemType *)malloc(L.maxLength*sizeof(ElemType)); // 分配数据空间
    L.element[0] = 1;
    L.element[1] = 29;
    L.element[2] = 10;
    L.element[3] = 5;
    L.element[4] = 13;
    // printf("%d\n", L.n = sizeof(L.element)/sizeof(L.element[0]));
    L.n = 5;
    int ret = Search(L, 5);
    if (ret == -1) {
        printf("not found");
    } else {
        printf("element[%d] is %d", ret, L.element[ret]);
    }

    return 0;

}

int Search(listSet L, ElemType x) // 在无序表中查找整数x
{
    int i;
    for (int i=0; i<L.n; i++) {
        if (L.element[i] == x) {
            return i; // 搜索成功
        }
    }
    return -1; // 搜索失败
}