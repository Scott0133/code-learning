// 基于小根堆（小顶堆）的堆排序、插入与删除

// 堆排序（不稳定性）
// i的父节点：[i/2]（向下取整）
// 节点下标：i
// 左子节点下标：2i+1
// 右子节点下标：2i+2
// 大根堆：根>=左、右   小根堆：根<=左、右

// v2：建立小根堆
// v3：基于小根堆的插入/删除（静态数组）
// 思路：将数组映射为[顺序二叉树]，检查所有非终端结点，是否满足小根堆要求，若不满足要求则调整
// 顺序存储的完全二叉树中，非终端节点编号i<=n/2
#include<stdio.h>
#define INF 999 // 定义空

void swap(int *a, int *b);
void BuildMinHeap(int A[], int len); // 建立小根堆
void HeadAdjust_v2(int A[], int k, int len); // 调整结点位置（以k为根的子树调整为小根堆）
void HeapSort_v2(int A[], int k, int len); // 堆排序主流程
void Print(int A[], int len);
void Insert(int A[], int n, int *len); // 在小根堆中插入新元素n，用指针返回len
void Delete(int A[], int x, int *len); // 在小根堆中删除x元素位置，用指针返回len

int main()
{
    int A[20] = {0, 53, 17, 78, 9, 45, 65, 87, 32}; // A[0]保留作为暂存
    int n = sizeof(A) / sizeof(A[0]) - 1; // len=实际数组长度-1
    int len = 8; // 未调用函数所以直接写值了
    // HeapSort_v2(A, 1, len); // 基于小根堆排序（得到递减序列）
    BuildMinHeap(A, len); // 建立小根堆
    Insert(A, 13, &len); // 在小根堆中插入元素13
    Insert(A, 46, &len); // 插入元素46
    Delete(A, 2, &len); // 删除数组下标2的元素
    Delete(A, 3, &len); // 删除数组下标3的元素
    Print(A, n);
    //printf("len is %d ", len);
    return 0;
}

void swap(int *a, int *b) // 交换数组元素
{
    int temp = 0;
    temp = *b;
    *b = *a;
    *a = temp;
}
// 建立小根堆
void BuildMinHeap(int A[], int len)
{
    for (int i=len/2 ; i>0; i--) { // 从后往前调整所有非终端结点
        HeadAdjust_v2(A, i, len); // 将每个结点调整为小根堆
    }
}
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
void Insert(int A[], int n, int *len)
{
    int i = *len + 1; // 设i为数组表尾
    A[i] = n; // 将n插入数组表尾
    int temp;
    int p = i/2; // 父节点位置
    while (A[i] < A[p]) { // 若新元素的值更小
        swap(&A[i], &A[p]); // 交换数据值
        i = p; // 将i设置为父节点
        p = i/2; // 下一个父节点
    }
    *len = *len + 1; // 数组长度加1
}
void Delete(int A[], int x, int *len)
{
    A[x] = INF; //A[x]的元素被删除
    A[x] = A[*len]; // 用堆底元素代替删除元素
    A[*len] = INF; // 堆底元素置空
    *len = *len - 1; // 数组长度减1
    BuildMinHeap(A, *len); // 用下坠法保持小根堆特性
}