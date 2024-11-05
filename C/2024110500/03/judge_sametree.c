// 判断t2是否为t1的子树

// 通过给出的先序、中序遍历创建二叉树（递归算法） 

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
int CheckSubTree(BstNode *t1, BstNode *t2) // 判断二叉树的子树是否相等（bug？）
{
    if (t1 == NULL && t2 == NULL) { // 递归出口
        return TRUE;
    } else if (t1 == NULL || t2 == NULL) { // 若t1与t2其中一个为空
        return FALSE;
    }
    if (t1->data == t2->data) { // 若t1根数据和t2根数据相同
        int left = CheckSubTree(t1->Lchild, t2->Lchild); // 递归查找左边子树
        int right = CheckSubTree(t1->Rchild, t2->Rchild); // 递归查找右边子树
        return left && right; // 注意返回值与运算
    } else {
        int left = CheckSubTree(t1->Lchild, t2); // 若为t1左子树的子树
        int right = CheckSubTree(t1->Rchild, t2); // 若为t1右子树的子树
        return left || right; // 这里返回值为或运算，因为递归长度可能不等
    }
}
// ----------------------------------------------------- copilot
int isSameTree_co(BstNode *t1, BstNode *t2) {
    if (t1 == NULL && t2 == NULL) {
        return TRUE;
    }
    if (t1 == NULL || t2 == NULL) {
        return FALSE;
    }
    if (t1->data != t2->data) {
        return FALSE;
    }
    return isSameTree_co(t1->Lchild, t2->Lchild) && isSameTree_co(t1->Rchild, t2->Rchild);
}

int CheckSubTree_co(BstNode *t1, BstNode *t2) {
    if (t2 == NULL) {
        return TRUE; // 空子树是任何树的子树
    }
    if (t1 == NULL) {
        return FALSE; // 非空子树不能是空树的子树
    }
    if (isSameTree_co(t1, t2)) {
        return TRUE;
    }
    return CheckSubTree_co(t1->Lchild, t2) || CheckSubTree_co(t1->Rchild, t2);
}
// ----------------------------------------------------- copilot

int main() {
    int Pre_t1[] = {1, 2, 4, 3};
    int In_t1[] = {4, 2, 3, 1};
    int Pre_t2[] = {2, 4, 3};
    int In_t2[] = {4, 2, 3};

    int n_t1 = sizeof(Pre_t1) / sizeof(Pre_t1[0]);
    int n_t2 = sizeof(Pre_t2) / sizeof(Pre_t2[0]);

    BstNode *root_t1 = (BstNode *)malloc(sizeof(BstNode));
    BstNode *root_t2 = (BstNode *)malloc(sizeof(BstNode));
    root_t1 = CreateTree(Pre_t1, In_t1, 0, n_t1 - 1, 0, n_t1 - 1); // 创建t1
    root_t2 = CreateTree(Pre_t2, In_t2, 0, n_t2 - 1, 0, n_t2 - 1); // t2

    int ret = CheckSubTree_co(root_t1, root_t2);




    return 0;
}
