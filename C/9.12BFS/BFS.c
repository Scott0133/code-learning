// 图的（宽度）广度优先遍历(DFS)
// 采用邻接表存储结构（无向图）
// 循环队列（模运算实现）

#include<stdio.h>
#include<stdlib.h>
#define FALSE 0
#define TRUE 1
#define ERROR 0
#define OK 1
#define OverFlow 2 // 上溢
#define UnderFlow 3 // 下溢
#define NotPresent 4 // 元素不存在
#define Duplicate 5 // 元素重复
#define Connect 1
typedef int ElemType;
typedef struct queue {
    int front;
    int rear;
    int maxSize; // 队列实际容量为maxSize-1
    ElemType *element;
} Queue;
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

void Create(Queue *Q, int mSize); // 创建一个能容纳mSize个单元的空队列
void Destroy(Queue *Q); // 销毁一个已存在的队列，即释放队列占用的数组空间
int IsEmpty(Queue *Q); // 判断队列是否为空，若是则返回TRUE，否则返回FALSE
int IsFull(Queue *Q); // 判断队列是否已满，若是则返回TRUE，否则返回FALSE
int Front(Queue *Q, ElemType *x); // 获取队头元素，通过x返回。
int EnQueue(Queue *Q, ElemType x); // 在队列Q的队尾插入元素x（入队）。操作成功返回TRUE，否则返回FALSE
int DeQueue(Queue *Q); // 从队列Q中删除队头元素（出队）。操作成功返回TRUE，否则返回FALSE
void Clear(Queue *Q); // 清除队列中全部元素，使队列恢复初始状态（Q->FRONT = Q->REAR = 0），但不释放空间
void Print(Queue Q); // 打印队列元素

int Init(LGraph *lg, int nSize); // 初始化邻接表
void Destroy_lg(LGraph *lg); // 邻接表撤销
int Exist(LGraph *lg, int u, int v); // 查询边
int Insert(LGraph *lg, int u, int v, ElemType w); // 插入边
int Remove(LGraph *lg, int u, int v); // 删除边
void Print_lg(LGraph lg); // 打印链表链接情况

// 例图↓↓
int Insert_lg_2(LGraph *lg, int u, int v, ElemType w); // 插入例图边
int Init_lg_2(LGraph *lg, int nSize); // 初始化例图
void Print_lg_2(LGraph lg); // 打印例图
void BFSGraph_lg_2(LGraph lg, int v); // 例图

void BFS(int v, int visited[], LGraph lg); // 广度优先遍历
void BFSGraph(LGraph lg, int v); // 广度优先遍历所有图

int main()
{
    // 图9.14 无向图G
    LGraph lg;
    Init(&lg, 8);
    Insert(&lg, 0, 4, Connect); Insert(&lg, 0, 2, Connect); Insert(&lg, 0, 1, Connect);
    Insert(&lg, 1, 5, Connect); Insert(&lg, 1, 3, Connect); Insert(&lg, 1, 2, Connect); Insert(&lg, 1, 0, Connect);
    Insert(&lg, 2, 6, Connect); Insert(&lg, 2, 5, Connect); Insert(&lg, 2, 4, Connect); Insert(&lg, 2, 1, Connect); Insert(&lg, 2, 0, Connect);
    Insert(&lg, 3, 5, Connect); Insert(&lg, 3, 1, Connect);
    Insert(&lg, 4, 7, Connect); Insert(&lg, 4, 6, Connect); Insert(&lg, 4, 2, Connect); Insert(&lg, 4, 0, Connect);
    Insert(&lg, 5, 6, Connect); Insert(&lg, 5, 3, Connect); Insert(&lg, 5, 2, Connect); Insert(&lg, 5, 1, Connect);
    Insert(&lg, 6, 7, Connect); Insert(&lg, 6, 5, Connect); Insert(&lg, 6, 4, Connect); Insert(&lg, 6, 2, Connect);
    Insert(&lg, 7, 6, Connect); Insert(&lg, 7, 4, Connect);
    // 例图（数组下标为1开始）
    LGraph lg_2; // 创建例图
    Init_lg_2(&lg_2, 8);
    Insert_lg_2(&lg_2, 1, 5, Connect); Insert_lg_2(&lg_2, 1, 2, Connect);
    Insert_lg_2(&lg_2, 2, 6, Connect); Insert_lg_2(&lg_2, 2, 1, Connect);
    Insert_lg_2(&lg_2, 3, 7, Connect); Insert_lg_2(&lg_2, 3, 6, Connect); Insert_lg_2(&lg_2, 3, 4, Connect);
    Insert_lg_2(&lg_2, 4, 8, Connect); Insert_lg_2(&lg_2, 4, 7, Connect); Insert_lg_2(&lg_2, 4, 3, Connect);
    Insert_lg_2(&lg_2, 5, 1, Connect);
    Insert_lg_2(&lg_2, 6, 7, Connect); Insert_lg_2(&lg_2, 6, 3, Connect); Insert_lg_2(&lg_2, 6, 2, Connect);
    Insert_lg_2(&lg_2, 7, 8, Connect); Insert_lg_2(&lg_2, 7, 6, Connect); Insert_lg_2(&lg_2, 7, 4, Connect); Insert_lg_2(&lg_2, 7, 3, Connect);
    Insert_lg_2(&lg_2, 8, 7, Connect); Insert_lg_2(&lg_2, 8, 4, Connect);
    
    

    // G
    // Print_lg(lg);
    // printf("\n");
    // BFSGraph(lg, 1);
    // 例图
    printf("\n");
    Print_lg_2(lg_2);
    printf("\n");
    BFSGraph_lg_2(lg_2, 2);
    



    return 0;
}

