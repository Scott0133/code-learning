#include<stdio.h>
#include<stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *head;

void Insert(int x);
void Print();

int main()
{
    head = NULL;

    int i,m,n;
    printf("How many numbers?\n");
    scanf("%d",&n);
    printf("Enter the number:");
    for (i=0; i<n; i++)
    {
        scanf("%d",&m);
        Insert(m);
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
    printf("list is:");
    while (temp != NULL)
    {
        printf("%d ",temp->data);
        temp = temp->next;
    }
    printf("\n");
}