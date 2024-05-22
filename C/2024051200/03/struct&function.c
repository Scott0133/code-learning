//结构体作为函数参数传递

#include<stdio.h>
#include<string.h>
struct Books            //tag为Books的结构体
{
    char title[50];
    int book_id;
};

/*函数声明*/
void printBook(struct Books book);

int main()
{
    struct Books book1 = {"TCPL",1};    //声明结构体变量book1并初始化
    struct Books book2 = {"CPP",2};     //声明结构体变量book2并初始化
    
    printBook(book1);
    printBook(book2);

    printf("the size of book1 is %d",sizeof(book1));
    return 0;
};

void printBook(struct Books book)
{
    printf("book name is %s \n",book.title);
    printf("book id is %d \n",book.book_id);
}