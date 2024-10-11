// Kruskal算法实现最小代价生成树
// 引入以下辅助数据结构：
    // 一维结构体数组edgeSet[]，从邻接矩阵获取所有的边存入edgeSet[]，并进行排序
    // 一维数组vexSet[]，用于标识各顶点所属连通分量，初始时vexSet[i]=i，标识各顶点自成一个连通分量
// 函数SelectSort()采用简单排序算法

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
typedef int ElemType;
typedef struct mGraph { // 邻接矩阵法结构体定义
    ElemType **a; // 邻接矩阵，指针a指向动态生成的二维数组
    int n; // 图的当前顶点数
    int e; // 图的当前边数
    ElemType noEdge; // 两顶点间无边时的值
}MGraph;
typedef struct edge { // 一维结构体数组定义
    int u;
    int v;
    ElemType w;
}Edge;
int InitGraph(MGraph *mg, int nSize, int noEdgeValue); // 邻接矩阵初始化
void Destroy(MGraph *mg); // 邻接矩阵的撤销
int Exist(MGraph *mg, int u, int v); // 搜索边是否存在
int Insert(MGraph *mg, int u, int v, ElemType w); // 插入边
int Remove(MGraph *mg, int u, int v); // 删除边
void Print(MGraph mg); // 打印图

void SelectSort(Edge *eg, int n); // 对图中的边按权值递增排序
void Kruskal(MGraph g);

int main()
{
    // 图9.18 带权连通图G
    MGraph mg;
    InitGraph(&mg, 6, 0); // 初始化顶点数、无边值
    Insert(&mg, 0, 1, 10); Insert(&mg, 1, 0, 10);
    Insert(&mg, 1, 4, 2); Insert(&mg, 4, 1, 2);
    Insert(&mg, 0, 5, 4); Insert(&mg, 5, 0, 4);
    Insert(&mg, 4, 5, 7); Insert(&mg, 5, 4, 7);
    Insert(&mg, 2, 5, 6); Insert(&mg, 5, 2, 6);
    Insert(&mg, 5, 3, 5); Insert(&mg, 3, 5, 5);
    Insert(&mg, 0, 2, 7); Insert(&mg, 2, 0, 7);
    Insert(&mg, 2, 3, 8); Insert(&mg, 3, 2, 8);
    Insert(&mg, 3, 4, 9); Insert(&mg, 4, 3, 9);

    // Print(mg);
    Kruskal(mg);

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
            printf("%d ", mg.a[i][j]);
        }
    }
}
void SelectSort(Edge *eg, int n) // 简单选择排序
{
    int small, i, j;
    Edge t;
    for (i=0; i<n-1; i++) { // 执行n-1趟
        small = i; // 假定待排序序列中第一个元素最小
        for (j=i+1; j<n; j++) { // 执行n-1趟
            if (eg[j].w < eg[small].w) { // 如果扫描到比最小值还小的元素，则记下其下标
                small = j; // 记下标
            }
            t = eg[i]; // 最小元素与待排序序列中第一个元素交换
            eg[i] = eg[small];
            eg[small] = t;
        }
    }
}
void Kruskal(MGraph mg)
{
    int i, j, k, u1, v1, vs1, vs2;
    int *vexSet = (int *)malloc(mg.n*sizeof(int));
    Edge *edgeSet = (Edge *)malloc(mg.e*sizeof(Edge));
    k = 0;
    for (i=0; i<mg.n; i++) { // 由邻接矩阵产生边集数组
        for (j=0; j<i; j++) {
            if (mg.a[i][j]!=0 && mg.a[i][j]!=mg.noEdge) {
                edgeSet[k].u = i;
                edgeSet[k].v = j;
                edgeSet[k].w = mg.a[i][j];
                k++;
            }
        }
    }
    SelectSort(edgeSet, mg.e/2); // 对边集数组排序，为无向图，边数=e/2
    for (i=0; i<mg.n; i++) {
        vexSet[i] = i;
    }
    k = 0;
    j = 0;
    while (k<mg.n-1) { // 加入n-1条边
        u1 = edgeSet[j].u;
        v1 = edgeSet[j].v;
        vs1 = vexSet[u1];
        vs2 = vexSet[v1];
        if (vs1 != vs2) { // 若vs1和vs2不相等，表示u和v属于不同连通分量
            printf("%d, %d, %d\n", edgeSet[j].u, edgeSet[j].v, edgeSet[j].w); // 输出边
            k++; // 边数+1
            for (i=0; i<mg.n; i++) { // 合并u和v所属的不同连同分量
                if (vexSet[i] == vs2) {
                    vexSet[i] = vs1;
                }
            }
        }
        j++;
    }
}