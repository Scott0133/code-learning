#include<stdio.h>
#include<stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *head;          //global variable

void Insert(int x);
void Print();

int main()
{
    head = NULL;
    printf("How many numbers?\n");
    int n,m,i;
    scanf("%d",&n);
    for (i=0; i<n; i++)
    {
        printf("Enter the number:\n");
        scanf("%d",&m);
        Insert(m);
        Print();
        printf("\n");
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
    struct Node *temp = head;
    
    printf("list is: ");
    while(temp != NULL)
    {
        printf("%d ",temp->data);
        temp = temp->next;
    }
}