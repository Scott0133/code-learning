// 二叉树的先、中、后序遍历
// 二叉树的抽象数据类型定义
// 程序5.7 求二叉树的结点数
// 程序5.8 清空二叉树
// 程序5.9 先序遍历构建二叉树
#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
typedef char ElemType;
typedef struct btnode { // 定义二叉树结点结构体
    ElemType element;
    struct btnode *lChild;
    struct btnode *rChild;
} BTNode;
typedef struct binarytree { // 定义二叉树结构体
    BTNode *root;
} BinaryTree;

// 运算：
void Create(BinaryTree *bt); // 创建二叉树bt
BTNode *NewNode(ElemType x, BTNode *ln, BTNode *rn); // 创建一个新结点，该结点的值为x，ln和rn为该结点的左右孩子的结点
int IsEmpty(); // 若二叉树bt为空，则返回TRUE，否则返回FALSE
int Root(BinaryTree *bt, ElemType *x); // 若二叉树bt非空，则用x返回其根结点的值，并返回TRUE，否则返回FALSE
void MakeTree(BinaryTree *bt, ElemType e, BinaryTree *left, BinaryTree *right); // 构造一棵二叉树bt，根结点值为e，以left和right为该根结点的左右子树
// void Visit(BinaryTree *bt); // 访问当前结点
void PreOrderTree(BinaryTree *bt); // 二叉树的先序遍历
void PreOrder(BTNode *t); // 先序遍历主流程
void InOrderTree(BinaryTree *bt); // 二叉树中序遍历
void InOrder(BTNode *t); // 中序遍历主流程
void PostOrderTree(BinaryTree *bt); // 二叉树后序遍历
void PostOrder(BTNode *t); // 后序遍历主流程
int TreeSize(BinaryTree *bt); // 返回二叉树结点数
int Size(BTNode *t); // 求二叉树的结点数，Size()本质是后序遍历算法
void TreeClear(BinaryTree *bt); // 清空二叉树
void Clear(BTNode *t); // 清空二叉树，本质是后序遍历算法
// 先序遍历构建二叉树
void PreMakeTree(BinaryTree *bt); // 先序遍历创建二叉树
BTNode *PreCreateBT(BTNode *t);

int main()
{
    // // BinaryTree a,b,x,y,z;
    // // Create(&a);
    // // Create(&b);
    // // Create(&x);
    // // Create(&y);
    // // Create(&z);
    // // MakeTree(&y, 'E', &a, &b);
    // // MakeTree(&z, 'F', &a, &b);
    // // MakeTree(&x, 'C', &y, &z);
    // // MakeTree(&y, 'D', &a, &b);
    // // MakeTree(&z, 'B', &y, &x); // 现在x为0x00
    //     // 定义五个二叉树变量，并使用初始化函数将他们初始化为空二叉树，然后调用maketree函数逐步构建二叉树
    // BinaryTree a; // 创建二叉树结构体a
    // BinaryTree b;
    // BinaryTree c;
    // BinaryTree d;
    // BinaryTree e;
    // BinaryTree x; BinaryTree y; // x，y为临时结点，置空
    // Create(&a); // a,b,c,d,e均为空结点
    // Create(&b);
    // Create(&c);
    // Create(&d);
    // Create(&e);
    // Create(&x); Create(&y); // 临时结点x，y
    // MakeTree(&d, 'D', &x, &y); // 叶子结点D，置空
    // MakeTree(&e, 'E', &x, &y); // 叶子节点E，置空
    // MakeTree(&c, 'C', &d, &e); // C为D,E的根节点
    // MakeTree(&b, 'B', &x, &y); // 叶子节点B，置空
    // MakeTree(&a, 'A', &b, &c); // 根节点A左子树为B，右子树为C
    // // 遍历二叉树
    // PreOrderTree(&a); // 先序遍历二叉树a
    // printf("\n");
    // InOrderTree(&a); // 中序遍历二叉树a
    // printf("\n");
    // PostOrderTree(&a); // 后续遍历二叉树a

    // int treesize = TreeSize(&a); // 计算二叉树结点数
    // printf("\ntreesize is %d", treesize);

    // TreeClear(&a); // 清空二叉树
    // return 0;
    BinaryTree a;
    PreMakeTree(&a); // 先序遍历构造二叉树 // 例：BD##CE##F##
    PreOrderTree(&a); // 先序遍历二叉树
    return 0;
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
    p->rChild = rn;
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
    // Visit(bt);
}
void PreOrderTree(BinaryTree *bt)
{
    PreOrder(bt->root);
}
void PreOrder(BTNode *t)
{
    if (!t) {
        return ;
    }
    printf("%c ", t->element); // 访问结点
    PreOrder(t->lChild);
    PreOrder(t->rChild);
}
void InOrderTree(BinaryTree *bt)
{
    InOrder(bt->root);
}
void InOrder(BTNode *t)
{
    if (!t) {
        return ;
    }
    InOrder(t->lChild);
    printf("%c ", t->element);
    InOrder(t->rChild);
}
void PostOrderTree(BinaryTree *bt)
{
    PostOrder(bt->root);
}
void PostOrder(BTNode *t)
{
    if (!t) {
        return ;
    }
    PostOrder(t->lChild);
    PostOrder(t->rChild);
    printf("%c ", t->element);
}
int TreeSize(BinaryTree *bt)
{
    return Size(bt->root);
}
int Size(BTNode *t)
{
    if (!t) {
        return 0;
    } else {
        return Size(t->lChild) + Size(t->rChild) + 1;
    }
}
void TreeClear(BinaryTree *bt)
{
    Clear(bt->root);
}
void Clear(BTNode *t)
{
    if (!t) {
        return;
    }
    Clear(t->lChild);
    Clear(t->rChild);
    free(t);
}
void PreMakeTree(BinaryTree *bt)
{
    bt->root = PreCreateBT(bt->root);
}
BTNode *PreCreateBT(BTNode *t)
{
    char ch;
    ch = getchar();
    if (ch == '#') { // 空结点
        t = NULL;
    } else { // 创建结点
        t = (BTNode *)malloc(sizeof(BTNode));
        t->element = ch; // 构造根结点
        t->lChild = PreCreateBT(t->lChild); // 构造左子树
        t->rChild = PreCreateBT(t->rChild); // 构造右子树
    }
    return t;
}
// void Visit(BinaryTree *bt)
// {
//     printf("%c, ", bt->root->element);
// }