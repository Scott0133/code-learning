//邻接矩阵法创建图
#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0

#define MaxVertexNum 100                        //顶点数目最大值
int visited[MaxVertexNum];                      //创建标记数组，初始化为false;                  

typedef struct {                                //邻接矩阵图的存储
    int Vex[MaxVertexNum];                      //顶点表
    int Edge[MaxVertexNum][MaxVertexNum];       //邻接矩阵，边
    int vexnum, arcnum;                         //图当前的顶点数、边数
}MGraph;

void InitGraph(MGraph *G);

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

    return 0;

}

void InitGraph(MGraph *G)
{

    int j, k;
    for (j=0; j<MaxVertexNum; j++)      //初始化边
    {
        G->Vex[j] = 0;                  //初始化顶点表
        visited[j] = FALSE;             //初始化标记数组
        for(k=0; k<MaxVertexNum; k++)
        {
            G->Edge[j][k] = 0;
        }
    }
    G->vexnum = G->arcnum = 0;          //初始化顶点数、边数
}