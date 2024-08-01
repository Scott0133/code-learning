// 采用DFS算法实现逆拓扑排序
// 邻接矩阵法创建图
// 不考虑环路情况
#include<stdio.h>
#define MaxVertexNum 100 // 定义矩阵大小
#define INF 9999 // 定义无穷
#define TRUE 10
#define FALSE -1
int visited[MaxVertexNum]; // 创建标记数组，若已处理数组则标记为TRUE，初始化为FALSE;   

typedef struct { // 邻接矩阵图的存储
    int Vex[MaxVertexNum]; // 顶点
    int Edge[MaxVertexNum][MaxVertexNum]; // 邻接矩阵，边
    int vexnum, arcnum; // 图当前的顶点数、边数
}MGraph;

int FirstNeighbor(MGraph G, int x);
int NextNeighbor(MGraph G, int x, int y);
void DFS(MGraph G, int v);
void DFSTraverse(MGraph G);
void Visit(MGraph G, int v);
void InitGraph(MGraph *G);
void InitvisitedArr(MGraph G, int visited[]);

int main()
{
    MGraph G; // 创建图
    InitGraph(&G); // 初始化图
    InitvisitedArr(G, visited); // 初始化visit数组
    DFSTraverse(G); // 逆拓扑排序，深度优先遍历实现

    return 0;
}

void InitGraph(MGraph *G) // 初始化邻接图
{
    G->vexnum = 5; // 定义顶点数
    G->arcnum = 5; // 定义边数
    for (int i=0; i<G->vexnum; i++) // 初始化边
    {
        G->Vex[i] = i; // 初始化顶点
        for (int j=0; j<G->vexnum; j++)
        {
            G->Edge[i][j] = INF; // 初始化边距离无穷
            if (i == j)
            {
                G->Edge[i][j] = 0; // 将自身距离设置为0
            }
        }
    } // for
    G->Edge[0][1] = TRUE;
    G->Edge[1][3] = TRUE;
    G->Edge[2][3] = TRUE;
    G->Edge[2][4] = TRUE;
    G->Edge[3][4] = TRUE;
}
void InitvisitedArr(MGraph G, int visited[])
{
    for (int i=0; i<MaxVertexNum; i++)
    {
        visited[i] = FALSE; // 初始化visited数组
    }
}
void DFS(MGraph G, int v) // 深度优先遍历
{
    visited[v] = TRUE;
    for (int w=FirstNeighbor(G, v); w>=0; w=NextNeighbor(G, v, w))
    {
        if (visited[w] == FALSE)
        {
            DFS(G, w); // 利用栈的特性
        }
    }
    Visit(G, v);
}
void DFSTraverse(MGraph G)
{
    int v;
    for (v=0; v<G.vexnum; ++v) // 从0号顶点开始遍历
    {
        if (visited[v] == FALSE)
        {
            DFS(G, v);
        }
    }
}
int FirstNeighbor(MGraph G, int x) // 求图G中顶点x的第一个邻接点，若有则返回顶点号；若x没有邻接点或不存在x，则返回-1
{
    for (int i=0; i<G.vexnum; i++)
    {
        if (G.Edge[x][i] == TRUE)
        {
            return G.Vex[i];
        }
    }
    return -1;
}
int NextNeighbor(MGraph G, int x, int y) // 假设图G中顶点y是顶点x的一个邻接点，返回除y之外顶点x的下一个邻接点的顶点号，若y是x的最后一个邻接点（未找到下一邻接点），则返回-1
{
    for (int i=y+1; i<G.vexnum; i++) // y是顶点i的下一个顶点
    {
        if (G.Edge[x][i] == TRUE)
        {
            return G.Vex[i];
        }
    }
    return -1;
}
void Visit(MGraph G, int v)
{
    v = G.Vex[v];
    printf("%d ", v);
}
