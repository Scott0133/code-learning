//Dijkstra算法————带权图的最短路径问题
//ALLBUG

#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define MaxVertexNum 100                        //顶点数目最大值
#define INF 999

int visited[MaxVertexNum];                      //创建标记数组，若已处理数组则标记为TRUE，初始化为FALSE;                  

typedef struct {                                //邻接矩阵图的存储
    char Vex[MaxVertexNum];                                //顶点表名字
    int arcs[MaxVertexNum][MaxVertexNum];       //邻接矩阵，弧
    int vexnum, arcnum;                         //图当前的顶点数、边数
}MGraph, *GRAPH;

void InitGraph(MGraph *G);
void SetGraph(MGraph *G);
int FirstNeighbor(MGraph G, int x); //求图G中顶点x的第一个邻接点，若有则返回顶点号；若x没有邻接点或不存在x，则返回-1
int NextNeighbor(MGraph G, int x, int y);
void Dijkstra(MGraph G, int v); //Dijkstra算法流程
int BubbleSort(int *arr, int size);

int main()
{
    MGraph G;
    InitGraph(&G);
    SetGraph(&G);

    Dijkstra(G, 2);

    return 0;
}

void InitGraph(MGraph *G)
{
    int j, k;
    for (j=1; j<MaxVertexNum; j++) //初始化边
    {
        visited[j] = FALSE; //初始化标记数组
        for(k=1; k<MaxVertexNum; k++)
        {
            G->arcs[j][k] = INF; //初始化邻接矩阵
        }
    }
    G->vexnum = G->arcnum = 0; //初始化顶点数、边数
}
void SetGraph(MGraph *G)
{
    //初始化结点名
    G->Vex[1] = 'A'; G->Vex[2] = 'B'; G->Vex[3] = 'C'; G->Vex[4] = 'D'; G->Vex[5] = 'E';
    //设置权值
    G->arcs[1][2] = 10;
    G->arcs[1][5] = 5;
    G->arcs[2][3] = 1;
    G->arcs[2][5] = 2;
    G->arcs[3][4] = 4;
    G->arcs[4][1] = 7;
    G->arcs[4][3] = 6;
    G->arcs[5][2] = 3;
    G->arcs[5][3] = 9;
    G->arcs[5][4] = 2;
    G->vexnum = 5; G->arcnum = 10; //顶点数与边数
}

void Dijkstra(MGraph G, int v)
{
    // 初始化起始结点
    int final[G.vexnum + 1]; // 标记各顶点是否为已找到最短路径
    int dist[G.vexnum + 1]; // 最短路径长度
    int path[G.vexnum + 1]; // 前驱
    final[1] = TRUE; // 初始顶点开始
    dist[1] = 0; // 初始点距离置0
    path[1] = -1; // 初始点前驱置-1
    // 初始化其余结点
    int k; // 其余结点
    for (k=2; k<=G.vexnum; k++)
    {
        final[k] = FALSE; // 初始化其余顶点最短路径
        dist[k] = G.arcs[1][k]; // 若存在弧长，则设置顶点v与k的弧长
        path[k] = (G.arcs[1][k] == INF) ? -1 : 1; // 若不存在弧长则设置其余顶点路径为-1，与v相邻顶点k路径设置为1
    }

        /*
            第1轮处理，循环遍历所有顶点，找到还没确定的最短路径，且dist最小的顶点v，令final[v]=true。并检查所有邻接自v的顶点j。
            对于j，若final[j] == false且dist[v] + arcs[v][j] < dist[j]，则令dist[j] = dist[v] + arcs[v][j]; path[j] = v;
        */

    
    int j; // 下一结点
    int min = dist[v];
    for (j=1; j<=G.vexnum; j++) // 找到还没确定的最短路径
    {
        if (final[j] == FALSE)
        {
            if (min > dist[j])
            {
                final[j] = TRUE; // 令final[j] = TRUE
                min = dist[j];
            }
        }
    }
    
    j = j - 1; //???
    //int min_2 = dist[v];
    for (int i=1; i<=G.vexnum; i++) // 第二轮遍历，检查j的邻接点（找到j的最短路径邻接点）
    {
        if (G.arcs[j][i] != INF)
        {
            if (path[i] == path[v] && dist[v] > G.arcs[j][i] + dist[j]) // 若前驱相同且找到更短路径
            {
                dist[v] = G.arcs[j][i] + dist[j]; // 修改最小值
                path[v] = j; // 修改路径
            }
        }
        if (dist[i] == INF) // 若下一结点距离为空
        {
            dist[i] = G.arcs[j][i] + dist[j]; // 写入值
            path[i] = j; // 修改路径
        }
    }
//--------------------------------------------------------test
    // min = dist[2];
    // for (j=1; j<=G.vexnum; ++j) // 找到还没确定的最短路径
    // {
    //     if (final[j] == FALSE)
    //     {
    //         // int min_3 = BubbleSort(dist, 6);
    //         if (min > dist[j])
    //         {
    //             final[j] = TRUE; // 令final[j] = TRUE
    //             min = dist[j];
    //         }
    //     }
    // }
    j = 4;
    //  for (int i=1; i<=G.vexnum; i++) // 第二轮遍历，检查j的邻接点（找到j的最短路径邻接点）
    // {
    //     if (G.arcs[j][i] != INF)
    //     {
    //         if (path[i] == path[v] && dist[v] > G.arcs[j][i] + dist[j]) // 若前驱相同且找到更短路径
    //         {
    //             dist[v] = G.arcs[j][i] + dist[j]; // 修改最小值
    //             path[v] = j; // 修改路径
    //         }
    //     }
    //     if (dist[i] == INF) // 若下一结点距离为空
    //     {
    //         dist[i] = G.arcs[j][i] + dist[j]; // 写入值
    //         path[i] = j; // 修改路径
    //     }
    // }


}

int FirstNeighbor(MGraph G, int x) //求图G中顶点x的第一个邻接点，若有则返回顶点号；若x没有邻接点或不存在x，则返回-1
{
    for (int i=1; i<G.vexnum+1; i++)
    {
        if (G.arcs[x][i] == TRUE)
        {
            return G.Vex[i];
        }
    }
    return -1;
}
int NextNeighbor(MGraph G, int x, int y) //假设图G中顶点y是顶点x的一个邻接点，返回除y之外顶点x的下一个邻接点的顶点号，若y是x的最后一个邻接点（未找到下一邻接点），则返回-1
{
    for (int i=y+1; i<G.vexnum+1; i++)
    {
        if (G.arcs[x][i] == TRUE)
        {
            return G.Vex[i];
        }
    }
    return -1;
}

int BubbleSort(int *arr, int size) {
    int i, j, tmp;
    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
    return tmp;
}
