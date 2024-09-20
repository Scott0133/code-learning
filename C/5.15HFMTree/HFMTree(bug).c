#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define OverFlow 2 // 上溢
#define UnderFlow 3 // 下溢
#define NotPresent 4 // 元素不存在
#define Duplicate 5 // 元素重复
typedef int ElemType;

typedef struct btnode { // 定义二叉树结点结构体
    ElemType element;
    struct btnode *lChild;
    struct btnode *rChild;
} BTNode;
typedef struct binarytree { // 定义二叉树结构体
    BTNode *root;
} BinaryTree;
typedef struct priorityQueue { // 优先权队列结构体
    BTNode **element; // 存储元素的数组
    int n; // 优先权队列中元素的数量
    int maxSize; // 优先权队列的容量
}PriorityQueue;

BinaryTree CreateHFMTree(int w[], int m); // w[]为输入权值集合的数组，m标识输入权值的数量
void CreatePQ(PriorityQueue *PQ, int mSize);
void Append(PriorityQueue *PQ, BinaryTree *x);
void Serve(PriorityQueue *PQ, BinaryTree *x);
void MakeTree(BinaryTree *bt, ElemType e, BinaryTree *left, BinaryTree *right);
BTNode *NewNode(ElemType x, BTNode *ln, BTNode *rn); // 创建一个新结点，该结点的值为x，ln和rn为该结点的左右孩子的结点
void AdjustUp(BTNode *heap[], int current);
void AdjustDown(BTNode *heap[], int current, int border);

int main()
{
    int w[] = {9, 11, 13, 3, 5, 12};
    int m = 6;

    CreateHFMTree(w, m);
    return 0;
}

void CreatePQ(PriorityQueue *PQ, int mSize) // 创建一个空的优先权队列
{
    PQ->maxSize = mSize;
    PQ->n = 0;
    PQ->element = (BTNode **)malloc(mSize*sizeof(BTNode*));
}
BTNode *NewNode(ElemType x, BTNode *ln, BTNode *rn)
{
    BTNode *p = (BTNode *)malloc(sizeof(BTNode));
    p->element = x;
    p->lChild = ln;
    p->rChild = rn;
    return p;
}
void MakeTree(BinaryTree *bt, ElemType e, BinaryTree *left, BinaryTree *right)
{
    if (bt->root || left == right) {
        return ;
    }
    bt->root = NewNode(e, left->root, right->root);
    left->root = right->root = NULL;
}
void AdjustUp(BTNode *heap[], int current)
{
    int p = current;
    BTNode *temp;
    while (p > 0) {
        if (heap[p]->element < heap[(p-1) / 2]->element) { // 若p指向元素小于其双亲结点，则与双亲结点交换
            temp = heap[p];
            heap[p] = heap[(p-1) / 2];
            heap[(p-1) / 2] = temp;
            p = (p-1) / 2; // 将p向上移动至当前考察元素的双亲结点位置
        } else { // 若p指向的元素不小于其双亲结点，则调整完毕
            break;
        }
    }
}
void AdjustDown(BTNode *heap[], int current, int border)
{
    int p = current;
    int minChild;
    BTNode *temp;
    while (2*p+1 <= border) { // 若p不是叶子结点则调整
        if ((2*p+2 <= border) && (heap[2*p+1]->element > heap[2*p+2]->element)) {
            minChild = 2*p+2; // 右孩子存在，且较大，则minChild指向p的右孩子
        } else {
            minChild = 2*p+1; // 右孩子不存在，或较大，则minChild指向p的左孩子
        }
        if (heap[p]->element <= heap[minChild]->element) {
            break; // 若当前节点不大于其最小的孩子，则调整结束
        } else { // 否则将p和其最小的孩子交换
            temp = heap[p];
            heap[p] = heap[minChild];
            heap[minChild] = temp;
            p = minChild; // 设置下轮循环待考察的元素的位置（即当前下移元素的位置）
        }
    }
}
void Append(PriorityQueue *PQ, BinaryTree *x) // 在优先权队列中增加一个新元素x
{
    // if (IsFull(PQ)) return;
    PQ->element[PQ->n] = x->root;
    PQ->n++;
    AdjustUp(PQ->element, PQ->n-1);
}
void Serve(PriorityQueue *PQ, BinaryTree *x) // 取出优先级最高的元素，利用参数x返回，并在优先权队列中删除该元素
{
    // if (IsEmpty(PQ)) {
    //     return;
    // }
    x->root = PQ->element[0];
    PQ->n--;
    PQ->element[0] = PQ->element[PQ->n];
    AdjustDown(PQ->element, 0, PQ->n-1);
}
BinaryTree CreateHFMTree(int w[], int m)
{
    PriorityQueue PQ; // 定义优先权队列PQ，用于存放二叉树根结点指针
    BinaryTree x, y, z; // x,y,z为二叉树变量
    CreatePQ(&PQ, m); // 初始化优先权队列PQ，设优先权值存在根结点数据域
    for (int i=0; i<m; i++) {
        MakeTree(&x, w[i], NULL, NULL); // 创建仅包含根结点的二叉树，w[i]为根的权值
        Append(&PQ, &x); // 将新创建的二叉树插入优先权队列
    }
    while (PQ.n > 1) {
        Serve(&PQ, &x); // 从PQ中取出根结点权值最小的二叉树，存入x
        Serve(&PQ, &y); // 从PQ中取出根结点权值次小的二叉树，存入y
        // 合并x和y，作为新二叉树z的左右子树，z的优先权值等于x和y的优先权值之和
        if (x.root->element < y.root->element) { // 设置左右子树根结点权值小于右子树
            MakeTree(&z, x.root->element+y.root->element, &x, &y);
        } else {
            MakeTree(&z, x.root->element+y.root->element, &y, &x);
        }
        Append(&PQ, &z); // 将合并生成的新二叉树z插入优先权队列
    }
    Serve(&PQ, &x); // 获取优先权队列中唯一的二叉树，存入x，该二叉树即为哈夫曼树
    return x;
}