//二叉树创建，手动创建
//使用二分查找法
#include<stdio.h>
#include<stdlib.h>
#define TURE 1
#define FALSE -1

typedef struct BstNode {            //定义二叉搜索树结构
    int data;
    struct BstNode *left;
    struct BstNode *right;
}BstNode;

BstNode* rootPtr;    //定义根指针

BstNode* GetNewNode(int data);                  //创建一个新结构体并返回
BstNode* Insert(BstNode* root, int data);       //形式1：使用return返回结构体的形式将参数传递main()
void Insert_2(BstNode** rootP, int data);       //形式2：使用指针形式返回结构体
int Search(BstNode* root, int data);             //使用递归查找已有值

int main()
{
    BstNode* root = NULL;
    root = Insert(root, 15);        //使用形式二：Insert(&root, 15);    现在root指向根
    root = Insert(root, 20);
    root = Insert(root, 25);
    root = Insert(root, 22);
    root = Insert(root, 17);
    Insert_2(&root, 30);            //使用形式二
    Search(root, 20);
    return 0;
    
}

BstNode *GetNewNode(int data)
{
    BstNode *newNode = (BstNode*)malloc(sizeof(BstNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

BstNode* Insert(BstNode* root, int data)
{
    if(root == NULL)
    {
        root = GetNewNode(data);
    }
    else if (data <= root->data)
    {
        root->left = Insert(root->left, data);      //使用递归传递参数
    }
    else
        root->right = Insert(root->right, data);
    return root;
}

void Insert_2(BstNode** rootP, int data)
{
    if (*rootP == NULL)
    {
        *rootP = GetNewNode(data);
    }
    else if (data <= (*rootP)->data)
    {
        (*rootP)->left = Insert((*rootP)->left, data);
    }
    else
        (*rootP)->right = Insert((*rootP)->right, data);
}

int Search(BstNode* root, int data)                     //递归查找
{
    if (root == NULL)
    {
        return FALSE;
    }
    else if (root->data == data)
    {
        return TURE;
    }
    else if (data <= root->data)
        return Search(root->left, data);
    else
        return Search(root->right, data);
}