//BFS算法求无权图的单源最短路径
//邻接矩阵法创建图
//图的广度优先遍历(Breadth-First-Traversal, BFS)
//fixbug
//图的深度优先遍历(Depth-First Traversal, DFS)
//BFS算法求最短路径
#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE -1
#define MaxVertexNum 100                        //顶点数目最大值
#define INF 999

int visited[MaxVertexNum];                      //创建标记数组，若已处理数组则标记为TRUE，初始化为FALSE;                  

typedef struct {                                //邻接矩阵图的存储
    int Vex[MaxVertexNum];                      //顶点表
    int Edge[MaxVertexNum][MaxVertexNum];       //邻接矩阵，边
    int vexnum, arcnum;                         //图当前的顶点数、边数
}MGraph, *GRAPH;

////////////////////////////////////////////////////////////////////////////链式队列结构体定义
typedef struct LinkNode {           //链式队列结点
    int data;               
    struct LinkNode *next;
}LinkNode;

typedef struct {                    //链式队列
    LinkNode *front, *rear;         //队列的头指针尾指针
}LinkQueue;
////////////////////////////////////////////////////////////////////////////


//-----------------------------------------------------//辅助队列
void InitQueue(LinkQueue *Q);                              //初始化队列
int  IsEmpty(LinkQueue Q);                                 //判断队列是否为空
void EnterQueue(LinkQueue *Q, int v);                      //插入队列，将图结点
int  DeleteQueue(LinkQueue *Q, int *v);                    //移除队列
//-----------------------------------------------------//BFS操作
void InitGraph(MGraph *G);
int FirstNeighbor(MGraph G, int x);                        //求图G中顶点x的第一个邻接点，若有则返回顶点号；若x没有邻接点或不存在x，则返回-1
int NextNeighbor(MGraph G, int x, int y);                  //假设图G中顶点y是顶点x的一个邻接点，返回除y之外顶点x的下一个邻接点的顶点号，(????)若y是x的最后一个邻接点，则返回-1
void BFS(MGraph G, int v);                                 //广度优先遍历
void BFSTraverse(MGraph G);                                //对整个图搜索
void Visit(MGraph G, int v);                               //访问顶点
//-----------------------------------------------------//DFS操作
void DFS(MGraph G, int v);                                 //深度优先遍历
void DFSTraverse(MGraph G);
//-----------------------------------------------------//DFS求顶点u到其他顶点最短路径（无源）
void BFS_Min_Dist(MGraph G, int u);                        //BFS算法求最短路径
void Print_Dist(MGraph G, int u,int dist[]);                                 //打印距离u的长度



int main()
{
    MGraph G;
    InitGraph(&G);
    for (int i=1; i<9; i++)                     //定义顶点
    {
        G.Vex[i] = i;
    }                                           //定义矩阵边
    G.Edge[1][2] = G.Edge[2][1] = TRUE;
    G.Edge[1][5] = G.Edge[5][1] = TRUE;
    G.Edge[2][6] = G.Edge[6][2] = TRUE;
    G.Edge[6][3] = G.Edge[3][6] = TRUE;
    G.Edge[6][7] = G.Edge[7][6] = TRUE;
    G.Edge[3][7] = G.Edge[7][3] = TRUE;
    G.Edge[3][4] = G.Edge[4][3] = TRUE;
    G.Edge[4][7] = G.Edge[7][4] = TRUE;
    G.Edge[7][8] = G.Edge[8][7] = TRUE;
    G.Edge[4][8] = G.Edge[8][4] = TRUE;
    G.vexnum = 8;

    // BFS(G, 2);
    // BFSTraverse(G);                             //遍历所有图
    //DFS(G, 2);
    //DFSTraverse(G);                                //遍历所有图
    BFS_Min_Dist(G, 2);
    return 0;

}
//----------------------------------------------------------//队列操作
void InitQueue(LinkQueue *Q)
{
    Q->front = Q->rear = (LinkNode *)malloc(sizeof(LinkNode));
    Q->front->next = NULL;                                      //front指向头结点
}
int IsEmpty(LinkQueue Q)
{
    if (Q.front == Q.rear)
        return TRUE;
    else
        return FALSE;
}
void EnterQueue(LinkQueue *Q, int v)
{
    LinkNode *s = (LinkNode *)malloc(sizeof(LinkNode));
    s->data = v;
    s->next = NULL;
    Q->rear->next = s;
    Q->rear = s;
}
int DeleteQueue(LinkQueue *Q, int *v)
{
    if (Q->front == Q->rear)
        return FALSE;
    LinkNode *p = Q->front->next;
    *v = p->data;
    Q->front->next = p->next;
    if (Q->rear == p)
        Q->rear = Q->front;
    free(p);
    return TRUE;
}
//----------------------------------------------------------//图操作
void InitGraph(MGraph *G)
{
    int j, k;
    for (j=1; j<MaxVertexNum; j++)      //初始化边
    {
        G->Vex[j] = 0;                  //初始化顶点表
        visited[j] = FALSE;             //初始化标记数组
        for(k=1; k<MaxVertexNum; k++)
        {
            G->Edge[j][k] = 0;
        }
    }
    G->vexnum = G->arcnum = 0;          //初始化顶点数、边数
}

