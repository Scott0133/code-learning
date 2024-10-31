// 通过给出的先序、中序遍历创建二叉树（递归算法） 
// bug
#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE -1

typedef struct BstNode {            //定义二叉树结构
    int data;
    struct BstNode *Lchild;
    struct BstNode *Rchild;
}BstNode;


BstNode *CreateTree(int Pre[], int In[], int h1, int l1, int l2, int h2); // 传入参数为pre数组，in数组，pre的起始坐标，pre的终止坐标，in的起始坐标，in的终止坐标
BstNode *CreateTree_v2(int Pre[], int In[], int l1, int h1, int l2, int h2); // by copilot
void InOrder(BstNode *root);

int main()
{
    int Pre[] = {1, 2, 4, 5, 3, 6, 7}; // 前序遍历数组
    int In[] = {4, 2, 5, 1, 6, 3, 7}; // 中序遍历数组
    int size = sizeof(Pre) / sizeof(Pre[0]);
    BstNode *temproot;
    temproot = CreateTree_v2(Pre, In, 0, size-1, 0, size-1);
    InOrder(temproot);

    return 0;
}

BstNode *CreateTree(int Pre[], int In[], int l1, int h1, int l2, int h2) // 传入参数为pre数组，in数组，pre的起始坐标，pre的终止坐标，in的起始坐标，in的终止坐标
{
    if (h1 < l1) { // 先序的结束坐标小于起始坐标
        return NULL;
    }
    BstNode *root = (BstNode*)malloc(sizeof(BstNode)); // 创建根结点
    root->data = Pre[l1]; // 根结点的起始位

    int i; // 定义i为根结点在中序中的下标

    for (i=l2; i<=h2 && In[i]!=Pre[l1]; i++) {
        if (i == l2) { // 中序的左边没有元素
            root->Lchild = NULL;
        } else {
            root->Lchild = CreateTree(Pre, In, l1+1, l1+i-l2, l2, i-1); // 递归建立左子树
        }
        if (i == h2) { // 中序的右边没有元素
            root->Rchild = NULL;
        } else {
            root->Rchild = CreateTree(Pre, In, l1+i-l2+1, h1, i+1, h2); // 递归建立右子树
        }
    }
    return root;
}
void InOrder(BstNode *root)
{
    if (root == NULL) {
        return ;
    }
    InOrder(root->Lchild);
    printf("%d ", root->data);
    InOrder(root->Rchild);
}

BstNode *CreateTree_v2(int Pre[], int In[], int l1, int h1, int l2, int h2) {
    if (h1 < l1) { // 先序的结束坐标小于起始坐标
        return NULL;
    }

    BstNode *root = (BstNode*)malloc(sizeof(BstNode)); // 创建根结点
    root->data = Pre[l1]; // 根结点的起始位

    int i; // 定义i为根结点在中序中的下标
    for (i = l2; i <= h2; i++) {
        if (In[i] == Pre[l1]) {
            break;
        }
    }

    if (i == l2) { // 中序的左边没有元素
        root->Lchild = NULL;
    } else {
        root->Lchild = CreateTree(Pre, In, l1 + 1, l1 + i - l2, l2, i - 1); // 递归建立左子树
    }
    
    if (i == h2) { // 中序的右边没有元素
        root->Rchild = NULL;
    } else {
        root->Rchild = CreateTree(Pre, In, l1 + i - l2 + 1, h1, i + 1, h2); // 递归建立右子树
    }

    return root;
}
