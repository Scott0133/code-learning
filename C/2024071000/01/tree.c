//二叉树初探
/*
二叉树顺序存储————只适合存储完全二叉树
基本操作：
            i的左孩子————2i
            i的右孩子————2i+1
            i的父节点————[i/2]
            i所在的层次————[log2^(n+1)]或[log2n]+1

若完全二叉树中有n个结点：
            判断i是否有左孩子————2i<=n ? 是：否
            判断i是否有右孩子————2i+1<=n ? 是：否
            判断i是否是叶子/分支节点————i>[n/2] ? 是：否
*/
#include<stdio.h>
#include<stdlib.h>
//以下为二叉树的链式存储
/*
n个结点的二叉链表共有n+1个空指针域
二叉树的遍历：
            先序遍历：根左右（NLR）
            中序遍历：左根右（LNR）
            后序遍历：左右根（LRN）
*/

//二叉树结点（链式存储
typedef struct BiTNode {
    int data;                           //数据域
    struct BiTNode *lchild, *rchild;    //左、右孩子指针
}BiTNode, *BiTree;

BiTree root = NULL;                     //定义一颗空树

void newnode(BiTree *T, int x);
void PreOrder(BiTree T);                        //先序遍历
void Visit(BiTree T);                           //访问结点
int treeDepth(BiTree T);                        //返回树的深度————后序遍历的应用

int main()
{
    root = (BiTree)malloc(sizeof(BiTNode));
    root->lchild = NULL;                        //将根结点的左孩子的指针域置空
    root->rchild = NULL;                        //将根结点的右孩子的指针域置空
    root->data = 1;                             //根结点存入数据1
}
void Visit(BiTree T)
{
    printf("%d ", T->data);
}

void PreOrder(BiTree T)
{
    if (T != NULL)
    {
        visit(T);
        PreOrder(T->lchild);
        PreOrder(T->rchild);
    }
}

int treeDepth(BiTree T)
{
    if (T == NULL)
    {
        return  0;
    }
    else
    {
        int l = treeDepth(T->lchild);
        int r = treeDepth(T->rchild);
        return l>r ? l+1 : r+1;
    }
}

// void newnode(BiTree *T, int x)
// {
//     BiTNode * p = (BiTNode*)malloc(sizeof(BiTNode));    //为新结点分配空间
//     p->data = x;                                        //将x作为数据存入
//     p->lchild = NULL;                                   //将左右指针域置空
//     p->rchild = NULL;
//     if (2*i <= n)               //若当前结点没有左孩子
//     {
//         (*root)->lchild = p;
//     }
//     else
//     {
//         (*root)->rchild = p;
//     }
// }