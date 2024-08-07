// Binary Search Tree - Implemenation in C++(now in C)
// Simple program to create a BST of integers and search an element in it 
#include<stdio.h>
#include<stdlib.h>
#define false -1
#define true 1

//Definition of Node for Binary search tree
typedef struct BstNode {
	int data; 
	struct BstNode* left;
	struct BstNode* right;
}BstNode;

// Function to create a new Node in heap
BstNode* GetNewNode(int data) {
	//BstNode* newNode = new BstNode();
    BstNode* newNode = (BstNode*)malloc(sizeof(BstNode));
	newNode->data = data;
	newNode->left = newNode->right = NULL;
	return newNode;
}

// To insert data in BST, returns address of root node 
BstNode* Insert(BstNode* root,int data) {
	if(root == NULL) { // empty tree
		root = GetNewNode(data);
	}
	// if data to be inserted is lesser, insert in left subtree. 
	else if(data <= root->data) {
		root->left = Insert(root->left,data);
	}
	// else, insert in right subtree. 
	else {
		root->right = Insert(root->right,data);
	}
	return root;
}
//To search an element in BST, returns true if element is found
int Search(BstNode* root,int data) {
	if(root == NULL) {
		return false;
	}
	else if(root->data == data) {
		return true;
	}
	else if(data <= root->data) {
		return Search(root->left,data);
	}
	else {
		return Search(root->right,data);
	}
}
int main() {
	BstNode* root = NULL;  // Creating an empty tree
	/*Code to test the logic*/
	root = Insert(root,15);	
	root = Insert(root,10);	
	root = Insert(root,20);
	root = Insert(root,25);
	root = Insert(root,8);
	root = Insert(root,12);
	// Ask user to enter a number.  
	int number;
	printf("Enter number be searched\n");
	scanf("%d", &number);
	//If number is found, print "FOUND"
	if(Search(root,number) == true)
    {
        printf("Found\n");
    }
	else
    {
        printf("Not Found\n");
    }
}