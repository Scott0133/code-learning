//对有向无环图(Directed Acyclic Graph, DAG)进行拓扑排序
//拓扑排序(Topological Order)
//拓扑排序实现：栈、邻接表
//1、从VOA网中选择一个没有前驱（入度为0）的顶点并输出
//2、从网中删除该顶点和所有以他为起点的有向边
//3、重复1和2直到VOA网为空或当前网中不存在无前驱的顶点为止

#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define MaxVertexNum 100 // 最大顶点数
#define MAXSIZE 100 // 最大栈/数组容量
// 邻接表法创建图
// 顶点数据类型
typedef int VertexType;
// "边/弧"结点
typedef struct ArcNode {
    int Adjvex; //边/弧指向的顶点位置
    struct ArcNode *nextarc; // 指向下一条弧的指针
    //int info; //边权值
}ArcNode;
// "顶点表"结点
typedef struct VNode {
    VertexType data; // 顶点名字
    ArcNode *firstarc; // 第一条边/弧
}VNode, AdjList[MaxVertexNum];
// "图"
typedef struct {
    AdjList vertices; // 邻接表
    int vexnum, arcnum; // 图的顶点数和弧数
}ALGraph, *Graph;
 // 定义顺序栈
typedef struct {
    int stacksize; // 栈数据
    int *top; //栈顶指针
    int *base; //栈底指针
}SqStack;

void InitStack(SqStack *S); // 初始化栈
int Push(SqStack *S, int x); // 入栈
int Pop(SqStack *S, int *e); // 出栈，变量e返回
int IsEmpty(SqStack S); // 判断栈空
void InitALGraph(ALGraph *G); // 初始化图
void AddNewArc(ALGraph *G, int v1, int v2); // 添加一条边
void InitArr(ALGraph *G, int indegree[], int print[]); // 初始化数组
int TopologicalSort(ALGraph *G); // 拓扑排序

int main()
{
    ALGraph G;
    TopologicalSort(&G);

    return 0;
}

int TopologicalSort(ALGraph *G)
{
    SqStack S; // 定义栈
    InitStack(&S); // 初始化栈，存储入度为0的顶点
    InitALGraph(G); //初始化图
    int indegree[MAXSIZE]; // 记录每个结点入度
    int print[MAXSIZE]; // 记录拓扑序列
    InitArr(G, indegree, print); // 初始化记录表
    int i; // 入度为0入栈元素
    int v; // 后续入栈元素
    ArcNode *p; // 声明一个临时存放结点位置的指针p
    for (i=0; i<G->vexnum; i++)
    {
        if (indegree[i] == 0)
        {
            Push(&S, i); // 将所有入度为0的顶点入栈
        }
    }
    int count = 0; // 记录当前已经输出顶点数，设count指向print[0]
    while (!IsEmpty(S))
    {
        Pop(&S, &i); // 栈顶元素出栈
        print[count++] = i; // 输出顶点i
        for (p=G->vertices[i].firstarc; p; p=p->nextarc)
        { // 将所有p指向的顶点入度-1，并且将入度减为0的顶点压入栈
            v = p->Adjvex;
            if (!(--indegree[v]))
            {
                Push(&S, v); // 入度为0，则入栈
            }
        }
    } // while
    if (count < G->vexnum)
        return FALSE; // 排序失败，有向图中有回路
    else
        return TRUE; // 排序成功
}
void InitALGraph(ALGraph *G)
{
    G->arcnum = 5; // 边数
    G->vexnum = 5; // 顶点数
    for (int i = 0; i<G->vexnum; ++i)
    {
        G->vertices[i].data = i; // 假设顶点名字为0, 1, 2, 3, 4
        G->vertices[i].firstarc = NULL; // 初始化每个顶点的第一条边为空
    }
    //添加邻边
    AddNewArc(G, 0, 1); // 0->1->NULL
    AddNewArc(G, 1, 3); // 1->3->NULL
    AddNewArc(G, 2, 4); // 2->4->NULL
    AddNewArc(G, 2, 3); // 2->3->4->NULL
    AddNewArc(G, 3, 4); // 3->4->NULL
                        // 4->NULL
}
void AddNewArc(ALGraph *G, int data, int x) // 建立一条data到x的弧，头插法
{
    ArcNode *newArc = (ArcNode *)malloc(sizeof(ArcNode));
    newArc->Adjvex = x; // newarc的顶点为x
    newArc->nextarc = G->vertices[data].firstarc; // 将newarc的nextarc值置NULL
    G->vertices[data].firstarc = newArc; // 将源顶点的第一条边接到newarc上
}
void InitArr(ALGraph *G, int indegree[], int print[])
{
    for (int i=0; i<G->vexnum; i++)
    {
        print[i] = -1; // 记录的拓扑序列初始化为-1
    }
    // 初始化顶点入度
    indegree[0] = 0;
    indegree[1] = 1;
    indegree[2] = 0;
    indegree[3] = 2;
    indegree[4] = 2;
}
void InitStack(SqStack *S)
{
    //SqStack *S = (SqStack *)malloc(MAXSIZE*sizeof(SqStack));
    //为栈分配内存
    S->base = (int *)malloc(MAXSIZE*sizeof(int)); // 为栈底指针分配MAXSIZE空间
    S->top = S->base;
    S->stacksize = MAXSIZE;
}
int Push(SqStack *S, int x)
{
    if (S->top - S->base == S->stacksize) //栈溢出
    {
        return FALSE;
    }
    *S->top = x;
    S->top = S->top + 1;
    return TRUE;
}
int Pop(SqStack *S, int *e)
{
    if (S->top == S->base) //栈空
    {
        return FALSE;
    }
    S->top = S->top - 1;
    *e = *S->top;
    return TRUE;
}
int IsEmpty(SqStack S)
{
    if (S.top == S.base)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}