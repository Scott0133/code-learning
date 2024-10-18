// 程序5.15哈夫曼树————最小加权路径长度的扩充二叉树算法
// 辅助数据结构：
    // 二叉链表数据结构
    // 优先权队列数据结构
#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define OverFlow 2 // 上溢
#define UnderFlow 3 // 下溢
#define NotPresent 4 // 元素不存在
#define Duplicate 5 // 元素重复
typedef int ElemType;
typedef int BOOL;
// typedef int ElemType_PQ;

typedef struct btnode { // 定义二叉树结点结构体
    ElemType element; // 根结点权值，数据类型为可比较的整型
    struct btnode *lChild;
    struct btnode *rChild;
} BTNode;
typedef struct binarytree { // 定义二叉树结构体
    BTNode *root;
} BinaryTree;
typedef struct priorityQueue { // 优先权队列结构体
    BinaryTree *elements_PQ; // 存储元素的数组 // 以根结点存储的权值为优先级存储二叉树
    int n; // 优先权队列中元素的数量
    int maxSize; // 优先权队列的容量
}PriorityQueue;
// 二叉链表操作
void Create(BinaryTree *bt); // 创建二叉树bt
BTNode *NewNode(ElemType x, BTNode *ln, BTNode *rn); // 创建一个新结点，该结点的值为x，ln和rn为该结点的左右孩子的结点
int IsEmpty(); // 若二叉树bt为空，则返回TRUE，否则返回FALSE
void MakeTree(BinaryTree *bt, ElemType e, BinaryTree *left, BinaryTree *right); // 构造一棵二叉树bt，根结点值为x，以left和right为该根结点的左右子树
// 优先权队列操作
void AdjustUp(BinaryTree heap[], int current);
void AdjustDown(BinaryTree heap[], int current, int border);
void CreatePQ(PriorityQueue *PQ, int mSize);
BOOL IsEmpty(PriorityQueue *PQ);
BOOL IsFull(PriorityQueue *PQ);
int Size(PriorityQueue *PQ);
void Append(PriorityQueue *PQ, BinaryTree x);
void Serve(PriorityQueue *PQ, BinaryTree *x);
// 中序遍历二叉树
void InOrder(BTNode *x);
void visit(BTNode x);
// 构造哈夫曼树
BinaryTree CreateHFMTree(int w[], int m); // w[]为输入权值集合的数组，m表示输入的权值的数量


int main()
{
    BinaryTree ret_tree; // 返回的二叉树
    int w[] = {9, 11, 13, 3, 5, 12}; // 权值集合数组
    ret_tree = CreateHFMTree(w, 6); // 创建哈夫曼树并返回给变量ret_tree
    InOrder(ret_tree.root); // 中序遍历二叉树
    return 0;
}

