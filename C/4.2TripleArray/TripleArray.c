// 三维整型数组的运算

#include<stdio.h>
#include<stdlib.h>
#define ERROR 0
#define OK 1
#define NotPresent 2
#define Duplicate 3
#define IllegalIndex 4
typedef int Status;
typedef struct triplearray {
    int m1;
    int m2;
    int m3;
    int *array;
} TripleArray;
Status CreateArray(TripleArray *triplearray, int m1, int m2, int m3); // 创建运算：申请n维数组A所需存储空间并分配给数组A，成功分配则函数返回OK，否则返回ERROR
Status DestroyArray(TripleArray *triArray); // 清楚运算：判断数组A是否存在，若存在则撤销数组，函数返回OK，否则返回ERROR
Status RetrieveArray(TripleArray triArray, int i1, int i2, int i3, int *x); // 数组元素查询运算：判断数组A是否存在，若不存在返回ERROR,否则对i1，i2，……，in进行边界检查，若
                                                                            // 下标非法，则函数返回ERROR，否则返回下标为i1，i2，……，in的数组元素
Status StoreArrayItem(TripleArray *triArray, int i1, int i2, int i3, int x); // 元素赋值运算：判断数组A是否存在，若不存在返回ERROR,否则对i1，i2，……，in进行边界检查，
                                                                            // 若下标非法，则函数返回ERROR，否则将下标为i1，i2，……，in的数组元素值设置为x，函数返回OK
void OutputArray(TripleArray triArray); // 数组输出运算：判断数组A是否存在，若不存在，则函数返回，否则将数组中所有元素依次输出
Status CopyArray(TripleArray *triArrayA, TripleArray *triArrayB); // 数组复制运算：判断 数组A和B是否存在，若A或B不存在，则返回函数ERROR，否则判断数组A和B大小是否相同（每维度大小相同）
                                                                    //若不同，则函数返回ERROR，否则将数组A中元素依次复制到数组B中


int main()
{
    int i1, i2, i3;
    TripleArray TripleArrayA, TripleArrayB;
    CreateArray(&TripleArrayA, 2, 2, 2);
    CreateArray(&TripleArrayB, 2, 2, 2);
    for (i1=0; i1<TripleArrayA.m1; i1++) {
        for (i2=0; i2<TripleArrayA.m2; i2++) {
            for (i3=0; i3<TripleArrayA.m3; i3++) {
                StoreArrayItem(&TripleArrayA, i1, i2, i3, 10);
                StoreArrayItem(&TripleArrayB, i1, i2, i3, 5);
            }
        }
    }
    OutputArray(TripleArrayA);
    OutputArray(TripleArrayB);
    CopyArray(&TripleArrayA ,&TripleArrayB);
    OutputArray(TripleArrayA);
    OutputArray(TripleArrayB);
    
}

Status CreateArray(TripleArray *triArray, int m1, int m2, int m3)
{
    triArray->m1 = m1;
    triArray->m2 = m2;
    triArray->m3 = m3;
    triArray->array = (int *)malloc(m1*m2*m3*sizeof(int));
    if (!triArray->array) {
        return ERROR;
    }
    return OK;
}
Status DestroyArray(TripleArray *triArray)
{
    if(!triArray)
        return ERROR;
    if (triArray->array)
        free(triArray->array);
    return OK;
}
Status RetrieveArray(TripleArray triArray, int i1, int i2, int i3, int *x)
{
    if (!triArray.array) {
        return NotPresent;
    }
    if (i1<0 || i2<0 || i3<0 || i1>=triArray.m1 || i2>=triArray.m2 || i3>=triArray.m3)
        return IllegalIndex;
    *x = *(triArray.array + i1*triArray.m2*triArray.m3 + i2*triArray.m3 + i3);
    return OK;
}
Status StoreArrayItem(TripleArray *triArray, int i1, int i2, int i3, int x)
{
    if (!triArray->array)
        return NotPresent;
    if (i1<0 || i2<0 || i3<0 || i1>=triArray->m1 || i2>=triArray->m2 || i3>=triArray->m3)
        return IllegalIndex;
    *(triArray->array + i1*triArray->m2*triArray->m3 + i2*triArray->m3 + i3) = x;
    return OK;
}
void OutputArray(TripleArray triArray)
{
    int i1, i2, i3;
    if (!triArray.array) {
        return;
    }
    for (i1=0; i1<triArray.m1; i1++) {
        for (i2=0; i2<triArray.m2; i2++) {
            for (i3=0; i3<triArray.m3; i3++) {
                int value;
                RetrieveArray(triArray, i1, i2, i3, &value);
                printf("array[%d][%d][%d] = %d\n", i1, i2, i3, value);
            }
        }
    }
}
Status CopyArray(TripleArray *triArrayA, TripleArray *triArrayB)
{
    int i1, i2, i3;
    if (!triArrayA->array || !triArrayB->array)
        return NotPresent;
    if (triArrayA->array == triArrayB->array)
        return Duplicate;
    if (triArrayA->m1 != triArrayB->m1 || triArrayA->m2 != triArrayB->m2 || triArrayA->m3 != triArrayB->m3)
        return ERROR;
    for (i1=0; i1<triArrayA->m1; i1++) {
        for (i2=0; i2<triArrayA->m2; i2++) {
            for (i3=0; i3<triArrayA->m3; i3++) {
                int value;
                RetrieveArray(*triArrayA, i1, i2, i3, &value);
                StoreArrayItem(triArrayB, i1, i2, i3, value);
            }
        }
    }
    return OK;
}