void Create(Queue *Q, int mSize)
{
    Q->maxSize = mSize;
    Q->element = (ElemType *)malloc(mSize*sizeof(ElemType));
    Q->front = Q->rear = 0;
}
void Destroy(Queue *Q)
{
    Q->maxSize = 0;
    free(Q->element);
    Q->front = Q->rear = -1;
}
int IsEmpty(Queue *Q)
{
    return Q->front == Q->rear; // front和rear相等为空
}
int IsFull(Queue *Q)
{
    return (Q->rear+1) % Q->maxSize == Q->front; // rear在front的后面，则循环队列已满
}
int Front(Queue *Q, ElemType *x)
{
    if (IsEmpty(Q)) {
        return FALSE;
    }
    *x = Q->element[(Q->front+1) % Q->maxSize];
    return TRUE;
}
int EnQueue(Queue *Q, ElemType x)
{
    if (IsFull(Q)) {
        return FALSE;
    }
    Q->rear = (Q->rear+1) % Q->maxSize; // 入队front指针移动
    Q->element[Q->rear] = x;
    return TRUE;
}
int DeQueue(Queue *Q)
{
    if (IsEmpty(Q)) {
        return FALSE;
    }
    Q->front = (Q->front+1) % Q->maxSize; // 出队rear指针移动
    return TRUE;
}
void Clear(Queue *Q)
{
    Q->front = Q->rear = 0;
}
void Print(Queue Q)
{
    Q.front++; // front指向元素置空
    while (Q.rear != Q.front) {
        printf("%d ", Q.element[Q.front]); // 从队首到队尾-1依次列出元素
        Q.front = (Q.front+1) % Q.maxSize;
        if (Q.front == Q.rear) {
            printf("\nThe rear element is %d", Q.element[Q.rear]); // 队尾元素
        }
    }
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
void Destroy_lg(LGraph *lg)
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
void Print_lg(LGraph lg)
{
    ENode *p; // 声明临时变量p
    // p = lg.a[0];
    for (int i=0; i<lg.n; i++) {
        p = lg.a[i]; // p指向lg.a[i]的地址
        printf("\n");
        if (p == NULL) continue; // 若当前链表为空，则跳过
        printf("vex%d:->", i);
        while (p != NULL) { // p指针不为空时
            printf("%d->", p->adjVex);
            p = p->nextArc;
            if (p == NULL) {
                printf("(NULL)");
            }
        }
    }
}
void BFS(int v, int visited[], LGraph lg)
{
    ENode *w; // 创建临时结构体指针w
    Queue q;
    Create(&q, lg.n); // 初始化队列
    printf("%d ", v); // 访问顶点v
    visited[v] = 1; // 设置顶点已访问
    EnQueue(&q, v); // 将顶点v入队
    while (!IsEmpty(&q)) { // 当队列非空时
        Front(&q, &v); // 获取顶点v，通过v返回
        DeQueue(&q); // 队首顶点出队
        for (w=lg.a[v]; w; w=w->nextArc) { // 遍历v的所有邻接点
            if (!visited[w->adjVex]) { // 如果未访问顶点w，则访问w并将其入队
                printf("%d ", w->adjVex);
                visited[w->adjVex] = 1; // 设置w已访问
                EnQueue(&q, w->adjVex); // 顶点w入队
            }
        }
    }
}
void BFSGraph(LGraph lg, int v)
{
    int *visited = (int *)malloc(lg.n*sizeof(int)); // 为visited数组创建空间
    for (int i=0; i<lg.n; i++) {
        visited[i] = 0; // 初始化visited数组
    }
    BFS(v, visited, lg);
    for (int j=0; j<lg.n; j++) { // 检查每一个顶点，若未访问则广度优先遍历
        if (!visited[j]) {
            BFS(v, visited, lg);
        }
    }
}
int Insert_lg_2(LGraph *lg, int u, int v, ElemType w)
{
    ENode *p; // 创建临时结构体指针p
    // if (u<0 || v<0 || u>lg->n-1 || v>lg->n-1 || u==v) { // 参数u、v无效或边不存在
    //     return ERROR;
    // }
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
int Init_lg_2(LGraph *lg, int nSize)
{
    lg->n = nSize; // 初始化图顶点个数
    lg->e = 0; // 初始化图的边数
    lg->a = (ENode **)malloc(nSize*sizeof(ENode *)); //为ENode结构体数组指针分配空间，大小为顶点个数*(ENode*)
    if (!lg->a) { // 动态分配失败
        return ERROR;
    } else {
        for (int i=1; i<lg->n+1; i++) {
            lg->a[i] = NULL; // 将结构体指针数组置空
        }
    }
    return OK;
}
void Print_lg_2(LGraph lg)
{
    ENode *p; // 声明临时变量p
    // p = lg.a[0];
    for (int i=1; i<lg.n+1; i++) {
        p = lg.a[i]; // p指向lg.a[i]的地址
        printf("\n");
        if (p == NULL) continue; // 若当前链表为空，则跳过
        printf("vex%d:->", i);
        while (p != NULL) { // p指针不为空时
            printf("%d->", p->adjVex);
            p = p->nextArc;
            if (p == NULL) {
                printf("(NULL)");
            }
        }
    }
}
void BFSGraph_lg_2(LGraph lg, int v)
{
    int *visited = (int *)malloc(lg.n*sizeof(int)); // 为visited数组创建空间
    for (int i=1; i<lg.n+1; i++) {
        visited[i] = 0; // 初始化visited数组
    }
    BFS(v, visited, lg);
    for (int j=1; j<lg.n+1; j++) { // 检查每一个顶点，若未访问则广度优先遍历
        if (!visited[j]) {
            BFS(v, visited, lg);
        }
    }
}