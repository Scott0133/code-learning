#include<stdio.h>
#include<stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* head;          //将头节点设置为全局变量

void Insert(int x);              //使用头插法将数据插入链表
void Print();               //顺序打印链表
void Delete(int x);         //在x位置删除元素
void ReversePrint(struct Node* p);        //使用递归方法逆序打印链表
void Print_in_rec(struct Node* p2);

int main()
{
    head = NULL;
    printf("How many number?");
    int i,m,n;
    scanf("%d",&m);
    for (i=0; i<m; i++)
    {
        printf("Enter the number:");
        scanf("%d",&n);
        Insert(n);
        Print();
    }

    Delete(5);
    Print();
    Delete(3);
    Print();
    //ReversePrint(head);
    //printf("\n");
    //Print_in_rec(head);
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
    struct Node* temp1 = head;
    while(temp1 != NULL)
    {
    //printf("List is: ");
    printf("%d ",temp1->data);
    temp1 = temp1->next;
    }

    printf("\n");
}

void Delete(int x)               //实现2<n<NULL位置删除一个节点
{
    int i;
    struct Node* front;
    struct Node* del;
    struct Node* rear;
    front = head;
    if (x == 1)
    {
        head = front->next;
        free(front);
        return;
    }
    for (i=0; i<x-2; i++)
    {
        front = front->next;
    }
    del = front->next;
    rear = del->next;
    front->next = rear;
    if (rear = NULL)
    {
        front = NULL;
        free(rear);
    }
    free(del);
}

void ReversePrint(struct Node* p)
{
    if ( p == NULL )
    {
    return;
    }  
    else
    {
        ReversePrint(p->next);      //先进行递归，后返回逆序
        printf("%d ",p->data);
    }
}

void Print_in_rec(struct Node* p2)
{
    if ( p2 == NULL )
    {
    return;
    }  
    else
    {
        printf("%d ",p2->data);
        Print_in_rec(p2->next);     //弹出空地址NULL五次
        printf("\n");                //test
    }
}