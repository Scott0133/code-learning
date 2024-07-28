//邻接表法创建矩阵

#include<stdio.h>
#define MaxVertexNum 100

// 顶点数据类型
typedef char VertexType;
// "边/弧"
typedef struct ArcNode {
    int Adjvex; //边/弧指向的结点
    struct ArcNode *nextarc; // 指向下一条弧的指针
    //int info; //边权值
}ArcNode;
// "顶点"
typedef struct VNode {
    VertexType data; // 顶点名字
    ArcNode *first; // 第一条边/弧
}VNode, AdjList[MaxVertexNum];
// "图"
typedef struct {
    AdjList vertices;
    int vexnum, arcnum;
}ALGraph;