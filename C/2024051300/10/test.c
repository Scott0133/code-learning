//创建结构，并以结构指针赋值并显示输出

#include<stdio.h>

struct Book {
    int id;
    char name[50];
};

void PrintBook(struct Book *ptr);

int main()
{
    struct Book book1 = {1,'a'};
    struct Book book2 = {23,'b'};
    struct Book book3 = {51,'c'};
    struct Book *ptr;
    ptr = &book1;
    PrintBook(ptr);
    ptr = &book2;
    PrintBook(ptr);
    ptr = &book3;
    PrintBook(ptr);

    return 0;

}

void PrintBook(struct Book *ptr)
{
    printf("book id is %d\n",ptr->id);
    printf("book name is %s\n",ptr->name);
}