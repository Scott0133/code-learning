#include <stdio.h>
#include <limits.h>

#define MAX_SIZE 5

void dijkstra(int graph[MAX_SIZE][MAX_SIZE], int start) {
    int i, j, k;
    int dist[MAX_SIZE]; // 最短路径长度
    int prev[MAX_SIZE]; // 前驱顶点
    int visited[MAX_SIZE] = {0}; // 标记已访问的顶点

    // 初始化
    for (i = 0; i < MAX_SIZE; i++) {
        dist[i] = INT_MAX; // 初始化距离为无穷大
        prev[i] = -1; // 初始化前驱顶点为无效值
    }
    dist[start] = 0; // 起点到自身的距离为0

    // 迭代
    for (i = 0; i < MAX_SIZE; i++) {
        int min_dist = INT_MAX;
        for (j = 0; j < MAX_SIZE; j++) {
            if (!visited[j] && dist[j] < min_dist) {
                min_dist = dist[j];
                k = j; // 选出距离最短的顶点
            }
        }
        visited[k] = 1; // 将该顶点标记为已访问

        for (j = 0; j < MAX_SIZE; j++) {
            if (!visited[j] && graph[k][j] != INT_MAX) {
                int new_dist = dist[k] + graph[k][j];
                if (new_dist < dist[j]) {
                    dist[j] = new_dist; // 更新最短路径长度
                    prev[j] = k; // 更新前驱顶点
                }
            }
        }
    }

    // 输出最短路径
    printf("起点到各顶点的最短路径长度：\n");
    for (i = 0; i < MAX_SIZE; i++) {
        printf("顶点 %c：%d\n", 'A' + i, dist[i]);
    }
}

int main() {
    int graph[MAX_SIZE][MAX_SIZE] = {
        {INT_MAX, 10, INT_MAX, INT_MAX, 5},
        {INT_MAX, INT_MAX, 1, INT_MAX, 2},
        {INT_MAX, INT_MAX, INT_MAX, 4, INT_MAX},
        {7, INT_MAX, 6, INT_MAX, INT_MAX},
        {INT_MAX, 3, 9, 2, INT_MAX}
    };
    int start_vertex = 0; // 假设起点是 A

    dijkstra(graph, start_vertex);

    return 0;
}
