//使用函数实现反向输出链表,尾节点插入

#include<stdio.h>
#include<stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void Insert();           //尾节点插入
void Print();
void ReversePrint(struct Node*);

struct Node* head;

int main()
{
    head = NULL;
    Insert(2);
    Insert(3);
    Insert(4);
    Insert(5);
    Insert(6);
    Print();
    printf("\n");
    ReversePrint(head);
}

void Insert(int x)
{   
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    struct Node* p = temp;  
    struct Node* q = head;
    temp->data = x;
    temp->next = NULL;
    head = temp;
    if (q == NULL)
        return;
    else
    {
        head = q;
        while (q->next != NULL)
        {
            q = q->next;
        }
        q->next = p;
    }
}

void Print()
{
    struct Node* p = head;
    while (p != NULL)
    {
        printf("%d ",p->data);
        p = p->next;
    }
}

void ReversePrint(struct Node* p)
{
    if (p == NULL)
    {
        return;
    }
    ReversePrint(p->next);
    printf("%d ", p->data);

}