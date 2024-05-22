//结构体测试
////------------------------------01定义结构
/*
struct tag {        //tag 是结构体标签。
    member-list     //member-list 是标准的变量定义，比如 int i; 或者 float f;，或者其他有效的变量定义。
    member-list
    member-list     //variable-list 结构变量，定义在结构的末尾，最后一个分号之前，您可以指定一个或多个结构变量。
    ...
} variable-list ;
*/

////------------------------------02三个实例
struct          //没有标签tag的结构体
{
    int a;
    char b;
    double c;
} s1;           //结构体变量s1

struct SIMPLE
{
    int a;
    char b;
    double c;
};              //没有声明结构变量

//struct Simple t1,t2;    //用simple标签的结构体声明新变量t1，t2


typedef struct   //也可以用typedef创建新类型
{
    int a;
    char b;
    double c;
} Simple2;

////------------------------------03结构体的成员可以包含其他结构体，也可以包含指向自己结构体类型的指针，
//  而通常这种指针的应用是为了实现一些更高级的数据结构如链表和树等。

struct COMPLEX
{
    char string[100];
    struct SIMPLE a;    //此结构体的声明包含了其他的结构体
};

struct NODE
{
    char string[100];
    struct NODE* next;
};

struct B;    //对结构体B进行不完整声明

//结构体A中包含指向结构体B的指针
struct A
{
    struct B *partner;
    //other members;
};

////------------------------------04结构体B中包含指向结构体A的指针，在A声明完后，B也随之进行声明
struct B
{
    struct A *partner;
    //other members;
};

////------------------------------05结构体变量初始化
struct Books
{
   char  title[50];
   char  author[50];
   char  subject[100];
   int   book_id;
} book = {"C 语言", "RUNOOB", "编程语言", 123456};

#include<stdio.h>

int main()
{
    //为了访问结构的成员，我们使用成员访问运算符（.）
printf("title : %s\nauthor: %s\nsubject: %s\nbook_id: %d\n", book.title, book.author, book.subject, book.book_id);
}