// 构建平衡二叉搜索树
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

BstNode *Create(int nums[], int low, int high);
BstNode *Create_BST(int nums[], int length);



int main()
{
    int nums[] = {7, 2, 3, 5, 8, 9};
    int length = sizeof(nums) / sizeof(nums[0]);
}

BstNode *Create(int nums[], int low, int high)
{
    int mid; // 
    if (low > high) return NULL;
    mid = (low+high)/2;
    BstNode *root = (BstNode *)malloc(sizeof(BstNode));
    root->data = nums[mid];
    root->Lchild = Create(nums, low, mid-1);
    root->Rchild = Create(nums, mid+1, high);

    return root;
}
BstNode *Create_BST(int nums[], int length)
{
    return Create(nums, 0, length);
}