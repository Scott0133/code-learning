//二叉树的线索化
//bug
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

int InitTree(ThreadTree *T);                    //初始化二叉线索树
ThreadTree *GetNewNode(int data);
ThreadTree *Insert(ThreadTree *T, int data);  //插入新结点
void CreateInThread(ThreadTree T);  //中序线索化二叉树主流程
void InThread(ThreadTree T);        //中序遍历二叉树，一边遍历一边线索化
void Visit(ThreadNode *q);


int main()
{                                   //测试
    ThreadTree T = NULL;
//   InitTree(&T);
    Insert(&T, 50);                 //手动创建线索二叉树
    Insert(&T, 30);
    Insert(&T, 45);
    Insert(&T, 21);
    Insert(&T, 23);
    Insert(&T, 7);
    Insert(&T, 33);
//    CreateInThread(T);
}


int InitTree(ThreadTree *T)
{
    (*T) = (ThreadNode*)malloc(sizeof(ThreadNode));
    (*T)->data = 0;
    (*T)->Lchild = NULL;
    (*T)->Rchild = NULL;
    (*T)->ltag = 0;
    (*T)->rtag = 0;
    return TRUE;
}

ThreadTree *GetNewNode(int data)
{
    ThreadNode *newNode = (ThreadNode*)malloc(sizeof(ThreadNode));
    newNode->data = data;
    newNode->Lchild = NULL;
    newNode->Rchild = NULL;
    return newNode;
}

ThreadTree* Insert(ThreadTree *T, int data)
{
    if((*T) == NULL)
    {
        (*T) = GetNewNode(data);
    }
    else if (data <= (*T)->data)
    {
        (*T)->Lchild = Insert((*T)->Lchild, data);      //使用递归传递参数
    }
    else
        (*T)->Rchild = Insert((*T)->Rchild, data);
    return (*T);
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