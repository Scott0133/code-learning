// 线性表顺序结构实现

#include<stdio.h>
#include<stdlib.h>
// 顺序表初始化
#define ERROR 0
#define OK 1
#define OverFlow 2 // 上溢
#define UnderFlow 3 // 下溢
#define NotPresent 4 // 元素不存在
#define Duplicate 5 // 元素重复
typedef int Elemtype; // 将Elemtype定义为整型
// 结构体定义
typedef struct seqList {
    int n; // 顺序表长度
    int maxLength; // 顺序表最大允许长度
    Elemtype *element; // 顺序表存储空间首地址
} SeqList;
int Init(SeqList *L, int mSize); // 顺序表初始化
int Find(SeqList L, int i, Elemtype *x); // 顺序表查找
int Insert(SeqList *L, int i, Elemtype x); // 顺序表元素插入
int Delete(SeqList *L, int i); // 顺序表元素删除
int Output(SeqList *L); // 顺序表输出
void Destroy(SeqList *L); // 顺序表撤销

int main()
{
    SeqList L;
    int i;
    Init(&L, 10); // 初始化线性表，最大长度为10
    for (i=0; i<10; i++) {
        Insert(&L, i-1, i); // 线性表中插入新元素
    }
    Output(&L);
    Delete(&L, 0);
    Output(&L);
    Destroy(&L);
    
    return 0;
}

int Init(SeqList *L, int mSize) // 顺序表初始化
{
    L->maxLength = mSize; // 初始化线性表大小
    L->n = 0; // 初始化顺序表长度为0
    L->element = (Elemtype *)malloc(mSize * sizeof(Elemtype)); // 为存储空间分配大小
    if (!L->element) {
        return ERROR;
    }
    return OK;
}
int Find(SeqList L, int i, Elemtype *x) // 顺序表查找，i为元素下标，*x返回元素
{
    if (i<0 || i>L.n-1) { // 判断查找下标i是否越界
        return ERROR;
    }
    *x = L.element[i]; // 取出element[i]的值通过*x返回
    return OK;
}
int Insert(SeqList *L, int i, Elemtype x) // 顺序表元素插入，将新元素放入下标i+1的位置，x为插入元素
{
    int j;
    if (i<-1 || i>L->n-1) { // 判断下标i是否越界
        return ERROR;
    }
    if (L->n == L->maxLength) { // 判断顺序表空间是否已满
        return ERROR;
    }
    for (j = L->n-1; j>i; j--) { // 从后往前逐个后移元素
        L->element[j+1] = L->element[j];
    }
    L->element[i+1] = x; // 将新元素放入下标i+1的位置
    L->n = L->n+1;
    return OK;
}
int Delete(SeqList *L, int i) // 顺序表元素删除，删除位置i的上一个元素
{
    int j;
    if (i<0 || i>L->n-1) { // 下标i是否越界
        return ERROR;
    }
    if (!L->n) {
        return ERROR;
    }
    for (j=i+1; j<L->n; j++) { // 从前往后逐个前移元素
        L->element[j-1] = L->element[j];
    }
    L->n--; // 表长减一
    return OK;
}
int Output(SeqList *L) // 顺序表输出
{
    int i;
    if (L->n == 0) { // 判断顺序表是否为空
        return ERROR;
    }
    for (i=0; i<=L->n-1; i++) {
        printf("%d ", L->element[i]); // 从前往后逐个输出元素
    }
    printf("\n");
    return OK;
}
void Destroy(SeqList *L) // 顺序表撤销
{
    L->n = 0;
    L->maxLength = 0;
    free(L->element);
}