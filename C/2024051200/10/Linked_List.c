/*
-store a given number of elements of a given data-type
-write/modify element at a position
-read element at a position
*/ 

/*
-empty list has size 0
-insert
-remove
-count
-read /modify
-specify data-type

*/

//linked List: Inserting a node at beginning
#include<stdlib.h>
#include<stdio.h>
void Insert(int x);
void Print();

struct Node {
    int data;
    struct Node* next;
};

struct Node* head; // global variable,can be accessed anywhere

int main() {
    head = NULL; //empty list;
    printf("How many numbers?\n");
    int n,i,x;
    scanf("%d",&n);
    for(i=0;i<n;i++){
        printf("Enter the number \n");
        scanf("%d",&x);
        Insert(x);
        Print();
    }
}

void Insert(int x)
{
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = x;
    temp->next = head;
    head = temp;
}

void Print()
{
    struct Node* temp = head;
    printf("List is: ");
    while(temp != NULL)
    {
        printf(" %d ",temp->data);
        temp = temp->next;
    }

}