// copilot
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
typedef struct stack {
    int* data;
    int top;
    int maxSize;
} Stack;

void InsertEdge(LGraph* lg, int u, int v);
int ReverseTopoSort(int* topo, LGraph* lg);

// 反转邻接表的函数
LGraph* ReverseAdjList(LGraph* lg) {
    LGraph* reversedLg = (LGraph*)malloc(sizeof(LGraph));
    reversedLg->n = lg->n;
    reversedLg->vertices = (VNode*)malloc(lg->n * sizeof(VNode));
    for (int i = 0; i < lg->n; i++) {
        reversedLg->vertices[i].firstArc = NULL;
    }

    for (int i = 0; i < lg->n; i++) { // 遍历图的所有边，将所有边反转
        ENode* p = lg->vertices[i].firstArc;
        while (p) {
            InsertEdge(reversedLg, p->adjVex, i);
            p = p->nextArc;
        }
    }

    return reversedLg;
}

int main() 
{
    // 创建一个简单的图
    int n = 9; // 顶点数
    LGraph lg;
    lg.n = n;
    lg.vertices = (VNode*)malloc(n * sizeof(VNode)); // 初始化顶点
    for (int i = 0; i < n; i++) {
        lg.vertices[i].firstArc = NULL;
    }
    // 插入边
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

    LGraph* reversedLg = ReverseAdjList(&lg); // 反转邻接表
    
    // // 打印图的邻接表
    // for (int i = 0; i < n; i++) {
    //     printf("顶点 %d: ", i);
    //     ENode* p = reversedLg->vertices[i].firstArc;
    //     while (p) {
    //         printf("%d -> ", p->adjVex);
    //         p = p->nextArc;
    //     }
    //     printf("NULL\n");
    // }
    int *topo = (int *)malloc(lg.n*sizeof(int)); // 初始化topo数组

    ReverseTopoSort(topo, reversedLg);
}

void InsertEdge(LGraph* lg, int u, int v) { // 顶点u到顶点v的边
    ENode* newNode = (ENode*)malloc(sizeof(ENode));
    newNode->adjVex = v;
    newNode->nextArc = lg->vertices[u].firstArc;
    lg->vertices[u].firstArc = newNode;
}

void Create_stack(Stack* S, int size) {
    S->data = (int*)malloc(size * sizeof(int));
    S->top = -1;
    S->maxSize = size;
}

int IsEmpty(Stack* S) {
    return S->top == -1;
}

void Push(Stack* S, int x) {
    if (S->top < S->maxSize - 1) {
        S->data[++S->top] = x;
    }
}

void Pop(Stack* S) {
    if (!IsEmpty(S)) {
        S->top--;
    }
}

void Top(Stack* S, int* x) {
    if (!IsEmpty(S)) {
        *x = S->data[S->top];
    }
}

void CalculateOutDegree(int* OutDegree, LGraph* lg) {
    int i;
    ENode* p;
    for (i = 0; i < lg->n; i++) {
        OutDegree[i] = 0; // 初始化出度为0
    }
    for (i = 0; i < lg->n; i++) {
        for (p = lg->vertices[i].firstArc; p; p = p->nextArc) {
            OutDegree[p->adjVex]++; // 计算每个顶点的出度
        }
    }
}

int ReverseTopoSort(int* topo, LGraph* lg) {
    int i, j, k;
    ENode* p;
    Stack S;
    int* OutDegree = (int*)malloc(lg->n * sizeof(int));
    
    Create_stack(&S, lg->n);
    CalculateOutDegree(OutDegree, lg);
    for (i = 0; i < lg->n; i++) {
        if (!OutDegree[i]) {
            Push(&S, i);
        }
    }
    int index = 0;
    while (!IsEmpty(&S)) {
        Top(&S, &j);
        Pop(&S);
        topo[index++] = j;
        printf("%d ", j);
        for (p = lg->vertices[j].firstArc; p; p = p->nextArc) {
            k = p->adjVex;
            OutDegree[k]--;
            if (!OutDegree[k]) {
                Push(&S, k);
            }
        }
    }
    if (index != lg->n) {
        return -1; // 若未处理完所有顶点，说明有回路，返回ERROR
    }
    free(OutDegree);
    return 0; // 返回成功
}