// 定义二叉树
// false，因插入函数修改不便，改用顺序存储
// 不使用顺序存储，无法进行二叉树中序遍历。。
#include<stdio.h>
#include<stdlib.h>
#define TRUE 0
#define FALSE 1

typedef struct btnode { // 定义二叉树结点结构体
    int data; // 权值
    int *Lchild;
    int *Rchild;
} BTNode;
typedef struct binarytree { // 定义二叉树结构体
    int n; // 结点数量
    BTNode *root; // 根结点指针
} BinaryTree;

int InitTree(BinaryTree *T); // 初始化二叉树，参数为二叉树结构体
int Insert(BinaryTree *T, int data); // 二叉树插入操作，参数为二叉树结构体，权值
void InOrder(BinaryTree T); // 中序遍历二叉树


int main()
{
    BinaryTree T; // 定义二叉树结构体
    InitTree(&T); // 初始化二叉树
}

int InitTree(BinaryTree *T)
{
    T->n = 0; // 结点数为0
}
int Insert(BinaryTree *T, int data)
{
    if (T->root == NULL) {
        BTNode *node = (BTNode *)malloc(sizeof(BTNode)); // 为新结点分配栈空间作为根结点
    }
}