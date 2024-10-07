//最小生成树————Prim算法
// 以顶点2为中心的网
#include <stdio.h>
#include <stdbool.h>

#define MAXV 100 //矩阵最大数为
#define INF 32767

// 定义图的邻接矩阵结构
typedef struct {
    int edges[MAXV][MAXV]; // 存储边的权重
    int n, e; // 结点数和边数
} MatGraph;

void CreateMat(MatGraph *g, int A[MAXV][MAXV], int n, int e);  // 创建图的邻接矩阵
void Prim(MatGraph g);   // Prim算法实现

int main() {
    MatGraph g;
    int A[MAXV][MAXV] = {
        {0, 6, 1, 5, INF, INF},
        {6, 0, 5, INF, 3, INF},
        {1, 5, 0, 5, 6, 4},
        {5, INF, 5, 0, INF, 2},
        {INF, 3, 6, INF, 0, 6},
        {INF, INF, 4, 2, 6, 0}};
    CreateMat(&g, A, 6, 10);

    printf("Prim algorithm result:\n");
    Prim(g);

    return 0;
}

void CreateMat(MatGraph *g, int A[MAXV][MAXV], int n, int e) {
    int i, j;
    g->n = n;
    g->e = e;
    for (i = 0; i < g->n; i++) {
        for (j = 0; j < g->n; j++) {
            g->edges[i][j] = A[i][j];
        }
    }
}

void Prim(MatGraph g) {
    int lowcost[MAXV]; // 记录结点到最小生成树的最小权值
    int closest[MAXV]; // 记录最小权值的边的另一端结点
    bool visited[MAXV]; // 记录结点是否已加入最小生成树(记录已访问结点)
    int i, j, k, min, m, sum = 0; // i用于遍历每条边，j用于遍历所有结点，k记录权值最小的边的另一端结点，min用于记录当前权值最小的边的权值。
    // 初始化操作
    for (i=1; i<g.n; i++) {
        lowcost[i] = g.edges[0][i]; // 初始状态为与第一个结点相连的边的权值
        closest[i] = 0; // 初始状态下最近的结点为第一个结点
        visited[i] = false; // 初始状态下所有结点都未加入最小生成树
    }
    visited[0] = true; // 第一个结点已加入最小生成树
    // Prim算法主体
    for (i=1; i<g.n; i++) { //遍历每条边，从1开始
        min = INF;
        for (j=1; j<g.n; j++) {
            if (!visited[j] && lowcost[j] < min) {
                min = lowcost[j];
                k = j; // 找到权值最小的边
            }
        }
        printf("Edge (%d, %d) with weight %d\n", closest[k], k, min); // 输出最小权值边的信息
        sum += min; // 累加权值
        visited[k] = true; // 标记为已访问结点，将该结点加入最小生成树
        // 更新lowcost和closest数组
        for (m=1; m<g.n; m++) {
            if (!visited[m] && g.edges[k][m] < lowcost[m]) {
                lowcost[m] = g.edges[k][m];
                closest[m] = k;
            }
        }
    }
    printf("Total weight of minimum spanning tree: %d\n", sum); // 输出最小生成树的总权值
}