// 程序5.11 基于完全二叉树的小根堆建立

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

int main()
{
    int testarr[] = {61, 28, 81, 43, 36, 47, 83, 5};
    CreateHeap(testarr, 8);

    return 0;
}

void AdjustDown(ElemType heap[], int current, int border)
{
    int p = current;
    int minChild;
    ElemType temp;
    while (2*p+1 <= border) { // 若p不是叶子结点则调整
        if ((2*p+2 <= border) && (heap[2*p+1] > heap[2*p+2])) {
            minChild = 2*p+2; // 右孩子存在，且较大，则minChild指向p的右孩子
        } else {
            minChild = 2*p+1; // 右孩子不存在，或较大，则minChild指向p的左孩子
        }
        if (heap[p] <= heap[minChild]) {
            break; // 若当前节点不大于其最小的孩子，则调整结束
        } else { // 否则将p和其最小的孩子交换
            temp = heap[p];
            heap[p] = heap[minChild];
            heap[minChild] = temp;
            p = minChild; // 设置下轮循环待考察的元素的位置（即当前下移元素的位置）
        }
    }
}
void CreateHeap(ElemType heap[], int n)
{
    int i;
    for (i=(n-2)/2; i>-1; i--) {
        AdjustDown(heap, i, n-1);
    }
}