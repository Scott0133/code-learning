//结构体作为函数的返回值
/*在这个例子中，我们定义了一个返回`Point`结构体的函数`getPoint()`。
在函数内部，我们创建一个`Point`结构体并设置其坐标值。
然后，我们将该结构体作为函数的返回值返回，并在`main()`函数中接收并打印返回的结构体的坐标值。
我们将getPoint()函数的返回类型改为指向Point结构体的指针。
在函数内部，我们使用malloc()动态分配了一个Point结构体的内存，并设置其坐标值。
然后，我们返回指向动态分配内存的指针。在main()函数中，我们接收返回的指针，并使用箭头运算符访问结构体的成员。
最后，记得使用free()函数释放动态分配的内存空间，以避免内存泄漏。*/

#include<stdio.h>
#include<stdlib.h>

struct Point {
    int x;
    int y;
};

struct Point* getPoint();

int main()
{
    struct Point* result = getPoint();
    printf("Point coordinates:(%d %d)\n", result->x,result->y);

    free(result);

    return 0;
}

struct Point* getPoint(){
    struct Point* p = (struct Point*)malloc(sizeof(struct Point));
    p->x = 10;
    p->y = 20;

    return p;
}