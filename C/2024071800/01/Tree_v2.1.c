//二叉树的线索化
//使用层序遍历遍历二叉树
//v2_1
//中序线索二叉树找中序后继
//中序线索二叉树找中序前驱
//对中序线索二叉树进行中序遍历（利用线索实现的非递归算法）
//对中序线索二叉树进行逆向中序遍历（利用线索实现的非递归算法）
#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE -1
//////////////////////////////////////////////////二叉树的结构定义↓
typedef struct ThreadNode {
    int data;
    struct ThreadNode *Lchild;
    struct ThreadNode *Rchild;
    int ltag;                       //左右线索标志，ltag == 1表示Lchild指针是线索，指向前驱；ltag == 0表示有左孩子
    int rtag;                       //             rtag == 1表示Rchild指针是线索，指向后继；rtag == 0表示有右孩子
}ThreadNode, *ThreadTree;

ThreadNode *p;                      //将线索化需要的指针变量作为全局参数
ThreadNode *pre = NULL;
ThreadNode *final = NULL;
//////////////////////////////////////////////////链式队列的结构定义↓

typedef struct LinkNode {           //链式队列结点
    ThreadNode *data;               //链式队列存树结点的指针
    struct LinkNode *next;
}LinkNode;

typedef struct {                    //链式队列
    LinkNode *front, *rear;         //队列的头指针尾指针
}LinkQueue;
//////////////////////////////////////////////////


//------------------------------------------------//手动插入线索树操作↓
ThreadNode *GetNewNode(int data);                          //创建一个新结构体并返回
ThreadNode *Insert_Inner(ThreadNode* T, int data);         //Insert()嵌套函数，使用递归
void        Insert(ThreadTree *T, int data);               //使用指针形式返回结构体
//------------------------------------------------//链式队列的操作↓
void LevelOrder(ThreadTree T);                             //层序遍历主流程
void InitQueue(LinkQueue *Q);                              //初始化队列
int  IsEmpty(LinkQueue Q);                                 //判断队列是否为空
void EnterQueue(LinkQueue *Q, ThreadTree P_Ptr);           //插入队列，将树结点的指针放入队列
int  DeleteQueue(LinkQueue *Q, ThreadTree *P_Ptr);         //移除队列
//------------------------------------------------//中序线索化二叉树操作↓
int  InitTree(ThreadTree *T);                              //初始化二叉线索树
void CreateInThread(ThreadTree T);                         //中序线索化二叉树主流程
void InThread(ThreadTree T);                               //中序遍历二叉树，一边遍历一边线索化
void Visit(ThreadNode *p);
void InOrder(ThreadTree T); //中序遍历测试
void Visit_Prt(ThreadTree T);
//------------------------------------------------//中序线索化二叉树中找中序后继↓
ThreadNode *FirstNode(ThreadNode *p);           //找到中序线索化二叉树的第一个访问结点
ThreadNode *NextNode(ThreadNode *p);            //找到第一个访问节点的下一个结点，即p的后继
void InOrder_seq(ThreadNode *node);             //非递归算法实现的中序遍历
ThreadNode *LastNode(ThreadNode *p);
ThreadNode *PreNode(ThreadNode *p);
void InOrder_reverse_seq(ThreadNode *node);

int main()
{                                   //测试
    ThreadTree T;                   //创建一个二叉树T
    ThreadNode *node;               //创建一个结点指针node
    InitTree(&T);                   //初始化二叉树
    Insert(&T, 50);                 //手动创建线索二叉树
    Insert(&T, 30);
    Insert(&T, 45);
    Insert(&T, 52);
    Insert(&T, 21);
    Insert(&T, 23);
    Insert(&T, 7);
    Insert(&T, 33);
    //InOrder(T);                   //中序遍历测试
    CreateInThread(T);              //中序线索化二叉树主流程
    node = T;                       //node指向根节点
    //InOrder_seq(node);              //非递归算法的中序遍历（利用线索实现的非递归算法）
    InOrder_reverse_seq(node);
    printf("done\n");
    //LevelOrder(T);                //层序遍历
}

