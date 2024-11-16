// 程序10.9 堆排序算法，基于最大堆数据结构实现元素从小到大排序
// 程序 基于完全二叉树的大根堆建立
// 时间复杂度最好/平均/最坏O(nxlog2n)，空间复杂度O(1)
// 不稳定

#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define OverFlow 2 // 上溢
#define UnderFlow 3 // 下溢
#define NotPresent 4 // 元素不存在
#define Duplicate 5 // 元素重复
#define MaxSize 100
typedef int ElemType;
typedef int KeyType; // 定义排序关键字为整型
typedef char DataType; // data数据为char类型

typedef struct entry { // 数据元素结构体
    KeyType key; // 排序关键字，KeyType应为可比较类型
    DataType data; // data包含数据元素中其他数据项（暂不使用）
} Entry;
typedef struct maxheap { // 定义最大堆结构体
    int n;
    int maxsize; // ?
    Entry D[MaxSize]; // D[]为数据元素结构体的数组
} MaxHeap;
// typedef struct maxheap { // 定义最大堆结构体
//     int n;
//     int Heap_Size;
//     Entry D[MaxSize]
// } MaxHeap;

void AdjustDown(MaxHeap *heap, Entry D[], int current, int border);
void CreateHeap(ElemType heap[], int n);
void Print_arr(MaxHeap *hp);
void HeapSort(MaxHeap *heap);
void Swap(Entry D[], int i, int j); // 更新swap函数风格


int main()
{
    // int testarr[] = {61, 28, 81, 43, 36, 47, 83, 5}; // 测试数组
    // CreateHeap(testarr, 8);
    // Print_arr(testarr);
    // 表10.7
    MaxHeap *hp = (MaxHeap *)malloc(sizeof(MaxHeap)); // 使用动态内存分配
    // 初始化结构体数据元素结构体数组，表10.2
    hp->D[0].key = 24;
    hp->D[1].key = 29;
    hp->D[2].key = 45;
    hp->D[3].key = 73;
    hp->D[4].key = 24; // 相同关键字
    hp->D[5].key = 89;
    hp->D[6].key = 90;
    hp->D[7].key = 11;
    hp->n = 8;
    HeapSort(hp);
    Print_arr(hp);

    free(hp);
    return 0;
}

void AdjustDown(MaxHeap *heap, Entry D[], int current, int border) // 元素下坠法调整为大根堆
{
    int p = current; // 将变量p指向当前考察元素
    int minChild; // 当前考察元素中最小的一个孩子
    int maxChild; // 当前考察元素中最大的一个孩子
    ElemType temp;
    while (2*p+1 <= border) { // 若p不是叶子结点则调整
        if ((2*p+2 <= border) && (heap->D[2*p+1].key < heap->D[2*p+2].key)) { // 2*p+1为左孩子，2*p+2为右孩子
            maxChild = 2*p+2; // 右孩子存在且右孩子大于左孩子，设定右孩子最大
        } else {
            maxChild = 2*p+1; // 否则左孩子最大
        }
        if (heap->D[p].key > heap->D[maxChild].key) {
            break ; //若当前节点大于最大的孩子，调整结束
        } else { // 否则将p和其最大的孩子交换
            temp = heap->D[p].key;
            heap->D[p].key = heap->D[maxChild].key;
            heap->D[maxChild].key = temp;
            p = maxChild; // 设置下轮循环待考察的元素的位置（即当前下移元素的位置）
        }
    }
}
// void CreateHeap(ElemType heap[], int n)
// {
//     int i;
//     for (i=(n-1)/2; i>-1; i--) { // 起始节点从非终端节点开始依次向前调整
//         AdjustDown(heap, i, n-1);
//     }
// }
void Print_arr(MaxHeap *hp)
{
    for (int i=0; i<8; i++) {
        printf("%d ", hp->D[i].key);
    }
}
void HeapSort(MaxHeap *hp)
{
    int i;
    Entry temp;
    for (i=(hp->n-2)/2; i>=0; i--) {
        AdjustDown(hp ,hp->D, i, hp->n-1);
    }
    for (i=hp->n-1; i>0; i--) { // i指向当前堆的堆底元素
        Swap(hp->D, 0, i); // 交换堆底与堆顶元素
        AdjustDown(hp ,hp->D, 0, i-1);
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