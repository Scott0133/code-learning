//最小生成树————Kruskal算法
#include <stdio.h>
//#include <limits.h>
#define INF 32767 //定义无穷
#define V 6 // 默认结点数

//---------------------------------------//并查集↓↓
// 初始化并查集
int parent[V];

// 查找结点所属集合的根结点
int find(int i) {
    while (parent[i] != i)
        i = parent[i];
    return i;
}

// 合并两个不同集合
void union1(int i, int j) {
    int a = find(i);
    int b = find(j);
    parent[a] = b;
}
//---------------------------------------//并查集↑↑
// Kruskal 算法主体
void kruskalMST(int A[V][V]) {
    int mincost = 0; // 最小生成树的总权值

    // 初始化并查集
    for (int i = 0; i < V; i++)
        parent[i] = i;

    int edge_count = 0; // 记录已加入最小生成树的边数

    while (edge_count < V - 1) {
        int min = INF, a = -1, b = -1;

        // 找到权值最小的边
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (find(i) != find(j) && A[i][j] < min) {
                    min = A[i][j];
                    a = i;
                    b = j;
                }
            }
        }

        // 如果不形成环路，则将该边加入最小生成树
        if (a != -1 && b != -1) {
            union1(a, b);
            printf("Edge %d: (%d, %d) A: %d\n", edge_count++, a, b, min);
            mincost += min;
        }
    }
    printf("\nMinimum A of MST: %d\n", mincost);
}

int main() {
    // 邻接矩阵表示的图（结点为6，边数为8）
    int A[V][V] = {
        {INF, 2, INF, 6, INF, INF},
        {2, INF, 3, 8, 5, INF},
        {INF, 3, INF, INF, 7, INF},
        {6, 8, INF, INF, 9, INF},
        {INF, 5, 7, 9, INF, 4},
        {INF, INF, INF, INF, 4, INF}
    };
    // 执行 Kruskal 算法
    kruskalMST(A);

    return 0;
}
