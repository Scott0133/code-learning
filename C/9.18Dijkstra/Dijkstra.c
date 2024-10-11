// Dijkstra算法求单源最短路径
// 辅助数据结构如下：
    // 一维数组final[]记录源点v0到顶点i的最短路径是否已经确定
    // 一维数组dist[]记录从源点v0到顶点i的当前最短路径长度
    // 一维数组path[]记录从源点v0到顶点i的当前最短路径上的顶点i的直接前驱顶点的序号        
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
int Choose(int *dist, int *final, int n); // 选出最小的dist[i]
int Dijkstra(int v, ElemType *dist, int *path, MGraph mg);

int main()
{
    // 测试图9.19(a)带权有向图G
    MGraph mg;
    InitGraph(&mg, 6, INFTY);
    Insert(&mg, 0, 1, 50);
    Insert(&mg, 0, 4, 80);
    Insert(&mg, 0, 2, 10);
    Insert(&mg, 1, 4, 20);
    Insert(&mg, 1, 2, 15);
    Insert(&mg, 2, 3, 15);
    Insert(&mg, 3, 1, 20);
    Insert(&mg, 3, 4, 45);
    Insert(&mg, 5, 4, 10);
    Insert(&mg, 5, 3, 9);
    ElemType dist[10]; // 一维数组dist[]记录从源点v0到顶点i的当前最短路径长度
    int path[10]; // 一维数组path[]记录从源点v0到顶点i的当前最短路径上的顶点i的直接前驱顶点的序号  
    // Print(mg);
    Dijkstra(0, dist, path, mg);

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
int Choose(int *dist, int *final, int n)
{
    int i, minpos;
    ElemType min;
    min = INFTY; // 定义最小值为极大，便于与任意有效值交换
    minpos = -1; // 初始化minpos为-1，便于与任意有效下标交换
    for (i=0; i<n; i++) {
        if (dist[i]<min && !final[i]) { // 选出最小值和下标
            min = dist[i];
            minpos = i;
        }
    }
    return minpos; // 返回下标位置
}
int Dijkstra(int v, ElemType *dist, int *path, MGraph mg)
{
    int i, k, w;
    int *final; // 定义final[]
    if (v<0 || v>mg.n-1) {
        return ERROR;
    }
    final = (int *)malloc(mg.n*sizeof(int));
    for (i=0; i<mg.n; i++) { // 初始化final[]，dist[]，path[]
        final[i] = 0;
        dist[i] = mg.a[v][i];
        if (i!=v && dist[i]<INFTY) {
            path[i] = v;
        } else {
            path[i] = -1;
        }
    }
    final[v] = 1; // 顶点v为源点
    dist[v] = 0;
    for (i=1; i<mg.n-1; i++) { // 处理其余n-1个顶点
        k = Choose(dist, final, mg.n);
        if (k == -1) continue;
        final[k] = 1; // k加入final
        // printf("%d ", k);
        for (w=0; w<mg.n; w++) { // 更新dist和path
            if (!final[w] && dist[k]+mg.a[k][w]<dist[w]) {
                dist[w] = dist[k] + mg.a[k][w];
                path[w] = k;
            }
        }
    }
    printf("path[v]:");
    for (i=0; i<mg.n; i++) {
        printf("%d ", path[i]);
    }
    printf("\ndist[v]:");
    for (i=0; i<mg.n; i++) {
        if (dist[i] == INFTY) {
            printf("∞ ");
        } else {
            printf("%d ", dist[i]);
        }
    }
    return OK;
}