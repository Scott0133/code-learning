#include<stdio.h>
#include<stdlib.h>
#define OK 1
#define FALSE -1

typedef struct BiNode {
    int data;
    struct BiNode *Lchild;
    struct BiNode *Rchild;
}BiNode, *Bitree;

typedef struct {
    int size;
    int *top;
    int *base;
}Stack;

int CreateBiTree(Bitree *T);                         //按顺序读入数字，建立二叉树
// void InitStack();
// int Push(Stack S, Bitree p);
// int Pop(Stack S, Bitree p);
// int StackEmpty();
// int PreOrderTraverse(Bitree T);
// int InOrderTraverse(Bitree T);
// int PostOrderTraverse(Bitree T);
// int InOrderTraverse_2(Bitree T, Stack S);        //中序遍历非递归算法


int main()
{
    Bitree T;
    CreateBiTree(&T);

    return 0;
}

int CreateBiTree(Bitree *T)
{
    char ch;
    scanf(&ch);
    if (ch == '#')
    {
        T == NULL;
    }
    else
    {
        Bitree *T = (BiNode *)malloc(sizeof(BiNode));
        (*T)->data = ch;
        CreateBiTree((*T)->Lchild);
        CreateBiTree((*T)->Rchild);
    }
}

// int PreOrderTraverse(Bitree T)      //先序遍历
// {
//     if (T == NULL)
//         return OK;
//     else
//     {
//         visit(T);
//         PreOrderTraverse(T->Lchild);
//         PreOrderTraverse(T->Rchild);
//     }
// }

// int InOrderTraverse(Bitree T)       //中序遍历
// {
//     if (T == NULL)
//         return OK;
//     else
//     {
//         InOrderTraverse(T->Lchild);
//         visit(T);
//         InOrderTraverse(T->Rchild);
//     }
// }

// int PostOrderTraverse(Bitree T)     //后序遍历
// {
//     if (T == NULL)
//         return OK;
//     else
//     {
//         PostOrderTraverse(T->Lchild);
//         PostOrderTraverse(T->Rchild);
//         visit(T);
//     }
// }

int InOrderTraverse_2(Bitree T, Stack S)
{
    Bitree p;
    Bitree q;
    InitStack();
    p = T;          //栈指针指向根
    while (p || !StackEmpty())
    {
        if (p)
        {
            Push(S, p);
            p = p->Lchild;
        }
        else
        {
            Pop(S, p);
            printf("%d", q->data);
        }
    }
}