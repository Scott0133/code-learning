//动态分配结构体

#include<stdio.h>
#include<stdlib.h>

struct Person{
    char name[20];
    int age;
};

int main()
{
    //malloc()动态分配Person结构体内存空间，通过sizeof()确定所需内存大小。
    struct Person* person = (struct Person*)malloc(sizeof (struct Person));
    
    if (person == NULL ){
        printf("Memory allocation failed.\n");
        return 1;
    }
    //可以像使用普通结构体一样，访问和操作这个动态分配的结构体。
    strcpy(person->name, "John");
    person->age = 25;
    
    printf("Name: %s\n", person->name);
    printf("age: %d\n",person->age);

    free(person);

    return 0;
}