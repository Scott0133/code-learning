// 图的深度优先遍历（DFS）
// 采用邻接表存储结构
#include<stdio.h>
#include<stdlib.h>
#define ERROR 0
#define OK 1
#define Overflow 2
#define Underflow 3
#define NotPresent 4
#define Duplicate 5
#define Connect 1
typedef int ElemType;
typedef struct eNode {
    int adjVex; // 与任意顶点u相邻接的顶点
    ElemType w; // 边的权值
    struct eNode* nextArc; // 指向下一个边结点
}ENode;
typedef struct Graph {
    int n; // 图的当前顶点数
    int e; // 图的当前边数
    ENode **a; // 指向一维指针数组
}LGraph;

int Init(LGraph *lg, int nSize); // 初始化邻接表
void Destroy(LGraph *lg); // 邻接表撤销
int Exist(LGraph *lg, int u, int v); // 查询边
int Insert(LGraph *lg, int u, int v, ElemType w); // 插入边
int Remove(LGraph *lg, int u, int v); // 删除边
void Print(LGraph lg); // 打印链表链接情况
void DFS(int v, int visited[], LGraph lg); // 深度优先遍历
void DFSGraph(LGraph lg, int v); // 深度优先遍历整个图

int main()
{
    // 图9.13 (a)有向图G
    LGraph lg;
    Init(&lg, 6);

    Insert(&lg, 0, 1, Connect); // 参数为（图，顶点u，顶点v，权值）
    Insert(&lg, 1, 3, Connect);
    Insert(&lg, 3, 2, Connect);
    Insert(&lg, 2, 0, Connect);
    Insert(&lg, 1, 2, Connect);
    Insert(&lg, 3, 0, Connect);
    Insert(&lg, 4, 2, Connect);
    Insert(&lg, 4, 0, Connect);
    Insert(&lg, 5, 3, Connect);
    Insert(&lg, 5, 1, Connect);

    Print(lg); // 顶点链接情况
    printf("\n");
    DFSGraph(lg, 2); // 从顶点2开始深度优先遍历图
    printf("\n");
    DFSGraph(lg, 5); // 从顶点4开始深度优先遍历图
    // printf("%d %d %d %d", lg.a[1]->w, lg.a[1]->nextArc->w, lg.a[2]->w, lg.a[3]->w);

    return 0;
}

int Init(LGraph *lg, int nSize)
{
    lg->n = nSize; // 初始化图顶点个数
    lg->e = 0; // 初始化图的边数
    lg->a = (ENode **)malloc(nSize*sizeof(ENode *)); //为ENode结构体数组指针分配空间，大小为顶点个数*(ENode*)
    if (!lg->a) { // 动态分配失败
        return ERROR;
    } else {
        for (int i=0; i<lg->n; i++) {
            lg->a[i] = NULL; // 将结构体指针数组置空
        }
    }
    return OK;
}
void Destroy(LGraph *lg)
{
    ENode *p, *q; // 声明临时结构体指针p，q
    for (int i=0; i<lg->n; i++) { // 释放所有非空结点的内存
        p = lg->a[i]; // 指针p指向顶点i的单链表的第一个结点
        q = p; // 将q指向p
        while (p) { // 若p不为空
            p = p->nextArc; // p指向下一结点
            free(q); // 释放q结点
            q = p; // q指向p
        }
    }
    free(lg->a); // 释放一维结构体指针数组a的存储空间
}
int Exist(LGraph *lg, int u, int v)
{
    ENode *p; // 声明临时结构体指针p
    if (u<0 || v<0 || u>lg->n-1 || v>lg->n-1 || u==v) { // 参数u、v无效或边不存在
        return ERROR;
    }
    p = lg->a[u]; // p指向顶点u单链表的第一个边结点
    while (p && p->adjVex != v) { // 指针p指向的结点存在与p指向的边结点值不为v
        p = p->nextArc;
    }
    if (!p) { // 若p指向的结点不存在
        return ERROR; // 未找到边
    }
    return OK; // 找到边
}
int Insert(LGraph *lg, int u, int v, ElemType w)
{
    ENode *p; // 创建临时结构体指针p
    if (u<0 || v<0 || u>lg->n-1 || v>lg->n-1 || u==v) { // 参数u、v无效或边不存在
        return ERROR;
    }
    if (Exist(lg, u, v)) { // 如果插入边已存在
        return Duplicate;
    }
    p = (ENode *)malloc(sizeof(ENode)); // 为新的边结点分配存储空间
    p->w = w; // 为新结点写入权值
    // 头插法
    p->adjVex = v;
    p->nextArc = lg->a[u]; // 将新的边结点插入单链表的最前端
    lg->a[u] = p;
    
    lg->e++; // 边的数量加1
    return OK;
}
int Remove(LGraph *lg, int u, int v)
{
    ENode *p, *q; // 声明临时结构体指针p、q
    if (u<0 || v<0 || u>lg->n-1 || v>lg->n-1 || u==v) { // 参数u、v无效或边不存在
        return ERROR;
    }
    p = lg->a[u], q = NULL; // p指向顶点u单链表的第一个结点，q为空
    while (p && p->adjVex != v) { // 指针p指向的结点存在与p指向的边结点值不为v
        q = p; // q指向p
        p = p->nextArc; // p指向下一个结点
    }
    if (!p) { // p为空，未找到边结点
        return NotPresent;
    }
    if (q) { // 若q存在
        q->nextArc = p->nextArc; // 从单链表删除此边
    } else {
        lg->a[u] = p->nextArc; // 确保删除第一个结点时链表头指针正确更新!
    }
    free(p);
    lg->e--; // 边的数量减1
    return OK;
}
void Print(LGraph lg)
{
    ENode *p; // 声明临时变量p
    // p = lg.a[0];
    for (int i=0; i<lg.n; i++) {
        p = lg.a[i]; // p指向lg.a[i]的地址
        printf("\n");
        if (p == NULL) continue; // 若当前链表为空，则跳过
        printf("vex%d->", i);
        while (p != NULL) { // p指针不为空时
            printf("%d->", p->adjVex);
            p = p->nextArc;
            if (p == NULL) {
                printf("(NULL)");
            }
        }
    }
}
void DFS(int v, int visited[], LGraph lg) // 从顶点v开始，深度优先遍历图lg
{
    ENode *w; // 创建临时结构体指针w
    printf("%d ", v); // 访问顶点v
    visited[v] = 1; // 将v设置为已访问
    for (w=lg.a[v]; w; w=w->nextArc) { // 遍历v的邻接点
        if (!visited[w->adjVex]) { // 若w为被访问，则递归调用DFS
            DFS(w->adjVex, visited, lg);
        }
    }
}
void DFSGraph(LGraph lg, int v)
{
    int *visited = (int *)malloc(lg.n*sizeof(int)); // 为visited数组创建空间
    for (int i=0; i<lg.n; i++) {
        visited[i] = 0; // 将所有顶点标记为未访问
    }
    DFS(v, visited, lg); // 先访问一次指定顶点
    for (int j=0; j<lg.n; j++) { // 逐一检查每个顶点，若未被访问，则调用DFS
        if (!visited[j]) {
            DFS(j, visited, lg);
        }
    }
    free(visited);
}