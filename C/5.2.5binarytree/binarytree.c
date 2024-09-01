// 二叉树的抽象数据类型定义
#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
typedef char ElemType;
typedef struct btnode { // 定义二叉树结点结构体
    ElemType element;
    struct btnode *lChild;
    struct btnode *rChile;
} BTNode;
typedef struct binarytree { // 定义二叉树结构体
    BTNode *root;
} BinaryTree;

// 运算：
void Create(BinaryTree *bt); // 创建二叉树bt
BTNode *NewNode(ElemType x, BTNode *ln, BTNode *rn); // 创建一个新结点，该结点的值为x，ln和rn为该结点的左右孩子的结点
int IsEmpty(); // 若二叉树bt为空，则返回TRUE，否则返回FALSE
int Root(BinaryTree *bt, ElemType *x); // 若二叉树bt非空，则用x返回其根结点的值，并返回TRUE，否则返回FALSE
void MakeTree(BinaryTree *bt, ElemType e, BinaryTree *left, BinaryTree *right); // 构造一棵二叉树bt，根结点值为x，以left和right为该根结点的左右子树

int main()
{
    BinaryTree a,b,x,y,z;
    Create(&a);
    Create(&b);
    Create(&x);
    Create(&y);
    Create(&z);
    MakeTree(&y, 'E', &a, &b);
    MakeTree(&z, 'F', &a, &b);
    MakeTree(&x, 'C', &y, &z);
    MakeTree(&y, 'D', &a, &b);
    MakeTree(&z, 'B', &y, &x);
}

void Create(BinaryTree *bt)
{
    bt->root = NULL;
}
BTNode *NewNode(ElemType x, BTNode *ln, BTNode *rn)
{
    BTNode *p = (BTNode *)malloc(sizeof(BTNode));
    p->element = x;
    p->lChild = ln;
    p->rChile = rn;
    return p;
}
int Root(BinaryTree *bt, ElemType *x)
{
    if (bt->root) {
        x = &bt->root->element;
        return TRUE;
    } else {
        return FALSE;
    }
}
void MakeTree(BinaryTree *bt, ElemType e, BinaryTree *left, BinaryTree *right)
{
    if (bt->root || left == right) {
        return ;
    }
    bt->root = NewNode(e, left->root, right->root);
    left->root = right->root = NULL;
}