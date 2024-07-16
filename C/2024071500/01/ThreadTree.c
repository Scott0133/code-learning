//二叉树的线索化
#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE -1

typedef struct ThreadNode {
    int data;
    struct ThreadNode *Lchild;
    struct ThreadNode *Rchild;
    int ltag;                       //左右线索标志，ltag == 1，表示Lchild指针是线索，指向前驱；ltag == 0表示指向左孩子
    int rtag;
}ThreadNode, *ThreadTree;

ThreadNode *p;                      //将线索化需要的指针变量作为全局参数
ThreadNode *pre = NULL;
ThreadNode *final = NULL;

//------------------------------------------------         //手动插入线索树
ThreadNode *GetNewNode(int data);                          //创建一个新结构体并返回
ThreadNode *Insert_Inner(ThreadNode* T, int data);         //Insert()嵌套函数，使用递归
void Insert(ThreadTree *T_Ptr, int data);                 //使用指针形式返回结构体
//------------------------------------------------
int InitTree(ThreadTree *T);                               //初始化二叉线索树
void CreateInThread(ThreadTree T);                         //中序线索化二叉树主流程
void InThread(ThreadTree T);                               //中序遍历二叉树，一边遍历一边线索化
void Visit(ThreadNode *q);

int main()
{                                   //测试
    ThreadTree T;
    InitTree(&T);
    Insert(&T, 50);                 //手动创建线索二叉树
    Insert(&T, 30);
    Insert(&T, 45);
    Insert(&T, 70);
    Insert(&T, 21);
    Insert(&T, 23);
    Insert(&T, 7);
    Insert(&T, 33);
    CreateInThread(T);              //中序线索化二叉树主流程
}

//---------------------------------------------------------------手动插入线索二叉树数据
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

void Insert(ThreadTree *T_Ptr, int data)
{
    if (*T_Ptr == NULL)
    {
        *T_Ptr = GetNewNode(data);
    }
    else if (data <= (*T_Ptr)->data)
    {
        (*T_Ptr)->Lchild = Insert_Inner((*T_Ptr)->Lchild, data);        //使用函数Insert_Inner递归
    }
    else
        (*T_Ptr)->Rchild = Insert_Inner((*T_Ptr)->Rchild, data);
}
//---------------------------------------------------------------

int InitTree(ThreadTree *T)
{
    *T = NULL;
}

void CreateInThread(ThreadTree T)
{
    pre = NULL;
    if (T != NULL)
    {
        InThread(T);
        if (pre->Lchild == NULL)
        {
            pre->rtag = 1;          //处理遍历的最后一个结点
        }
    }
}

void InThread(ThreadTree T)
{
    if (T != NULL)
    {
        InThread(T->Lchild);
        Visit(T);
        InThread(T->Rchild);
    }
}

void Visit(ThreadNode *q)
{
    if (q->Lchild == NULL)
    {
        q->Lchild = pre;
        q->ltag = 1;
    }
    if (pre != NULL && pre->Rchild != NULL)
    {
        pre->Rchild = q;
        pre->rtag = 1;
    }
    pre = q;
}