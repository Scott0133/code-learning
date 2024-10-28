// 打印二叉树左视图

// 非递归方式求二叉树高度（未考虑错误情况）
// 程序5.6 层次遍历（层序遍历）
    // 辅助数据结构：循环队列
    // 辅助数据结构：二叉树的抽象数据类型定义
// pass
#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define QUEUESIZE 100 // 队列容量100
#define FALSE 0
#define TRUE 1
#define OverFlow 2 // 上溢
#define UnderFlow 3 // 下溢
#define NotPresent 4 // 元素不存在
#define Duplicate 5 // 元素重复
// 循环队列（模运算实现）
typedef char ElemType; // 数据类型指定为char类型
typedef struct btnode { // 定义二叉树结点结构体
    ElemType element;
    struct btnode *lChild;
    struct btnode *rChild;
} BTNode;
typedef struct binarytree { // 定义二叉树结构体
    BTNode *root;
} BinaryTree;
typedef struct queue {
    int front;
    int rear;
    int length;
    int maxSize; // 队列实际容量为maxSize-1
    BTNode *element; // 存储的一维数组为ElemType类型
} Queue;
// 队列运算
void Create_Q(Queue *Q, int mSize); // 创建一个能容纳mSize个单元的空队列
void Destroy(Queue *Q); // 销毁一个已存在的队列，即释放队列占用的数组空间
int IsEmpty(Queue *Q); // 判断队列是否为空，若是则返回TRUE，否则返回FALSE
int IsFull(Queue *Q); // 判断队列是否已满，若是则返回TRUE，否则返回FALSE
int Front(Queue *Q, BTNode *x); // 获取队头元素，通过x返回。
int EnQueue(Queue *Q, BTNode x); // 在队列Q的队尾插入元素x（入队）。操作成功返回TRUE，否则返回FALSE
int DeQueue(Queue *Q); // 从队列Q中删除队头元素（出队）。操作成功返回TRUE，否则返回FALSE
void Clear(Queue *Q); // 清除队列中全部元素，使队列恢复初始状态（Q->FRONT = Q->REAR = 0），但不释放空间
void Print(Queue Q); // 打印队列元素
int Q_length(Queue Q); // 返回Q队列的长度
// 二叉树运算
void Create_BT(BinaryTree *bt); // 创建二叉树bt
BTNode *NewNode(ElemType x, BTNode *ln, BTNode *rn); // 创建一个新结点，该结点的值为x，ln和rn为该结点的左右孩子的结点
int IsEmpty(); // 若二叉树bt为空，则返回TRUE，否则返回FALSE
int Root(BinaryTree *bt, ElemType *x); // 若二叉树bt非空，则用x返回其根结点的值，并返回TRUE，否则返回FALSE
void MakeTree(BinaryTree *bt, ElemType e, BinaryTree *left, BinaryTree *right); // 构造一棵二叉树bt，根结点值为x，以left和right为该根结点的左右子树
void Visit(BinaryTree *bt); // 访问当前结点
// 层次遍历
int LevelOrderTree_height(BinaryTree *tree); // 层次遍历主函数




int main()
{
    // 图5.13 二叉树层次遍历的访问
    BinaryTree a,b,x,y,z; // a，b作为空结点，x y z分别作为中间结点进行链接
    Create_BT(&a);
    Create_BT(&b);
    Create_BT(&x);
    Create_BT(&y);
    Create_BT(&z);
    MakeTree(&y, 'E', &a, &b);
    MakeTree(&z, 'F', &a, &b);
    MakeTree(&x, 'C', &y, &z);
    MakeTree(&y, 'D', &a, &b);
    MakeTree(&z, 'B', &y, &b);
    MakeTree(&y, 'A', &z, &x); 
    int height = LevelOrderTree_height(&y);
    printf("\ntree height is %d\n", height);
    return 0;
}

void Create_Q(Queue *Q, int mSize)
{
    Q->maxSize = mSize;
    Q->element = (BTNode *)malloc(mSize*sizeof(BTNode));
    Q->front = Q->rear = 0;
    Q->length = 0;
}
void Destroy(Queue *Q)
{
    Q->maxSize = 0;
    free(Q->element);
    Q->front = Q->rear = -1;
}
int IsEmpty(Queue *Q)
{
    return Q->front == Q->rear; // front和rear相等为空
}
int IsFull(Queue *Q)
{
    return (Q->rear+1) % Q->maxSize == Q->front; // rear在front的后面，则循环队列已满
}
int Front(Queue *Q, BTNode *x)
{
    if (IsEmpty(Q)) {
        return FALSE;
    }
    *x = Q->element[(Q->front+1) % Q->maxSize];
    return TRUE;
}
int EnQueue(Queue *Q, BTNode x)
{
    if (IsFull(Q)) {
        return FALSE;
    }
    Q->rear = (Q->rear+1) % Q->maxSize; // 入队front指针移动
    Q->element[Q->rear] = x;
    Q->length++;
    return TRUE;
}
int DeQueue(Queue *Q)
{
    if (IsEmpty(Q)) {
        return FALSE;
    }
    Q->front = (Q->front+1) % Q->maxSize; // 出队rear指针移动
    Q->length--;
    return TRUE;
}
void Clear(Queue *Q)
{
    Q->front = Q->rear = 0;
}
void Print(Queue Q)
{
    Q.front++; // front指向元素置空
    while (Q.rear != Q.front) {
        printf("%d ", Q.element[Q.front]); // 从队首到队尾-1依次列出元素
        Q.front = (Q.front+1) % Q.maxSize;
        if (Q.front == Q.rear) {
            printf("\nThe rear element is %d", Q.element[Q.rear]); // 队尾元素
        }
    }
}
void Create_BT(BinaryTree *bt)
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
// void Visit(BinaryTree *bt)
// {
//     printf("%c, ", bt->root->element);
// }
int LevelOrderTree_height(BinaryTree *tree)
{
    if (!tree->root) { // 若根结点不存在
        return FALSE;
    }
    Queue Q; // Q是用于存储BTNode结点类型的队列
    Create_Q(&Q, QUEUESIZE); // 创建队列空间
    BTNode *p = tree->root; // 声明临时结点结构体指针p指向根结点
    int level = 0; // 初始化高度为0
    EnQueue(&Q, *p); // 将根结点进队
    while (!IsEmpty(&Q)) { // 当链表不为空时
        int n = Q.length;
        for (int i=0; i<n; i++) {
            Front(&Q, p);
            DeQueue(&Q);
            // printf("%c ", p->element); // 访问结点p
            if (p->lChild) {
                EnQueue(&Q, *p->lChild);
            }
            if (p->rChild) {
                EnQueue(&Q, *p->rChild);
            }
            if (i == 0) { // 打印二叉树左视图（i==0为每层遍历的第一位元素）
                printf("%c ", p->element);
            }
        }
        level++; // 遍历完每层之后，高度加一
    }
    Destroy(&Q);
    return level;
}
int Q_length(Queue Q)
{
    return Q.length;
}