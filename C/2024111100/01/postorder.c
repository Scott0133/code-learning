// 构建平衡二叉搜索树
// 后续遍历测试
// bug fix
#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0

int pre = 0; //初始化前驱结点值为0

typedef struct BstNode {            //定义二叉搜索树结构
    int data;
    struct BstNode *Lchild;
    struct BstNode *Rchild;
}BstNode;

BstNode *Create(int nums[], int low, int high);
BstNode *Create_BST(int nums[], int length);
void Post_Order(BstNode *root);


int main()
{
    int nums[] = {1, 2, 3, 4, 5, 6, 7};
    int length = sizeof(nums) / sizeof(nums[0]);
    BstNode *root = (BstNode *)malloc(sizeof(BstNode));

    root = Create_BST(nums, length);
    Post_Order(root);

    return 0;
    
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
    return Create(nums, 0, length-1); // high为length-1
}
void Post_Order(BstNode *root)
{
    if (root == NULL) {
        return;
    }
    Post_Order(root->Lchild);
    Post_Order(root->Rchild);
    printf("%d ", root->data);
}