// 程序 基于完全二叉树的大根堆建立

#include<stdio.h>
#define TRUE 1
#define FALSE 0
#define OverFlow 2 // 上溢
#define UnderFlow 3 // 下溢
#define NotPresent 4 // 元素不存在
#define Duplicate 5 // 元素重复
typedef int ElemType;

void AdjustDown(ElemType heap[], int current, int border);
void CreateHeap(ElemType heap[], int n);
void Visit(ElemType heap[], int p);
void Print_arr(int *arr);
int main()
{
    int testarr[] = {61, 28, 81, 43, 36, 47, 83, 5}; // 测试数组
    CreateHeap(testarr, 8);
    Print_arr(testarr);
    
    return 0;
}

void AdjustDown(ElemType heap[], int current, int border) // 元素下坠法调整为大根堆
{
    int p = current; // 将变量p指向当前考察元素
    int minChild; // 当前考察元素中最小的一个孩子
    int maxChild; // 当前考察元素中最大的一个孩子
    ElemType temp;
    while (2*p+1 <= border) { // 若p不是叶子结点则调整
        if ((2*p+2 <= border) && (heap[2*p+1] < heap[2*p+2])) { // 2*p+1为左孩子，2*p+2为右孩子
            maxChild = 2*p+2; // 右孩子存在且右孩子大于左孩子，设定右孩子最大
        } else {
            maxChild = 2*p+1; // 否则左孩子最大
        }
        if (heap[p] > heap[maxChild]) {
            break ; //若当前节点大于最大的孩子，调整结束
        } else { // 否则将p和其最大的孩子交换
            temp = heap[p];
            heap[p] = heap[maxChild];
            heap[maxChild] = temp;
            p = maxChild; // 设置下轮循环待考察的元素的位置（即当前下移元素的位置）
        }
    }
}
void CreateHeap(ElemType heap[], int n)
{
    int i;
    for (i=(n-1)/2; i>-1; i--) { // 起始节点从非终端节点开始依次向前调整
        AdjustDown(heap, i, n-1);
    }
}
void Visit(ElemType heap[], int p)
{
    printf("visited %d\n", heap[p]);
}
void Print_arr(int *arr)
{
    for (int i=0; i<8; i++) {
        printf("%d ", arr[i]);
    }
}