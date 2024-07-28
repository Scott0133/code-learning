//floyd算法
//使用邻接矩阵
#include<stdio.h>
#define TRUE 1
#define FALSE 0
#define MaxVertexNum 100
#define INF 9999


typedef struct {                                //邻接矩阵图的存储，及path表，path表存储中转路径
    char Vex[MaxVertexNum];                     //顶点表名字
    int A[MaxVertexNum][MaxVertexNum];          //邻接矩阵，路径
    int path[MaxVertexNum][MaxVertexNum];
    int vexnum, arcnum;                         //图当前的顶点数、路径数
}MGraph;

void Floyd(MGraph *G);
void InitGraph(MGraph *G);

int main()
{
    MGraph G;
    InitGraph(&G);
    Floyd(&G);

    return 0;
}

void InitGraph(MGraph *G)
{   
    //总结点数
    G->vexnum = 3;
    //总路径数
    G->arcnum = 5;
    //初始化名字
    G->Vex[0] = 'A';
    G->Vex[1] = 'B';
    G->Vex[2] = 'C';
    //初始化邻接矩路径，初始化path表
    int i, j; //i为行号，j为列号
    for (i=0; i<G->vexnum; i++)
    {
        for (j=0; j<G->vexnum; j++)
        {
            G->A[i][j] = 0;
            G->path[i][j] = -1;
        }
    }
    //设置路径
    G->A[0][1] = 6;
    G->A[0][2] = 13;
    G->A[1][0] = 10;
    G->A[1][2] = 4;
    G->A[2][0] = 5;
    G->A[2][1] = INF;
}

void Floyd(MGraph *G)
{
    for (int k=0; k<G->vexnum; k++) { //考虑以k作为中转点
        for (int i=0; i<G->vexnum; i++) { //i为行号，j为列号，遍历整个矩阵
            for (int j=0; j<G->vexnum; j++) {
                if (G->A[i][j] > G->A[i][k] + G->A[k][j])
                {
                    G->A[i][j] = G->A[i][k] + G->A[k][j]; //更新路径信息
                    G->path[i][j] = k; //更新path表信息
                }
            }
        }
    }
}