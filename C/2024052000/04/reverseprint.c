//在任意位置插入节点
//在指定位置删除节点
//用递归方式正向、反向打印链表

#include<stdio.h>
#include<stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* head;

void Insert(int data,int n);
void Print();
void Delete();
void Print_with_recursion();
void ReversePrint();

int main()
{
    head = NULL;
    Insert(2,1);
    Insert(3,2);
    Insert(4,1);
    Insert(5,2);
    Insert(6,3);
    Delete(3);
    Delete(1);
    Print();
    printf("\n");
    Print_with_recursion(head);
    printf("\n");
    ReversePrint(head);

}

void Insert(int data,int n)
{
    struct Node* temp1 = (struct Node*)malloc(sizeof(struct Node));
    temp1->data = data;
    temp1->next = NULL;
    if (n == 1) {
        temp1->next = head;
        head = temp1;
        return;
    }

    struct Node* temp2 = head;

    for (int i=0; i<n-2; i++)
    {
        temp2 = temp2->next;
    }
    temp1->next = temp2->next;
    temp2->next = temp1;
}

void Print()
{
    struct Node* temp = head;
    while(temp != NULL) {
        printf("%d",temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void Delete(int n)
{
    struct Node* temp1 = head;
    if (n == 1)
    {
        head = temp1->next;
        free(temp1);
        return;
    }

    int i;
    for (i=0; i<n-2; i++)
    {
        temp1 = temp1->next;
    }
    struct Node* temp2 = temp1->next;
    temp1->next = temp2->next;
    free(temp2);
}

void Print_with_recursion(struct Node* p)       //递归正向打印
{
    if (p == NULL)
    {
        return;
    }
    printf("%d ",p->data);
    Print_with_recursion(p->next);
}

void ReversePrint(struct Node* p)                             //递归逆向打印
{
        if (p == NULL)
    {
        return;
    }
    ReversePrint(p->next);
    printf("%d ",p->data);
}