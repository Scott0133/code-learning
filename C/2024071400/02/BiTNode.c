//二叉树的链式存储（无序）
#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE -1

typedef struct BiTNode {
    int data;
    struct BiTNode *Lchild;
    struct BiTNode *Rchild;
}BiTNode,*BiTree;

int InitBiTree(BiTree* root);
int Insert(BiTree* root, int data, int flag);

int main()
{
    BiTree root;
    InitBiTree(&root);           //以root作为根结点并data赋值0
    Insert(&root, 10, 1);        //temp作为root的左孩子
    Insert(&root, 20, 0);        //右
}

int InitBiTree(BiTree* root)
{
    (*root) = (BiTNode*)malloc(sizeof(BiTNode));
    (*root)->data = 0;
    (*root)->Lchild = NULL;
    (*root)->Rchild = NULL;
    return TRUE;
}

int Insert(BiTree* root, int data, int flag)
{
    BiTNode *temp = (BiTNode*)malloc(sizeof(BiTNode));  //新结点并初始化
    temp->data = data;
    temp->Lchild = NULL;
    temp->Rchild = NULL;
    if (flag == 1)
        (*root)->Lchild = temp;    //将新结点作为根结点的左孩子
    else 
        (*root)->Rchild = temp;

    return TRUE;
}