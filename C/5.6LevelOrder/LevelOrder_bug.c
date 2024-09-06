// 二叉树的先、中、后序遍历
// 二叉树的抽象数据类型定义
// 队列BUG（待使用顺序队列）
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
typedef char ElemType;

// -------------------------------------------------
typedef struct btnode { // 定义二叉树结点结构体
    ElemType element;
    struct btnode *lChild;
    struct btnode *rChild;
} BTNode;
typedef struct binarytree { // 定义二叉树结构体
    BTNode *root;
} BinaryTree; // 二叉树结构体
// ------------------------------------------------- 循环队列结构体定义
typedef struct queue {
    int front;
    int rear;
    int maxSize; // 队列实际容量为maxSize-1
    ElemType *element;
} Queue;
//------------------------------------------------//层序遍历二叉树↓
void Create(BinaryTree *bt); // 创建二叉树bt
BTNode *NewNode(ElemType x, BTNode *ln, BTNode *rn); // 创建一个新结点，该结点的值为x，ln和rn为该结点的左右孩子的结点
int IsEmpty(); // 若二叉树bt为空，则返回TRUE，否则返回FALSE
int Root(BinaryTree *bt, ElemType *x); // 若二叉树bt非空，则用x返回其根结点的值，并返回TRUE，否则返回FALSE
void MakeTree(BinaryTree *bt, ElemType e, BinaryTree *left, BinaryTree *right); // 构造一棵二叉树bt，根结点值为e，以left和right为该根结点的左右子树
void LevelOrderTree(BinaryTree *tree); // 层序遍历二叉树
//------------------------------------------------//循环队列的操作↓
void CreateQueue(Queue *Q, int mSize); // 创建一个能容纳mSize个单元的空队列
void Destroy(Queue *Q); // 销毁一个已存在的队列，即释放队列占用的数组空间
int IsEmpty(Queue *Q); // 判断队列是否为空，若是则返回TRUE，否则返回FALSE
int IsFull(Queue *Q); // 判断队列是否已满，若是则返回TRUE，否则返回FALSE
int Front(Queue *Q, BTNode **p); // 获取队头元素，返回element
int EnQueue(Queue *Q, BTNode *p); // 在队列Q的队尾插入元素x（入队）。操作成功返回TRUE，否则返回FALSE
int DeQueue(Queue *Q); // 从队列Q中删除队头元素（出队）。操作成功返回TRUE，否则返回FALSE
void Clear(Queue *Q); // 清除队列中全部元素，使队列恢复初始状态（Q->FRONT = Q->REAR = 0），但不释放空间
void Print(Queue Q); // 打印队列元素

int main()
{
    // 定义五个二叉树变量，并使用初始化函数将他们初始化为空二叉树，然后调用maketree函数逐步构建二叉树
    BinaryTree a; // 创建二叉树结构体a
    BinaryTree b;
    BinaryTree c;
    BinaryTree d;
    BinaryTree e;
    BinaryTree f;
    BinaryTree x; BinaryTree y; // x，y为临时结点，置空
    Create(&a); // a,b,c,d,e,f均为空结点
    Create(&b);
    Create(&c);
    Create(&d);
    Create(&e);
    Create(&f);
    Create(&x); Create(&y); // 临时结点x，y
    MakeTree(&d, 'D', &x, &y); // 叶子结点D，置空
    MakeTree(&e, 'E', &x, &y); // 叶子节点E，置空
    MakeTree(&f, 'F', &x, &y); // 叶子结点F，置空
    MakeTree(&c, 'C', &e, &f); // C为E,F的根节点
    MakeTree(&b, 'B', &d, &y); // 结点B左子树为D，右子树为空
    MakeTree(&a, 'A', &b, &c); // 根节点A左子树为B，右子树为C
    LevelOrderTree(&a); // 层序遍历二叉树

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
}
// 循环队列的操作
void CreateQueue(Queue *Q, int mSize)
{
    Q->maxSize = mSize;
    Q->element = (ElemType *)malloc(mSize*sizeof(ElemType));
    Q->front = Q->rear = 0;
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
int Front(Queue *Q, BTNode **p)
{
    if (IsEmpty(Q)) {
        return FALSE;
    }
    (*p)->element = Q->element[(Q->front + 1) % Q->maxSize];
    return TRUE;
}

int EnQueue(Queue *Q, BTNode *p)
{
    if (IsFull(Q)) {
        return FALSE;
    }
    Q->rear = (Q->rear+1) % Q->maxSize; // 入队front指针移动
    Q->element[Q->rear] = p->element;
    return TRUE;
}
int DeQueue(Queue *Q)
{
    if (IsEmpty(Q)) {
        return FALSE;
    }
    Q->front = (Q->front+1) % Q->maxSize; // 出队rear指针移动
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
void LevelOrderTree(BinaryTree *tree)
{
    if (!tree->root) {
        return ;
    }
    Queue Q; // Q是用于存储BTNode结点类型的队列
    CreateQueue(&Q, QUEUESIZE); // 创建包含QUEUESIZE个单元的队列存储空间
    BTNode *p = tree->root;
    EnQueue(&Q, p); // 将根结点进队
    while (!IsEmpty(&Q)) { // 当根结点不为空
        Front(&Q, &p); // bug
        DeQueue(&Q);
        printf("%c ", p->element); // 访问结点p
        if (p->lChild) {
            EnQueue(&Q, p->lChild);
        }
        if (p->rChild) {
            EnQueue(&Q, p->rChild);
        }
    }
    Destroy(&Q);
}
// void LevelOrderTree_debug(BinaryTree *tree)
// {
//     if (!tree->root) {
//         return ;
//     }
//     Queue Q; // Q是用于存储BTNode结点类型的队列
//     CreateQueue(&Q, QUEUESIZE); // 创建包含QUEUESIZE个单元的队列存储空间
//     BTNode *p = tree->root;
//     EnQueue(&Q, p); // 将根结点进队
//     while (!IsEmpty(&Q)) { // 当根结点不为空
//         Front(&Q, p);
//         DeQueue(&Q);
//         printf("%c ", p->element); // 访问结点p
//         if (p->lChild) {
//             EnQueue(&Q, p->lChild);
//         }
//         if (p->rChild) {
//             EnQueue(&Q, p->rChild);
//         }
//         // 调试信息
//         printf("当前节点: %c\n", p->element);
//     }
//     Destroy(&Q);
// }
