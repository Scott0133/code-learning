#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct BstNode {
    int data;
    struct BstNode *Lchild;
    struct BstNode *Rchild;
} BstNode;

typedef struct Stack {
    BstNode *element[100];
    int top;
} Stack;

void Create(Stack *S) {
    S->top = -1;
}

int IsEmpty(Stack *S) {
    return S->top == -1;
}

void Push(Stack *S, BstNode *node) {
    S->element[++(S->top)] = node;
}

BstNode *Pop(Stack *S) {
    return S->element[(S->top)--];
}

BstNode *Top(Stack *S) {
    return S->element[S->top];
}

int BST_judge(BstNode *root) {
    Stack *S = (Stack *)malloc(sizeof(Stack));
    Create(S);
    int pre = INT_MIN;

    while (!IsEmpty(S) || root != NULL) {
        while (root != NULL) {
            Push(S, root);
            root = root->Lchild;
        }

        root = Pop(S);

        if (root->data <= pre) {
            free(S);
            return 0;
        }
        pre = root->data;
        
        root = root->Rchild;
    }
    
    free(S);
    return 1;
}

BstNode *NewNode(int data) {
    BstNode *node = (BstNode *)malloc(sizeof(BstNode));
    node->data = data;
    node->Lchild = NULL;
    node->Rchild = NULL;
    return node;
}

int main() {
    BstNode *root = NewNode(5);
    root->Lchild = NewNode(3);
    root->Rchild = NewNode(7);
    root->Lchild->Lchild = NewNode(2);
    root->Lchild->Rchild = NewNode(4);
    root->Rchild->Lchild = NewNode(6);
    root->Rchild->Rchild = NewNode(8);
    root->Lchild->Lchild->Lchild = NewNode(1);
    root->Rchild->Rchild->Rchild = NewNode(9);

    if (BST_judge(root)) {
        printf("The tree is a Binary Search Tree.\n");
    } else {
        printf("The tree is NOT a Binary Search Tree.\n");
    }

    return 0;
}
