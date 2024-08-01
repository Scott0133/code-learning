// 平均查找长度ASL(Average Search Length)
// 顺序查找顺序表中的元素
// 动态分配顺序表

#include<stdio.h>
#include<stdlib.h>
#define INITSIZE 10 // 初始大小为10
#define TRUE 1
#define FALSE -1

typedef struct { // 定义顺序表
    int *data; // 动态分配数组的指针
    int MAXSIZE; // 顺序表当前最大容量
    int length; // 顺序表当前长度
}SqList;

void InitList(SqList *L); // 初始化顺序表
void IncreaseSize(SqList *L, int len); // 增加动态数组的长度
void Insert(SqList *L, int i, int e); // 在顺序表i处插入元素e
void SetNum(SqList *L, int x, int y); // 在顺序表下标x设置数据y
void Print(SqList L);
int Seqrch_Seq(SqList L, int key);

int main()
{
    SqList L; // 定义顺序表
    InitList(&L); // 初始化顺序表
    // 初始化顺序表
    SetNum(&L, 0, 33); //顺序表下标从0开始 
    SetNum(&L, 1, 10);
    SetNum(&L, 2, 13);
    SetNum(&L, 3, 29);
    SetNum(&L, 4, 16);
    SetNum(&L, 5, 19);
    SetNum(&L, 6, 32);
    SetNum(&L, 7, 7);
    SetNum(&L, 8, 43);
    SetNum(&L, 9, 41);
    SetNum(&L, 10, 37);
    int ret = Seqrch_Seq(L, 37);
    printf("%d", ret);
    //IncreaseSize(&L, 5);
    //printf("%d, %d, %d, %d", L.data[0],L.data[1],L.data[2],L.data[3]);
}
void InitList(SqList *L) // 初始化顺序表
{
    L->data = (int *)malloc(INITSIZE*sizeof(int)); // 为顺序表中data分配空间，相当于定义data数组
    L->length = 0; // 初始化表长为0
    L->MAXSIZE = INITSIZE; // 初始化顺序表最大大小为INITSIZE
}
void IncreaseSize(SqList *L, int len) // 动态增加顺序表大小
{
    int *p = L->data; // p为动态分配数组的临时指针，指向源data的位置
    L->data = (int *)malloc((L->MAXSIZE+len)*sizeof(int)); // 为<heap>中的data分配空间，大小为原MAXSIZE大小加len，相当于多分配len大小，并将data指向新空间
    for (int i=0; i<L->length; i++)
    {
        L->data[i] = p[i]; // 将源data数组的值写入新data数组
    }
    L->MAXSIZE = L->MAXSIZE + len; // 更新MAXSIZE大小
    free(p); // 释放临时指针（源数组）
}
void Insert(SqList *L, int i, int e) // 在顺序表i处插入元素e
{
    for (int j=L->length; j>=i; j--) // 将第i个元素及之后的元素后移（若length>i则执行，未考虑越界情况）
    {
        L->data[j] = L->data[j-1]; 
    }
    L->data[i-1] = e; // 在i处插入e
    L->length++; // 表当前长度加一
}
void Print(SqList L)
{
    int i = 0;
    while (L.length != 0)
    {
        printf("%d ", L.data[i++]);
        L.length--;
    }
}
void SetNum(SqList *L, int x, int y)
{
    L->data[x] = y;
    L->length++;
}
int Seqrch_Seq(SqList L, int key) // 顺序查找
{
    int i;
    for (i=0; i<L.length; i++)
    {
        if (L.data[i] == key)
            return L.data[i];
    }
    return FALSE;
}