// 寻找根结点到叶子节点是否有路径之和为k（bug）

// 通过给出的先序、中序遍历创建二叉树（递归算法） 
// copilot：你的代码逻辑基本正确，但在处理节点到叶子节点路径时漏掉了适当的递归路径更新。可以通过增加辅助函数，便于在路径上逐步累加检查

#include <stdio.h>
#include <stdlib.h>
#define TRUE 0
#define FALSE 1

typedef struct BstNode {
    int data;
    struct BstNode *Lchild;
    struct BstNode *Rchild;
} BstNode;

BstNode *CreateTree(int Pre[], int In[], int l1, int h1, int l2, int h2) {
    if (h1 < l1) {
        return NULL;
    }

    BstNode *root = (BstNode *)malloc(sizeof(BstNode));
    root->data = Pre[l1];
    
    int i;
    for (i = l2; i <= h2; i++) {
        if (In[i] == Pre[l1]) {
            break;
        }
    }

    root->Lchild = CreateTree(Pre, In, l1 + 1, l1 + i - l2, l2, i - 1);
    root->Rchild = CreateTree(Pre, In, l1 + i - l2 + 1, h1, i + 1, h2);

    return root;
}
int FindPath(BstNode *root, int sum) // 找到一条根节点到叶子节点路径之和为k的路径
{
    if (root == NULL) {
        return FALSE;
    }
    if (root->Lchild == NULL && root->Rchild == NULL) { // 此时为叶子结点
        if (sum == root->data) { // sum的值为总和（递归出口）
            return TRUE;
        } else {
            return FALSE;
        }
    }
    return FindPath(root->Lchild, sum-root->data) || FindPath(root->Rchild, sum-root->data);
}


int main() {
    int Pre[] = {1, 2, 4, 5, 3, 7, 10};
    int In[] = {4, 2, 5, 1, 7, 3, 10};
    int n = sizeof(Pre) / sizeof(Pre[0]);

    BstNode *root = (BstNode *)malloc(sizeof(BstNode));
    root = CreateTree(Pre, In, 0, n - 1, 0, n - 1); // 创建二叉树（普通二叉树）
    int ret = FindPath(root, 7);


    return 0;
}
