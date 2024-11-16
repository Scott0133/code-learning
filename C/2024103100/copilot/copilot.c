// 通过给出的先序、中序遍历创建二叉树（递归算法） 
// copilot
#include <stdio.h>
#include <stdlib.h>

typedef struct BstNode {
    int data;
    struct BstNode *Lchild;
    struct BstNode *Rchild;
} BstNode;

BstNode *NewNode(int data) {
    BstNode *node = (BstNode *)malloc(sizeof(BstNode));
    node->data = data;
    node->Lchild = NULL;
    node->Rchild = NULL;
    return node;
}

BstNode *CreateTree(int Pre[], int In[], int l1, int h1, int l2, int h2) {
    if (h1 < l1) {
        return NULL;
    }

    BstNode *root = (BstNode *)malloc(sizeof(BstNode));
    root->data = Pre[l1];
    
    int i;
    for (i = l2; i <= h2; i++) {
        if (In[i] == Pre[l1]) {
            break;
        }
    }

    root->Lchild = CreateTree(Pre, In, l1 + 1, l1 + i - l2, l2, i - 1);
    root->Rchild = CreateTree(Pre, In, l1 + i - l2 + 1, h1, i + 1, h2);

    return root;
}

void PrintInOrder(BstNode *node) {
    if (node == NULL) {
        return;
    }
    PrintInOrder(node->Lchild);
    printf("%d ", node->data);
    PrintInOrder(node->Rchild);
}

void PrintPreOrder(BstNode *node) {
    if (node == NULL) {
        return;
    }
    printf("%d ", node->data);
    PrintPreOrder(node->Lchild);
    PrintPreOrder(node->Rchild);
}

int main() {
    int Pre[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int In[] = {3, 2, 4, 1, 5, 7, 8, 6};
    int n = sizeof(Pre) / sizeof(Pre[0]);

    BstNode *root = CreateTree(Pre, In, 0, n - 1, 0, n - 1);

    printf("Inorder traversal: ");
    PrintInOrder(root);
    printf("\n");

    printf("Preorder traversal: ");
    PrintPreOrder(root);
    printf("\n");

    return 0;
}
