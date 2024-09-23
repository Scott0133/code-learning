#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define OverFlow 2 // 上溢
#define UnderFlow 3 // 下溢
#define NotPresent 4 // 元素不存在
#define Duplicate 5 // 元素重复
typedef int BOOL;

typedef struct btnode { // 二叉树结点结构体
    int element; // 权值存储于element
    struct btnode *lChild;
    struct btnode *rChild;
}BTNode;
typedef struct binarytree { // 二叉树结构体
    BTNode *root;
}Binarytree;
typedef struct priorityQueue { // 优先权队列结构体
    Binarytree *elements; // 存储元素的数组
    int n; // 优先权队列中元素的数量
    int maxSize; // 优先权队列的容量
}PriorityQueue;

void AdjustUp(Binarytree heap[], int current);
void AdjustDown(Binarytree heap[], int current, int border);
void CreatePQ(PriorityQueue *PQ, int mSize); // 创建一个空的优先权队列
void Destroy(PriorityQueue *PQ); // 销毁一个优先权队列，释放其占用的内存空间
BOOL IsEmpty(PriorityQueue *PQ); // 判断优先权队列是否为空
BOOL IsFull(PriorityQueue *PQ); // 判断优先权队列是否已满
int Size(PriorityQueue *PQ); // 获取当前优先权队列中元素的数量
void Append(PriorityQueue *PQ, Binarytree x); // 在优先权队列中增加一个新元素x
void Serve(PriorityQueue *PQ, Binarytree *x); // 取出优先级最高的元素，利用参数x返回，并在优先权队列中删除该元素
void PrintArr(PriorityQueue *PQ);
void MakeTree(Binarytree *bt, int e, Binarytree *left, Binarytree *right);
BTNode* NewNode(int x, BTNode *ln, BTNode *rn);
Binarytree CreateHFMTree(int w[], int m); // 构造哈夫曼树

void Print(PriorityQueue PQ);

int main()
{
    // int x; // 临时返回值
    // int mSize = 100;
    // PriorityQueue PQ; // 创建一个优先权队列结构体

    // CreatePQ(&PQ, mSize); 
    // Append(&PQ, 71); // 插入元素形成小根堆
    // Append(&PQ, 74);
    // Append(&PQ, 2);
    // Append(&PQ, 72);
    // Append(&PQ, 54);
    // Append(&PQ, 93);
    // Append(&PQ, 52);
    // Append(&PQ, 28);
    // PrintArr(&PQ);

    // Serve(&PQ, &x); // 取出优先级最高的元素，利用参数x返回
    // Serve(&PQ, &x);
    // printf("\n");
    // PrintArr(&PQ);
    // PriorityQueue PQ;
    int w[] = {9, 11, 13, 3, 5, 12};
    int m = 6;
    CreateHFMTree(w, m);

    return 0;
}


