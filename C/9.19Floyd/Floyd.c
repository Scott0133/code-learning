// Floyd算法实现所有顶点之间的最短路径
// 辅助数据结构：
    // 一维数组d[]，表示顶点之间的最短路径
    // 一维数组p[]，表示最短路径顶点的直接前驱

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
#define INFTY 32767 // 定义权值的极大值
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

void Floyd(MGraph mg); // Floyd算法

int main()
{
    // 测试图9.22(a)带权有向图G
    MGraph mg;
    InitGraph(&mg, 4, INFTY);
    Insert(&mg, 0, 1, 1);
    Insert(&mg, 0, 3, 4);
    Insert(&mg, 1, 3, 2);
    Insert(&mg, 1, 2, 9);
    Insert(&mg, 2, 0, 3);
    Insert(&mg, 2, 3, 8);
    Insert(&mg, 2, 1, 5);
    Insert(&mg, 3, 2, 6);
    // Print(mg);
    Floyd(mg);
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
            if (mg.a[i][j] == INFTY) {
                printf("∞ "); continue;
            }
            printf("%d ", mg.a[i][j]);
        }
    }
}
void Floyd(MGraph mg)
{
    int i, j, k;
    ElemType **d = (ElemType **)malloc(mg.n*sizeof(ElemType *)); // 为二维数组d分配存储空间
    int **p = (int **)malloc(mg.n*sizeof(int *)); // 为二维数组p分配存储空间
    for (i=0; i<mg.n; i++) {
        d[i] = (ElemType *)malloc(mg.n*sizeof(ElemType));
        p[i] = (int *)malloc(mg.n*sizeof(int));
        for (j=0; j<mg.n; j++) {
            d[i][j] = mg.noEdge;
            p[i][j] = 0;
        }
    }
    for (i=0; i<mg.n; i++) {
        for (j=0; j<mg.n; j++) { // 初始化d和p
            d[i][j] = mg.a[i][j];
            if (i!=j && mg.a[i][j]<INFTY) {
                p[i][j] = i;
            } else {
                p[i][j] = -1;
            }
        }
    }
    for (k=0; k<mg.n; k++) { // Floyd算法
        for (i=0; i<mg.n; i++) {
            for (j=0; j<mg.n; j++) {
                if (d[i][k]+d[k][j] < d[i][j]) { // 更新d和p
                    d[i][j] = d[i][k]+d[k][j];
                    p[i][j] = p[k][j];
                }
            }
        }
    }
    printf("d[][]:\n");
    for (i=0; i<mg.n; i++) {
        for (j=0; j<mg.n; j++) {
            printf("%d ", d[i][j]);
        }
        printf("\n");
    }
    printf("p[][]:\n");
    for (i=0; i<mg.n; i++) {
        for (j=0; j<mg.n; j++) {
            printf("%d ", p[i][j]);
    }
    printf("\n");
}
}