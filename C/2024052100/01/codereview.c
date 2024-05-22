#include<stdio.h>
#include<stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* head;          //全局变量

void Insert();
void Print();
void Delete();
void ReversePrint();
void List_Print();

int main()
{
    head = NULL;

    printf("How many numbers?");
    int i,m,n;
    scanf("%d", &n);
    for(i=0; i<n; i++)
    {
        printf("Enter the numbers:");
        scanf("%d", &m);
        Insert(m);
        Print();
    }
    //Delete();
    //Print();

    ReversePrint(head);
    printf("\n");
    List_Print(head);
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

void Delete()       //location 2
{
    struct Node* front;
    struct Node* later;
    struct Node* del;
    front = head;
    del = front->next;
    later = del->next;
    front->next = later;
    free(del);
}

void ReversePrint(struct Node *temp)     //递归调用需要参数，逆向输出
{
    if (temp == NULL)
    {
        return;
    }
    ReversePrint(temp->next);
    printf("%d ",temp->data);
}

void List_Print(struct Node *temp)     //递归调用需要参数，正向输出
{
    if (temp == NULL)
    {
        return;
    }

    printf("%d ",temp->data);
    List_Print(temp->next);
}