int FirstNeighbor(MGraph G, int x)      //求图G中顶点x的第一个邻接点，若有则返回顶点号；若x没有邻接点或不存在x，则返回-1
{
    for (int i=1; i<G.vexnum+1; i++)
    {
        if (G.Edge[x][i] == TRUE)
        {
            return G.Vex[i];
        }
    }
    return -1;
}
int NextNeighbor(MGraph G, int x, int y)//假设图G中顶点y是顶点x的一个邻接点，返回除y之外顶点x的下一个邻接点的顶点号，若y是x的最后一个邻接点（未找到下一邻接点），则返回-1
{
    for (int i=y+1; i<G.vexnum+1; i++)
    {
        if (G.Edge[x][i] == TRUE)
        {
            return G.Vex[i];
        }
    }
    return -1;
}
void BFSTraverse(MGraph G)
{
    int i;
    for (i=1; i<G.vexnum; ++i)          //从1号顶点开始遍历
    {
        if (!visited[i])
        {
            BFS(G, i);
        }
    }
}

void BFS(MGraph G, int v)
{
    LinkQueue Q;                         //创建临时辅助队列
    InitQueue(&Q);
    Visit(G, v);
    visited[v] = TRUE;                   //对v做已访问标记
    EnterQueue(&Q, v);                   //顶点v入列Q
    while (IsEmpty(Q) == FALSE)          //如果队列非空
    {
        DeleteQueue(&Q, &v);
        for (int w=FirstNeighbor(G, v); w>=0; w=NextNeighbor(G, v, w))
        {
        //检测v所有结点
            if (visited[w] == FALSE)             //w为v尚未访问的相邻结点
            {
                Visit(G, w);
                visited[w] = TRUE;
                EnterQueue(&Q, w);
            }
        }
    }
}

void Visit(MGraph G, int v)
{
    v = G.Vex[v];
    printf("%d ", v);
}

void DFS(MGraph G, int v)
{
    Visit(G, v);
    visited[v] = TRUE;
    for (int w=FirstNeighbor(G, v); w>=0; w=NextNeighbor(G, v, w))
    {
        if (visited[w] == FALSE)
        {
            DFS(G, w);          //利用栈的特性
        }
    }
}

void DFSTraverse(MGraph G)
{
    int i;
    for (i=1; i<G.vexnum; ++i)          //从1号顶点开始遍历
    {
        if (!visited[i])
        {
            DFS(G, i);
        }
    }
}

void BFS_Min_Dist(MGraph G, int u)
{
    int v = u;
    int temp = G.vexnum + 1; //数组大小
    int dist[temp]; //路径长度数组，并初始化
    int path[temp]; //路径的直接前驱（路径末尾的上一个顶点），并初始化
    LinkQueue Q; //创建临时辅助队列
    InitQueue(&Q); //初始化临时队列
    for (int i=0; i<G.vexnum; i++) //初始化记录表
    {
        dist[i] = INF;
        path[i] = -1;
    }
    dist[u] = 0; //设置起始结点的距离为0

    visited[u] = TRUE;                   //对u做已访问标记
    EnterQueue(&Q, u);                   //顶点u入列Q
    while (IsEmpty(Q) == FALSE)          //如果队列非空
    {
        DeleteQueue(&Q, &u);
        for (int w=FirstNeighbor(G, u); w>=0; w=NextNeighbor(G, u, w))
        {
        //检测u所有结点
            if (visited[w] == FALSE)             //w为u尚未访问的相邻结点
            {
                dist[w] = dist[u] + 1; //路径长度加一
                path[w] = u; //路径从u到w
                visited[w] = TRUE;
                EnterQueue(&Q, w);
            }
        }
    }
    Print_Dist(G, v, dist);
}

void Print_Dist(MGraph G, int u,int dist[])
{
    for (int i=1; i<G.vexnum+1; i++)
    {
        printf("the distance between %d and %d is %d\n", G.Vex[i], u, dist[i]);
    }
}