//创建一个链表，并插入元素

#include<stdio.h>
#include<stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *head;

void Print();
void Insert(int x);

int main()
{   
    head = NULL;
    int a,b,i;
    printf("How many numbers:\n");
    scanf("%d",&a);
    for(i=0; i<a; i++)
    {
        printf("enter the number");
        scanf("%d",&b);
        Insert(b);
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
