#include<stdio.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* head;          //全局变量

void Insert(int x);
void Print();

int main()
{
    head = NULL;
    printf("How many numbers?\n");
    int x,n,i;
    scanf("%d",&n);
    for(i=0; i<n; i++) {
        printf("Enter the numbers:");
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
    while (temp != NULL)
    {
        printf("%d ",temp->data);
        temp = temp->next;
    }
    printf("\n");
}