// 基于小根堆（小顶堆）的堆排序

// 堆排序（不稳定性）
// i的父节点：[i/2]（向下取整）
// 节点下标：i
// 左子节点下标：2i+1
// 右子节点下标：2i+2
// 大根堆：根>=左、右   小根堆：根<=左、右

// v2：建立小根堆
// 思路：将数组映射为[顺序二叉树]，检查所有非终端结点，是否满足小根堆要求，若不满足要求则调整
// 顺序存储的完全二叉树中，非终端节点编号i<=n/2
#include<stdio.h>
#define INF 999 // 定义上限

void swap(int *a, int *b);
// void BuildMaxHeap(int A[], int len); // 建立大根堆
void BuildMinHeap(int A[], int len);
// void HeadAdjust(int A[], int k, int len); // 调整结点位置（以k为根的子树调整为大根堆）
void HeadAdjust_v2(int A[], int k, int len);
// void HeapSort(int A[], int k, int len); // 堆排序主流程
void HeapSort_v2(int A[], int k, int len);
void Print(int A[], int len);
void Insert(int A[], int a); // 在小根堆中插入新元素
void Delete(int A[], int x); // 在小根堆中删除元素

int main()
{
    int A[] = {0, 53, 17, 78, 9, 45, 65, 87, 32}; // A[0]保留作为暂存
    int len = sizeof(A) / sizeof(A[0]) - 1; // len=实际数组长度-1
    // HeapSort(A, 1, len); // （基于大根堆的堆排序得到递增序列）
    HeapSort_v2(A, 1, len); // 基于小根堆排序
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
// // 建立大根堆
// void BuildMaxHeap(int A[], int len)
// {
//     for (int i=len/2; i>0; i--) { // 从后往前调整所有非终端结点（所有非终端结点<=n/2）
//         HeadAdjust(A, i, len);
//     }
// }

// 建立小根堆
void BuildMinHeap(int A[], int len)
{
    for (int i=len/2 ; i>0; i--) { // 从后往前调整所有非终端结点
        HeadAdjust_v2(A, i, len); // 将每个结点调整为小根堆
    }
}


// // 将以k为根的子树调整为大根堆
// void HeadAdjust(int A[], int k, int len) { // （元素下坠法）
//     A[0] = A[k]; // A[0]暂存子树的根结点（A[0]待处理）
//     for (int i=2*k; i<=len; i*=2) { // 沿key较大的子结点向下筛选（i指向当前结点左孩子，长度，i指向k结点的左孩子）
//         if (i<len && A[i]<A[i+1]) { // i<len保证i有[右兄弟]，比较左孩子和右孩子大小
//             i++; // 取较大的左右孩子结点下标
//         }
//         if (A[0] >= A[i])   break; // 筛选结束
//         else {
//             A[k] = A[i]; // 将A[i]调整到双亲结点上
//             k = i; // 修改k值，以便继续向下筛选
//         }
//     }
//     A[k] = A[0]; // 被筛选结点的值放入最终位置
// }
void HeadAdjust_v2(int A[], int k, int len) // 以k为根的子树[调整]小根堆
{
    A[0] = A[k]; // A[0]暂存将要调整的结点
    for (int i=2*k; i<=len; i*=2) { // （i指向当前节点左孩子，长度，i指向当前节点的下一个左孩子）
        if (i<len && A[i]>A[i+1]) { // i<len保证当前节点i有右兄弟，如果左孩子值大于右孩子
            i++; // 取右孩子的值（值较小的一个）
        }
        if (A[0] <= A[i])   break; // 如果当前根节点的值为最小，结束筛选
        else { // 根节点值不为最小，继续筛选
            A[k] = A[i]; // 将A[i]调整到双亲结点上
            k = i; // 修改key值，继续筛选
        }
    }
    A[k] = A[0]; // 被筛选结点放入最终位置
}

// // 基于大根堆进行排序（基于大根堆排序得到递增序列）
// void HeapSort(int A[], int k, int len) {
//     BuildMaxHeap(A, len); // 初始建堆
//     for (int i=len; i>1; i--) { // n-1趟的交换和建堆过程（i指向待排序元素序列中的最后一个，每趟处理后i前移）
//         swap(&A[i], &A[1]); // 堆顶元素和堆底元素交换
//         HeadAdjust(A, 1, i-1); // 把剩余的待排序元素整理成堆（第i个元素已有序，故传入元素为i-1）
//     }
// }
void HeapSort_v2(int A[], int k, int len) // 基于小根堆进行排序（基于小根堆排序得到递减序列）
{
    BuildMinHeap(A, len); // 建立小根堆
    for (int i=len; i>1; i--) { // 进行n-1趟排序
        swap(&A[i], &A[1]); // 栈顶元素与栈底元素交换（将最小的元素换到栈顶）
        HeadAdjust_v2(A, 1, i-1); // 将剩余元素排序整理为小根堆
    }
}

void Print(int A[], int len)
{
    for (int i=1; i<=len; i++) {
        printf("%d ", A[i]);
    }
}

// 基于小根堆的元素插入删除