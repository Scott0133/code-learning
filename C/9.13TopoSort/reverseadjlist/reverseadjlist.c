#include <stdio.h>
#include <stdlib.h>

typedef struct eNode {
    int adjVex; // 与任意顶点u相邻接的顶点
    struct eNode* nextArc; // 指向下一个边结点
} ENode;

typedef struct vNode {
    ENode* firstArc; // 指向第一条依附该顶点的弧的指针
} VNode, *AdjList;

typedef struct {
    AdjList vertices; // 顶点数组
    int n; // 顶点数
} LGraph;

// 插入边的函数
void InsertEdge(LGraph* lg, int u, int v) {
    ENode* newNode = (ENode*)malloc(sizeof(ENode));
    newNode->adjVex = v;
    newNode->nextArc = lg->vertices[u].firstArc;
    lg->vertices[u].firstArc = newNode;
}

// 反转邻接表的函数
LGraph* ReverseAdjList(LGraph* lg) {
    LGraph* reversedLg = (LGraph*)malloc(sizeof(LGraph));
    reversedLg->n = lg->n;
    reversedLg->vertices = (VNode*)malloc(lg->n * sizeof(VNode));
    for (int i = 0; i < lg->n; i++) {
        reversedLg->vertices[i].firstArc = NULL;
    }

    for (int i = 0; i < lg->n; i++) {
        ENode* p = lg->vertices[i].firstArc;
        while (p) {
            InsertEdge(reversedLg, p->adjVex, i);
            p = p->nextArc;
        }
    }

    return reversedLg;
}

int main() {
    // 创建一个简单的图
    int n = 9; // 顶点数
    LGraph lg;
    lg.n = n;
    lg.vertices = (VNode*)malloc(n * sizeof(VNode));
    for (int i = 0; i < n; i++) {
        lg.vertices[i].firstArc = NULL;
    }

    // 使用插入函数添加边
    InsertEdge(&lg, 0, 2);
    InsertEdge(&lg, 0, 7);
    InsertEdge(&lg, 1, 2);
    InsertEdge(&lg, 1, 4);
    InsertEdge(&lg, 2, 3);
    InsertEdge(&lg, 3, 5);
    InsertEdge(&lg, 3, 6);
    InsertEdge(&lg, 4, 3);
    InsertEdge(&lg, 4, 5);
    InsertEdge(&lg, 7, 8);
    InsertEdge(&lg, 8, 6);

    // 打印原始图的邻接表
    printf("原始图的邻接表:\n");
    for (int i = 0; i < n; i++) {
        printf("顶点 %d: ", i);
        ENode* p = lg.vertices[i].firstArc;
        while (p) {
            printf("%d -> ", p->adjVex);
            p = p->nextArc;
        }
        printf("NULL\n");
    }

    // 反转邻接表
    LGraph* reversedLg = ReverseAdjList(&lg);

    // 打印反转后的邻接表
    printf("\n反转后的邻接表:\n");
    for (int i = 0; i < reversedLg->n; i++) {
        printf("顶点 %d: ", i);
        ENode* p = reversedLg->vertices[i].firstArc;
        while (p) {
            printf("%d -> ", p->adjVex);
            p = p->nextArc;
        }
        printf("NULL\n");
    }

    // 释放内存
    for (int i = 0; i < n; i++) {
        ENode* p = lg.vertices[i].firstArc;
        while (p) {
            ENode* temp = p;
            p = p->nextArc;
            free(temp);
        }
    }
    free(lg.vertices);

    for (int i = 0; i < reversedLg->n; i++) {
        ENode* p = reversedLg->vertices[i].firstArc;
        while (p) {
            ENode* temp = p;
            p = p->nextArc;
            free(temp);
        }
    }
    free(reversedLg->vertices);
    free(reversedLg);

    return 0;
}
