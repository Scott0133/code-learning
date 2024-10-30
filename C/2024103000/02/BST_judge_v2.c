// 迭代版本的中序遍历，判断是否为二叉排序树
    // 辅助数据结构：栈
    // 全局变量：前驱结点值pre，标志位flag

//二叉树创建，手动创建
//使用二分查找法
//二叉排序树
#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE -1

int pre = 0; //初始化前驱结点值为0

typedef struct BstNode {            //定义二叉搜索树结构
    int data;
    struct BstNode *Lchild;
    struct BstNode *Rchild;
}BstNode;
typedef struct stack { // 堆栈结构体的定义
    int top; // top为当前栈顶位置下标
    int maxSize; // maxSize-1为堆栈的最大栈顶位置下标
    BstNode *element; // element为结构体BstNode的一维数组
} Stack;

BstNode* GetNewNode(int data);                            //创建一个新结构体并返回
BstNode* Insert_Inner(BstNode* root, int data);          //形式1：使用return返回结构体的形式将参数传递main()
void Insert(BstNode** rootP, int data);                 //形式2：使用指针形式返回结构体
int Search(BstNode* root, int data);             //使用递归查找已有值

void Create(Stack *S, int mSize); // 创建一个能容纳mSize个单元的空堆栈
int IsEmpty(Stack *S); // 判断堆栈是否为空，若为空返回TRUE，否则返回FALSE
int IsFull(Stack *S); // 判断堆栈是否已满，若是，则返回TRUE，否则返回FALSE
BstNode *Top(Stack *S, BstNode *temp); // 获取栈顶元素，通过x返回。返回栈顶元素
int Push(Stack *S, BstNode *x); // 在栈顶插入元素x（入栈）。若操作成功，则返回TRUE，否则返回FALSE
int Pop(Stack *S); // 删除栈顶元素（出栈）。若操作成功，则返回TRUE，否则返回FALSE

void InOrder(BstNode *root);
int BST_judge_v2(BstNode *root);


int main()
{
    BstNode* root = NULL;
    Insert(&root, 5);            // 为保证根结点存在，使用形式二返回根结点
    Insert_Inner(root, 3); // 形式一插入
    Insert_Inner(root, 7);
    Insert_Inner(root, 1);
    Insert_Inner(root, 4);
    Insert_Inner(root, 6);
    Insert_Inner(root, 8);
    Insert_Inner(root, 2);
    // InOrder(root);
    BST_judge_v2(root); // 非递归方式实现判断二叉排序树
    
    return 0;
    
}
//---------------------------------------------------------------
BstNode *GetNewNode(int data)
{
    BstNode *newNode = (BstNode*)malloc(sizeof(BstNode));
    newNode->data = data;
    newNode->Lchild = NULL;
    newNode->Rchild = NULL;
    return newNode;
}

BstNode* Insert_Inner(BstNode* root, int data)
{	
    if(root == NULL) 
    {
		root = GetNewNode(data);
	}
    else if (data <= root->data)
    {
        root->Lchild = Insert_Inner(root->Lchild, data);      //使用递归传递参数
    }
    else
        root->Rchild = Insert_Inner(root->Rchild, data);
    return root;
}

void Insert(BstNode** rootP, int data)
{
    if (*rootP == NULL)
    {
        *rootP = GetNewNode(data);
    }
    else if (data <= (*rootP)->data)
    {
        (*rootP)->Lchild = Insert_Inner((*rootP)->Lchild, data);        //使用函数Insert_Inner递归
    }
    else
        (*rootP)->Rchild = Insert_Inner((*rootP)->Rchild, data);
}
//---------------------------------------------------------------

void Create(Stack *S, int mSize)
{
    S->maxSize = mSize;
    S->element = (BstNode *)malloc(mSize*sizeof(BstNode));
    S->top = -1;
}
void Destroy(Stack *S)
{
    S->maxSize = 0;
    free(S->element);
    S->top = -1;
}
int IsEmpty(Stack *S)
{
    return S->top == -1;
}
int IsFull(Stack *S)
{
    return S->top == S->maxSize - 1;
}
BstNode *Top(Stack *S, BstNode *temp) // 获取栈顶元素，通过x返回。返回栈顶元素
{
    // if (IsEmpty(S)) {
    //     return FALSE;
    // }
    *temp = S->element[S->top];
    // return &(S->element[S->top]); // 返回指向栈顶元素的指针
}
int Push(Stack *S, BstNode *x) // 
{
    if (IsFull(S)) {
        return FALSE;
    }
    S->top++; // 顶层指针+1
    S->element[S->top] = *x; // 修改元素
    return TRUE;
}
int Pop(Stack *S)
{
    if (IsEmpty(S)) {
        return FALSE;
    }
    S->top = S->top - 1;
    return TRUE;
}
int BST_judge_v2(BstNode *root)
{
    Stack *S = (Stack *)malloc(sizeof(Stack)); // 创建辅助数据结构栈（应用指针类型返回）
    Create(S, 10); // 初始化栈
    BstNode *temp = (BstNode *)malloc(sizeof(BstNode)); // 创建临时变量保存
    while (!IsEmpty(S) || root != NULL) {
        while (root != NULL) {
            Push(S, root); // 找到第一个不为null的最左结点,进栈
            root = root->Lchild; // 寻找下一个左列
        }

        root = Top(S, temp); // 现在结点为中间结点
        Pop(S);

        if (root->data <= pre) { // 若前驱结点小于中间结点
            return FALSE;
        }
        pre = root->data;
        root = root->Rchild; // 指向右结点
    }
    return TRUE;
}
void InOrder(BstNode *root)
{
    if (root == NULL) {
        return ;
    }
    InOrder(root->Lchild);
    printf("%d ", root->data);
    InOrder(root->Rchild);
}