//---------------------------------------------------------------手动插入线索二叉树数据↓
ThreadNode *GetNewNode(int data)
{
    ThreadNode *newNode = (ThreadNode*)malloc(sizeof(ThreadNode));
    newNode->data = data;
    newNode->Lchild = NULL;
    newNode->Rchild = NULL;
    newNode->ltag = 0;
    newNode->rtag = 0;
    return newNode;
}
ThreadNode *Insert_Inner(ThreadNode* T, int data)
{	
    if(T == NULL) 
    {
		T = GetNewNode(data);
	}
    else if (data <= T->data)
    {
        T->Lchild = Insert_Inner(T->Lchild, data);                      //使用递归传递参数
    }
    else
        T->Rchild = Insert_Inner(T->Rchild, data);
    return T;
}
void Insert(ThreadTree *T, int data)
{
    if (*T == NULL)
    {
        *T = GetNewNode(data);
    }
    else if (data <= (*T)->data)
    {
        (*T)->Lchild = Insert_Inner((*T)->Lchild, data);        //使用函数Insert_Inner递归
    }
    else
        (*T)->Rchild = Insert_Inner((*T)->Rchild, data);
}
//---------------------------------------------------------------中序线索化二叉树操作↓
int InitTree(ThreadTree *T)
{
    *T = NULL;
}
void CreateInThread(ThreadTree T)   //中序线索化二叉树主流程
{
    pre = NULL;
    if (T != NULL)
    {
        InThread(T);
        if (pre->Rchild == NULL)
        {
            pre->rtag = 1;          //处理遍历的最后一个结点
        }
    }
}
void InThread(ThreadTree T)         //中序遍历二叉树，一边遍历一边线索化
{
    if (T != NULL)
    {
        InThread(T->Lchild);
        Visit(T);
        InThread(T->Rchild);
    }
}
void Visit(ThreadNode *q)           //访问动作，并线索化
{
    if (q->Lchild == NULL)
    {
        q->Lchild = pre;
        q->ltag = 1;
        //Visit_Prt(q);
    }
    if (pre != NULL && pre->Rchild == NULL)
    {
        pre->Rchild = q;
        pre->rtag = 1;
        //Visit_Prt(q);
    }
    pre = q;
}
void Visit_Prt(ThreadTree T)        //访问结点并打印值
{
    printf("%d ", T->data);
}
void InOrder(ThreadTree T)          //中序遍历测试
{
    if (T != NULL)
    {
        InOrder(T->Lchild);
        Visit_Prt(T);
        InOrder(T->Rchild);
    }
}
//------------------------------------------------------------------层序遍历队列操作↓
void InitQueue(LinkQueue *Q)
{
    Q->front = Q->rear = (LinkNode *)malloc(sizeof(LinkNode));
    Q->front->next = NULL;                                      //front指向头结点
}
int IsEmpty(LinkQueue Q)
{
    if (Q.front == Q.rear)
        return TRUE;
    else
        return FALSE;
}
void EnterQueue(LinkQueue *Q, ThreadTree P_Ptr)
{
    LinkNode *s = (LinkNode *)malloc(sizeof(LinkNode));
    s->data = P_Ptr;
    s->next = NULL;
    Q->rear->next = s;
    Q->rear = s;
}
int DeleteQueue(LinkQueue *Q, ThreadTree *P_Ptr)
{
    if (Q->front == Q->rear)
        return FALSE;
    LinkNode *p = Q->front->next;
    *P_Ptr = p->data;
    Q->front->next = p->next;
    if (Q->rear == p)
        Q->rear = Q->front;
    free(p);
    return TRUE;
}
void LevelOrder(ThreadTree T)
{
    LinkQueue Q;
    InitQueue(&Q);                  //初始化辅助队列，带头结点
    //ThreadTree ptr;
    EnterQueue(&Q, T);              //EnterQueue(LinkQueue *, ThreadTree );
    while (IsEmpty(Q) == FALSE)     //当队列非空循环
    {
        DeleteQueue(&Q, &T);
        Visit_Prt(T);
        if (T->Lchild != NULL)
        {
            EnterQueue(&Q, T->Lchild);
        }
        if (T->Rchild != NULL)
        {
            EnterQueue(&Q, T->Rchild);
        }
    }
}
//------------------------------------------------------------------对中序线索二叉树进行中序遍历（利用线索实现的非递归算法）
ThreadNode *FirstNode(ThreadNode *p)           //找到中序线索化二叉树的第一个访问结点并返回
{
    while (p->ltag == 0)                       
    {
        p = p->Lchild;
    }
    return p;
}
ThreadNode *NextNode(ThreadNode *p)            //找到第一个访问节点的下一个结点
{
    if (p->rtag == 0)                          //如果第一个结点有右孩子，找到右孩子的最左下结点并返回
    {
        return FirstNode(p->Rchild);
    }
    else                                       //第一个结点没有右孩子，直接返回下一结点
    {
        return p->Rchild;
    }
}
void InOrder_seq(ThreadNode *node)                   //非递归算法实现的中序遍历
{
    for (ThreadNode *p = FirstNode(node); p != NULL; p = NextNode(p))
    {
        Visit_Prt(p);
    }
}

ThreadNode *LastNode(ThreadNode *p)
{
    while (p->rtag == 0)
    {
        p = p->Rchild;
    }
    return p;
}
ThreadNode *PreNode(ThreadNode *p)
{
    if (p->ltag == 0)
    {
        return LastNode(p->Lchild);
    }
    else
    {
        return p->Lchild;
    }
}
void InOrder_reverse_seq(ThreadNode *node)
{
    for (ThreadNode *p = LastNode(node); p != NULL; p = PreNode(p))
    {
        Visit_Prt(p);
    }
}