// 堆排序（不稳定性）
// i的父节点：[i/2]（向下取整）
// 节点下标：i
// 左子节点下标：2i+1
// 右子节点下标：2i+2
// 大根堆：根>=左、右   小根堆：根<=左、右

// 建立大根堆
// 思路：将数组映射为[顺序二叉树]，检查所有非终端结点，是否满足大根堆要求，若不满足要求则调整
// 顺序存储的完全二叉树中，非终端节点编号i<=n/2
#include<stdio.h>
#define INF 999

void swap(int *a, int *b);
void BuildMaxHeap(int A[], int len); // 建立大根堆
void HeadAdjust(int A[], int k, int len); // 调整结点位置（以k为根的子树调整为大根堆）
void HeapSort(int A[], int k, int len); // 堆排序主流程
void Print(int A[], int len);

int main()
{
    int A[] = {0, 53, 17, 78, 9, 45, 65, 87, 32}; // A[0]保留做为暂存
    int len = sizeof(A) / sizeof(A[0]) - 1; // len=实际数组长度-1
    HeapSort(A, 1, len); // （基于大根堆的堆排序得到递增序列）
    Print(A, len);

    return 0;
}

void swap(int *a, int *b)
{
    int temp = 0;
    temp = *b;
    *b = *a;
    *a = temp;
}
// 建立大根堆
void BuildMaxHeap(int A[], int len)
{
    for (int i=len/2; i>0; i--) { // 从后往前调整所有非终端结点（所有非终端结点<=n/2）
        HeadAdjust(A, i, len);
    }
}
// 将以k为根的子树调整为大根堆
void HeadAdjust(int A[], int k, int len) { // （元素下坠法）
    A[0] = A[k]; // A[0]暂存子树的根结点（A[0]待处理）
    for (int i=2*k; i<=len; i*=2) { // 沿key较大的子结点向下筛选（i指向当前结点左孩子，长度，i指向k结点的左孩子）
        if (i<len && A[i]<A[i+1]) { // i<len保证i有右兄弟，比较左孩子和右孩子大小
            i++; // 取较大的左右孩子结点下标
        }
        if (A[0] >= A[i])   break; // 筛选结束
        else {
            A[k] = A[i]; // 将A[i]调整到双亲结点上
            k = i; // 修改k值，以便继续向下筛选
        }
    }
    A[k] = A[0]; // 被筛选结点的值放入最终位置
}
// 基于大根堆进行排序（基于大根堆排序得到递增序列）
void HeapSort(int A[], int k, int len) {
    BuildMaxHeap(A, len); // 初始建堆
    for (int i=len; i>1; i--) { // n-1趟的交换和建堆过程（i指向待排序元素序列中的最后一个，每趟处理后i前移）
        swap(&A[i], &A[1]); // 堆顶元素和堆底元素交换
        HeadAdjust(A, 1, i-1); // 把剩余的待排序元素整理成堆（第i个元素已有序，故传入元素为i-1）
    }
}
void Print(int A[], int len)
{
    for (int i=1; i<=len; i++) {
        printf("%d ", A[i]);
    }
}

// 基于小根堆的元素插入删除