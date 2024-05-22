//指向结构的指针
#include<stdio.h>

struct Books
{
    char title[50];
    int id;
};

/*函数声明*/
void printBook_as_struct_pointer(struct Books *book);   //*book为结构体指针

int main()
{
    struct Books book1 = {"TCPL",1};    //声明结构体变量book1并初始化
    struct Books book2 = {"CPP",2};     //声明结构体变量book2并初始化

    printBook_as_struct_pointer(&book1);    //访问方式1
    printBook_as_struct_pointer(&book2);

    struct Books* ptr;                      //*ptr也是指向Books的结构体指针
    ptr = &book1;
    printBook_as_struct_pointer(ptr);       //访问方式2

    ptr = &book2;
    printBook_as_struct_pointer(ptr);

    return 0;
}

void printBook_as_struct_pointer(struct Books *book)
{
    printf("book name is %s \n",book->title);
    printf("book id is %d \n",book->id);
}