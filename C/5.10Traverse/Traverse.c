// 程序5.10 二叉树的非递归遍历算法

#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define OverFlow 2 // 上溢
#define UnderFlow 3 // 下溢
#define NotPresent 4 // 元素不存在
#define Duplicate 5 // 元素重复
#define STACKSIZE 100 // 栈容量
typedef char ElemType;
//--------二叉树
typedef struct btnode { // 定义二叉树结点结构体
    ElemType element;
    struct btnode *lChild;
    struct btnode *rChild;
} BTNode;
typedef struct binarytree { // 定义二叉树结构体
    BTNode *root;
} BinaryTree;
//--------堆栈
typedef struct stack { // 堆栈结构体的定义
    int top; // top为当前栈顶位置下标
    int maxSize; // maxSize-1为堆栈的最大栈顶位置下标
    BTNode **element; // element为存储堆栈元素的一维数组首地址的指针，存储BTNode*结点
} Stack;

void CreateStack(Stack *S, int mSize); // 创建一个能容纳mSize个单元的空堆栈
int IsEmpty(Stack *S); // 判断堆栈是否为空，若为空返回TRUE，否则返回FALSE
int IsFull(Stack *S); // 判断堆栈是否已满，若是，则返回TRUE，否则返回FALSE
BTNode *Top(Stack *S, BTNode **p); // 获取栈顶元素，通过x返回。返回栈顶元素
int Push(Stack *S, BTNode *p); // 在栈顶插入元素x（入栈）。若操作成功，则返回TRUE，否则返回FALSE
int Pop(Stack *S); // 删除栈顶元素（出栈）。若操作成功，则返回TRUE，否则返回FALSE

void PreMakeTree(BinaryTree *bt); // 先序遍历创建二叉树
BTNode *PreCreateBT(BTNode *t);

BTNode *GetFirst(BinaryTree *bt, Stack *S); // 获取中序遍历规则下待访问的第一个结点
BTNode *GetNext(BTNode *current, Stack *S); // 获取current结点在中序遍历规则下的下一个结点
void Traverse(BinaryTree *bt); // 按照中序遍历规则非递归遍历二叉树中所有结点

int main()
{
    BinaryTree a;
    PreMakeTree(&a); // 创建二叉树 // 例：BD##CE##F##
    Traverse(&a); // 非递归遍历

    return 0;
}
//-------栈操作
void CreateStack(Stack *S, int mSize)
{
    S->maxSize = mSize;
    S->element = (BTNode **)malloc(mSize*sizeof(BTNode*));
    S->top = -1;
}
int IsEmpty(Stack *S)
{
    return S->top == -1;
}
int IsFull(Stack *S)
{
    return S->top == S->maxSize - 1;
}
BTNode *Top(Stack *S, BTNode **p) // 获取并返回栈顶指针
{
    if (IsEmpty(S)) {
        return FALSE;
    }
    *p = S->element[S->top];
    return *p;
}
int Push(Stack *S, BTNode *p)
{
    if (IsFull(S)) {
        return FALSE;
    }
    S->top++;
    S->element[S->top] = p;
    return TRUE;
}
int Pop(Stack *S)
{
    if (IsEmpty(S)) {
        return FALSE;
    }
    S->top--;
    return TRUE;
}
//-------二叉树创建
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
//-------非递归二叉树中序遍历访问
BTNode *GetFirst(BinaryTree *bt, Stack *S) // 获取中序遍历规则下待访问的第一个结点
{
    BTNode *p = bt->root; // 创建临时结点指针p，并指向根结点
    if (!p) { // 若二叉树为空
        return NULL;
    }
    while (p->lChild != NULL) { //当结点的左孩子非空时
        Push(S, p); // 将结点进栈
        p = p->lChild; // 结点指向结点的左孩子
    }
    return p; // 找到并返回待访问的第一个结点
}
BTNode *GetNext(BTNode *current, Stack *S) // 获取current结点在中序遍历规则下的下一个结点
{
    BTNode *p; // 创建临时结点指针
    if (current->rChild != NULL) { // 如果当前结点的右孩子非空
        p = current->rChild; // 指针指向当前结点的右孩子
        while (p->lChild != NULL) { // 如果当前结点的左孩子非空
            Push(S, p); // 将结点进栈
            p = p->lChild; // 指针指向当前结点的左孩子
        }
        current = p; // 更新当前结点
    } else if (!IsEmpty(S)) { // 若当前栈非空
        Top(S, &current); // 获取栈顶结点，返回给current
        Pop(S); // 出栈
    } else {
        current == NULL; // 当前结点为空
        return NULL;
    }
    return current; // 返回当前结点
}
void Traverse(BinaryTree *bt) // 按照中序遍历规则非递归遍历二叉树中所有结点
{
    Stack S;
    BTNode *current; // 创建当前结点
    CreateStack(&S, STACKSIZE); // 创建栈
    current = GetFirst(bt, &S); // 获取第一个结点作为当前结点
     while (current) { // 若当前结点存在
        printf("%c ", current->element); // 访问结点
        current = GetNext(current, &S); // 获取下一个结点作为当前结点
    }
}