void Create(BinaryTree *bt)
{
    bt->root = NULL;
}
BTNode *NewNode(ElemType x, BTNode *ln, BTNode *rn)
{
    BTNode *p = (BTNode *)malloc(sizeof(BTNode));
    p->element = x; // 设置根结点权值
    p->lChild = ln;
    p->rChild = rn;
    return p;
}
void MakeTree(BinaryTree *bt, ElemType e, BinaryTree *left, BinaryTree *right)
{
    // if (bt->root || left == right) { // bt->root
    //     return ;
    // }
    bt->root = NewNode(e, left->root, right->root);
    left->root = right->root = NULL;
}
void AdjustUp(BinaryTree heap[], int current)
{
    int p = current;
    BinaryTree temp;
    while (p > 0) {
        if (heap[p].root->element < heap[(p-1)/2].root->element) { // 若p指向元素小于其双亲结点，则与双亲结点交换
            temp = heap[p];
            heap[p] = heap[(p-1)/2];
            heap[(p-1)/2] = temp;
            p = (p-1) / 2; // 将p向上移动至当前考察元素的双亲结点位置
        } else { // 若p指向的元素不小于其双亲结点，则调整完毕
            break;
        }
    }
}
void AdjustDown(BinaryTree heap[], int current, int border)
{
    int p = current;
    int minChild;
    BinaryTree temp;
    while (2*p+1 <= border) { // 若p不是叶子结点则调整
        if ((2*p+2 <= border) && (heap[2*p+1].root->element > heap[2*p+2].root->element)) {
            minChild = 2*p+2; // 右孩子存在，且较大，则minChild指向p的右孩子
        } else {
            minChild = 2*p+1; // 右孩子不存在，或较大，则minChild指向p的左孩子
        }
        if (heap[p].root->element <= heap[minChild].root->element) {
            break; // 若当前节点不大于其最小的孩子，则调整结束
        } else { // 否则将p和其最小的孩子交换
            temp = heap[p];
            heap[p] = heap[minChild];
            heap[minChild] = temp;
            p = minChild; // 设置下轮循环待考察的元素的位置（即当前下移元素的位置）
        }
    }
}
void CreatePQ(PriorityQueue *PQ, int mSize) // 创建一个空的优先权队列
{
    PQ->maxSize = mSize;
    PQ->n = 0;
    PQ->elements_PQ = (BinaryTree *)malloc(mSize*sizeof(BinaryTree));
}
BOOL IsEmpty(PriorityQueue *PQ) // 判断优先权队列是否为空
{
    if (PQ->n == 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}
BOOL IsFull(PriorityQueue *PQ) // 判断优先权队列是否已满
{
    if (PQ->n == PQ->maxSize) {
        return TRUE;
    } else {
        return FALSE;
    }
}
int Size(PriorityQueue *PQ) // 获取当前优先权队列中元素的数量
{
    return PQ->n;
}
void Append(PriorityQueue *PQ, BinaryTree x) // 在优先权队列中增加一个新元素x
{
    if (IsFull(PQ)) {
        return;
    }
    PQ->elements_PQ[PQ->n] = x;
    PQ->n++;
    AdjustUp(PQ->elements_PQ, PQ->n-1);
}
void Serve(PriorityQueue *PQ, BinaryTree *x) // 取出优先级最高的元素，利用参数x返回，并在优先权队列中删除该元素
{
    if (IsEmpty(PQ)) {
        return;
    }
    *x = PQ->elements_PQ[0];
    PQ->n--;
    PQ->elements_PQ[0] = PQ->elements_PQ[PQ->n];
    AdjustDown(PQ->elements_PQ, 0, PQ->n-1);
}
BinaryTree CreateHFMTree(int w[], int m)
{
    PriorityQueue PQ; // 定义优先权队列PQ，用于存放[二叉树根结点]指针
    BinaryTree a, b, x, y, z; // x y z为二叉树变量 // a b为空结点
    Create(&a); Create(&b);
    CreatePQ(&PQ, m); // 初始化优先权队列PQ，设优先权值存在根结点数据域
    for (int i=0; i<m; i++) {
        MakeTree(&x, w[i], &a, &b); // 创建仅包含根结点的二叉树，w[i]为根的权值
        Append(&PQ, x); // 将新创建的二叉树插入优先权队列
    }
    while (PQ.n > 1) {
        Serve(&PQ, &x); // 从PQ取出根结点权值最小的二叉树，存入x
        Serve(&PQ, &y); // 从PQ取出根结点权值次小的二叉树，存入y
        // 合并x和y，作为新二叉树z的左右子树，z的优先权值等于x和y的优先权值之和
        if (x.root->element < y.root->element) { // 若左子树根结点权值小于右子树
            MakeTree(&z, x.root->element+y.root->element, &x, &y);
        } else {
            MakeTree(&z, x.root->element+y.root->element, &y, &x);
        }
        Append(&PQ, z); // 将合并生成的新二叉树z插入优先权队列
    }
    Serve(&PQ, &x); // 获取优先权队列中的唯一二叉树存入x，该二叉树即为哈夫曼树
    return x;
}
void InOrder(BTNode *x)
{
    if (!x) {
        return ;
    }
    InOrder(x->lChild);
    visit(*x);
    InOrder(x->rChild);
}
void visit(BTNode x)
{
    printf("%d ", x.element);
}
