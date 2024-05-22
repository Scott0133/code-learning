//结构体自引用初探————静态链表

#include<stdio.h>
 struct Node 
 {
    int data;
    struct Node* next;      //结构体的自我调用
 };

int main()
{
    struct Node node1,node2,node3;

    node1.data = 2;
    node2.data = 4;
    node3.data = 6;

    struct Node *start = &node1;        //头节点从node1开始

    node1.next = &node2;
    node2.next = &node3;
    node3.next = NULL;                  //到NULL结束

    PrintNode(start);
    
    return 0;
    
}

void PrintNode(struct Node *current)
{
    while (current != NULL)
    {
        printf("current node data is %d \n",current->data);
        current = current->next;
    }
}