//结构体的对齐
/*在这个例子中，我们使用#pragma pack(1)预处理指令告诉编译器以字节对齐方式为1来定义结构体。
默认情况下，编译器会进行结构体成员的对齐，以优化访问速度。
通过指定对齐方式为1，我们可以减少内存浪费，但可能会导致访问效率稍微降低。
我们可以使用sizeof运算符来查看对齐后的结构体大小。
*/

#include<stdio.h>
#pragma pack(1)

struct Person {
    char name[20];
    int age;
};

int main()
{
    struct Person p;

    printf("Size of struct Person: %d\n", sizeof(p));

    return 0;
}