// 堆排序
// i的父节点：[i/2]（向下取整）
// 节点下标：i
// 左子节点下标：2i+1
// 右子节点下标：2i+2
// 大根堆：根>=左、右   小根堆：根<=左、右

// 思路：将数组映射为顺序二叉树，检查所有终端节点，是否满足堆要求，若不满足要求则调整
#include<stdio.h>
#define INF 999

int main()
{
    int A[] = {0, 53, 17, 78, 9, 45, 65, 87, 32}; // 建立大根堆，A[0]保留做为暂存
}