// 图的邻接矩阵法实现
// 包含顶点数、边数、权值、无边值
#include<stdio.h>
#include<stdlib.h>
#define ERROR 0
#define OK 1
#define Overflow 2
#define Underflow 3
#define NotPresent 4
#define Duplicate 5
typedef int ElemType; // 定义变量类型为整型
typedef struct mGraph { // 邻接矩阵法结构体定义
    ElemType **a; // 邻接矩阵，指针a指向动态生成的二维数组
    int n; // 图的当前顶点数
    int e; // 图的当前边数
    ElemType noEdge; // 两顶点间无边时的值
}MGraph;
int InitGraph(MGraph *mg, int nSize, int noEdgeValue); // 邻接矩阵初始化
void Destroy(MGraph *mg); // 邻接矩阵的撤销
int Exist(MGraph *mg, int u, int v); // 搜索边是否存在
int Insert(MGraph *mg, int u, int v, ElemType w); // 插入边
int Remove(MGraph *mg, int u, int v); // 删除边
void Print(MGraph mg); // 打印图

int main()
{
    // 测试图9.10 G4
    MGraph mg;
    InitGraph(&mg, 4, 0);
    Insert(&mg, 0, 1, 1);
    Insert(&mg, 0, 3, 1);
    Insert(&mg, 1, 0, 1);
    Insert(&mg, 1, 2, 1);
    Insert(&mg, 2, 1, 1);
    Insert(&mg, 2, 3, 1);
    Insert(&mg, 3, 0, 1);
    Insert(&mg, 3, 2, 1);

    // Remove(&mg, 3, 2);
    Print(mg);

    return 0;
}

int InitGraph(MGraph *mg, int nSize, int noEdgeValue) // 参数为图指针，顶点数，顶点无边时的值
{
    mg->n = nSize; // 初始化顶点数
    mg->e = 0; // 初始化边为0
    mg->noEdge = noEdgeValue; // 初始化无边时的值
    mg->a = (ElemType **)malloc(nSize*sizeof(ElemType*)); // 为二维数组分配空间(生成长度为nSize的一维指针数组)
    if (!mg->a) { // 动态分配二维数组失败
        return ERROR;
    }
    for (int i=0; i<mg->n; i++) { // 动态生成二维数组
        mg->a[i] = (ElemType*)malloc(sizeof(ElemType));
        for (int j=0; j<mg->n; j++) { // 初始化所有顶点的边值
            mg->a[i][j] = mg->noEdge;
        }
        mg->a[i][i] = 0; // 初始化顶点到自身的距离为0
    }
    return OK;
}
/*
第一个 malloc 函数：
mg->a = (ElemType **)malloc(nSize * sizeof(ElemType*));

这个 malloc 函数用于为二维数组分配空间。具体来说，它分配了一个长度为 nSize 的一维指针数组，每个元素都是指向 ElemType 类型的指针。这样做的目的是为每个顶点分配一个指针，以便稍后可以为每个顶点分配具体的边值。

第二个 malloc 函数：
mg->a[i] = (ElemType*)malloc(sizeof(ElemType));

这个 malloc 函数在循环中被调用，用于为每个顶点分配一个 ElemType 类型的空间。这样，每个顶点都有一个独立的空间来存储边值。
*/
void Destroy(MGraph *mg)
{
    for (int i=0; i<mg->n; i++) {
        free(mg->a[i]); // 释放n个一维数组存储空间
        free(mg->a); // 释放一维指针数组存储空间
    }
}
int Exist(MGraph *mg, int u, int v) // 参数为图指针，横坐标下标，纵坐标下标（从0开始）
{
    if (u<0 || v<0 || u>mg->n-1 || v>mg->n-1 || u==v || mg->a[u][v] == mg->noEdge) { // 参数u、v无效或边不存在
        return ERROR;
    } else {
        return OK;
    }
}
int Insert(MGraph *mg, int u, int v, ElemType w) // 参数为图指针，横坐标下标，纵坐标下标（从0开始），边的权值
{
    if (u<0 || v<0 || u>mg->n-1 || v>mg->n-1 || u==v) { // 参数u、v无效
        return ERROR;
    }
    if (mg->a[u][v] != mg->noEdge) { // 若待插入边已存在
        return Duplicate;
    }
    mg->a[u][v] = w; // 插入新边
    mg->e++; // 边数加1
    return OK;
}
int Remove(MGraph *mg, int u, int v) // 参数为图指针，横坐标下标，纵坐标下标（从0开始）
{
    if (u<0 || v<0 || u>mg->n-1 || v>mg->n-1 || u==v) { // 参数u、v无效
        return ERROR;
    }
    if (mg->a[u][v] == mg->noEdge) { // 若待删除边不存在
        return NotPresent;
    }
    mg->a[u][v] = mg->noEdge; // 删除指定边
    mg->e--; // 边数减1
    return OK;
}
void Print(MGraph mg)
{
    for (int i=0; i<mg.n; i++) {
        printf("\n");
        for (int j=0; j<mg.n; j++) {
            printf("%d ", mg.a[i][j]);
        }
    }
}