void AdjustUp(Binarytree heap[], int current)
{
    int p = current;
    Binarytree temp;
    temp.root = (BTNode *)malloc(sizeof(BTNode));
    while (p > 0) {
        if (heap[p].root->element < heap[(p-1) / 2].root->element) { // 若p指向元素小于其双亲结点，则与双亲结点交换
            temp.root->element = heap[p].root->element;
            heap[p].root->element = heap[(p-1) / 2].root->element;
            heap[(p-1) / 2].root->element = temp.root->element;
            p = (p-1) / 2; // 将p向上移动至当前考察元素的双亲结点位置
        } else { // 若p指向的元素不小于其双亲结点，则调整完毕
            break;
        }
    }
}
void AdjustDown(Binarytree heap[], int current, int border)
{
    int p = current;
    int minChild;
    Binarytree temp;
    temp.root = (BTNode *)malloc(sizeof(BTNode));
    while (2*p+1 <= border) { // 若p不是叶子结点则调整
        if ((2*p+2 <= border) && (heap[2*p+1].root->element > heap[2*p+2].root->element)) {
            minChild = 2*p+2; // 右孩子存在，且较大，则minChild指向p的右孩子
        } else {
            minChild = 2*p+1; // 右孩子不存在，或较大，则minChild指向p的左孩子
        }
        if (heap[p].root->element <= heap[minChild].root->element) {
            break; // 若当前节点不大于其最小的孩子，则调整结束
        } else { // 否则将p和其最小的孩子交换
            temp.root->element = heap[p].root->element;
            heap[p].root->element = heap[minChild].root->element;
            heap[minChild].root->element = temp.root->element;
            p = minChild; // 设置下轮循环待考察的元素的位置（即当前下移元素的位置）
        }
    }
}
void CreatePQ(PriorityQueue *PQ, int mSize) // 创建一个空的优先权队列
{
    PQ->maxSize = mSize;
    PQ->n = 0;
    PQ->elements = (Binarytree *)malloc(mSize*sizeof(Binarytree));
}
void Destroy(PriorityQueue *PQ) // 销毁一个优先权队列，释放其占用的内存空间
{
    free(PQ->elements);
    PQ->n = 0;
    PQ->maxSize = 0;
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
void Append(PriorityQueue *PQ, Binarytree x) // 在优先权队列中增加一个新结点x
{
    if (IsFull(PQ)) {
        return;
    }
    PQ->elements[PQ->n] = x;
    PQ->n++;
    AdjustUp(PQ->elements, PQ->n-1);
}
void Serve(PriorityQueue *PQ, Binarytree *x) // 取出优先级最高的元素，利用参数x返回，并在优先权队列中删除该元素
{
    if (IsEmpty(PQ)) {
        return;
    }
    *x = PQ->elements[0];
    PQ->n--;
    PQ->elements[0] = PQ->elements[PQ->n];
    AdjustDown(PQ->elements, 0, PQ->n-1);
}
void PrintArr(PriorityQueue *PQ)
{
    for (int i=0; i<PQ->n; i++) {
        printf("%d ", PQ->elements[i]);
    }
}
BTNode* NewNode(int x, BTNode *ln, BTNode *rn)
{
    BTNode *p = (BTNode*)malloc(sizeof(BTNode));
    p->element = x;
    p->lChild = ln;
    p->rChild = rn;
    return p;
}
void MakeTree(Binarytree *bt, int e, Binarytree *left, Binarytree *right)
{
    // bt->root = NULL;
    // if (bt->root || left == right) {
    //     return ;
    // }
    // bt->root = NewNode(e, left->root, right->root);
    BTNode *p = (BTNode*)malloc(sizeof(BTNode));
    p->element = e;
    p->lChild = NULL;
    p->rChild = NULL;
    bt->root = p;
    // left->root = right->root = NULL;
}
void MakeTree_v2(Binarytree *bt, int e, Binarytree *left, Binarytree *right)
{
    // if (bt->root || left == right) {
    //     return ;
    // }
    bt->root = NewNode(e, left->root, right->root);
    left->root = right->root = NULL;
}
void Create(Binarytree *bt)
{
    bt->root = NULL;
}
Binarytree CreateHFMTree(int w[], int m) // w为输入权值集合的数组，m表示输入的权值的数量
{
    PriorityQueue PQ; // 定义优先权队列PQ，用于存放二叉树根结点指针
    Binarytree x, y, z, a, b; // x,y,z为二叉树变量,a,b为临时变量
    CreatePQ(&PQ, m); // 初始化优先权队列PQ，设优先权值存在根结点数据域
    Create(&a);
    Create(&b);
    for (int i=0; i<m; i++) {
        MakeTree_v2(&x, w[i], &a, &b); // 创建仅包含根结点的二叉树
        Append(&PQ, x); // 将创建的二叉树插入优先权队列
    }
    Print(PQ);
    while (PQ.n > 1) {
        Serve(&PQ, &x); // 从PQ中取出根结点权值最小的二叉树，存入x
        Serve(&PQ, &y); // 从PQ中取出根结点权值次小的二叉树，存入y
        // 合并x和y，作为新二叉树z的左右子树，z的优先权值等于x和y的优先权值之和
        if (x.root->element < y.root->element) { // 设置左子树根结点权值小于右子树
            MakeTree_v2(&z, x.root->element + y.root->element, &x, &y);
        } else {
            MakeTree_v2(&z, x.root->element + y.root->element, &y, &x);
        }
        Append(&PQ, z); // 将合并生成的新二叉树z插入优先权队列
    }
    Serve(&PQ, &x); // 获取优先权队列中唯一的二叉树，存入x，该二叉树为哈夫曼树
    return x;
}
void Print(PriorityQueue PQ)
{
    for (int i=0; i<6; i++) {
        printf("%d ", PQ.elements[i].root->element);
    }
}