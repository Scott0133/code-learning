// 拓扑排序 和 逆拓扑排序
    // 辅助数据结构：栈、出度数组OutDegree[],topo数组topo[]
    // 修复bug：使用指针移动，避免结点权值无法递增
#include<stdio.h>
#include<stdlib.h>
#define ERROR 0
#define OK 1
#define FALSE 0
#define TRUE 1
#define Overflow 2
#define Underflow 3
#define NotPresent 4
#define Duplicate 5
#define Connect 1
#define MAXSIZE 100
typedef int ElemType;
// 结点和图
typedef struct eNode {
    int adjVex; // 与任意顶点u[相邻接]的顶点
    ElemType w; // 边的权值
    struct eNode* nextArc; // 指向下一个边结点
}ENode;
typedef struct Graph {
    int n; // 图的当前顶点数
    int e; // 图的当前边数
    ENode **a; // 指向动态生成的二维数组
}LGraph;
// 栈（链栈）
typedef struct stack { // 堆栈结构体的定义
    int top; // top为当前栈顶位置下标
    int maxSize; // maxSize-1为堆栈的最大栈顶位置下标
    ElemType *element; // element为存储堆栈元素的一维数组首地址的指针
}Stack;

int Init(LGraph *lg, int nSize); // 初始化邻接表
int Exist(LGraph *lg, int u, int v); // 查询边
int Insert(LGraph *lg, int u, int v, ElemType w); // 插入边
int Remove(LGraph *lg, int u, int v); // 删除边
void Print(LGraph lg); // 打印邻接表链接情况

void Create_stack(Stack *S, int mSize); // 创建一个能容纳mSize个单元的空堆栈
int IsEmpty(Stack *S); // 判断堆栈是否为空，若为空返回TRUE，否则返回FALSE
int IsFull(Stack *S); // 判断堆栈是否已满，若是，则返回TRUE，否则返回FALSE
int Top(Stack *S, ElemType *x); // 获取栈顶元素，通过x返回。返回栈顶元素
int Push(Stack *S, ElemType x); // 在栈顶插入元素x（入栈）。若操作成功，则返回TRUE，否则返回FALSE
int Pop(Stack *S); // 删除栈顶元素（出栈）。若操作成功，则返回TRUE，否则返回FALSE

void Degree(int *InDegree, LGraph *lg); // 求所有顶点入度，并存入数组InDegree[]
int TopoSort(int *topo, LGraph *lg); // 拓扑排序，参数为：顶点序号数组、图指针
void Inittopo(LGraph lg, int topo[]);

int Reverse_TopoSort(int *topo, LGraph *lg, int outDegree[], int visited[]); // 逆拓扑排序
void calculateOutDegrees(LGraph *lg, int outDegree[]); // 初始化出度数组
int Reverse_TopoSort_copilot(int *topo, LGraph *lg, int outDegree[]);

int main()
{
    // 图9.15 AOV网
    LGraph lg; // 声明图的结构体变量lg
    int *topo; // 声明topo数组，存储拓扑排序顶点
    topo = (int *)malloc(lg.n*sizeof(int)); // 创建topo[]
    Init(&lg, 9); // 初始化邻接表
    Inittopo(lg, topo);
    Insert(&lg, 0, 7, Connect); Insert(&lg, 0, 2, Connect);
    Insert(&lg, 1, 4, Connect); Insert(&lg, 1, 2, Connect);
    Insert(&lg, 2, 3, Connect);
    Insert(&lg, 3, 6, Connect); Insert(&lg, 3, 5, Connect);
    Insert(&lg, 4, 5, Connect); Insert(&lg, 4, 3, Connect);
    Insert(&lg, 7, 8, Connect); Insert(&lg, 8, 6, Connect);

    // test
    int outDegree[MAXSIZE];
    calculateOutDegrees(&lg, outDegree); // 求各顶点出度并存入数组
    Reverse_TopoSort_copilot(topo, &lg, outDegree);

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
    p->w = w; // 为新结点写入权值（修改此处的connect）
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
        // if (p == NULL) continue; 
        if (p == NULL) {
            printf("vex%d->NULL", i); // 若当前链表为空，顶点指向NULL并跳过
            continue;
        }
        printf("vex%d->", i);
        while (p != NULL) { // p指针不为空时
            printf("%d->", p->adjVex);
            p = p->nextArc;
            if (p == NULL) {
                printf("NULL");
            }
        }
    }
}

void Create_stack(Stack *S, int mSize)
{
    S->maxSize = mSize;
    S->element = (ElemType *)malloc(mSize*sizeof(ElemType));
    S->top = -1;
}
int IsEmpty(Stack *S)
{
    return S->top == -1;
}
int IsFull(Stack *S)
{
    return S->top == S->maxSize - 1;
}
int Top(Stack *S, ElemType *x) // 获取栈顶元素，通过x返回。返回栈顶元素
{
    if (IsEmpty(S)) {
        return FALSE;
    }
    *x = S->element[S->top];
    return *x;
}
int Push(Stack *S, ElemType x)
{
    if (IsFull(S)) {
        return FALSE;
    }
    S->top++;
    S->element[S->top] = x;
    return TRUE;
}
int Pop(Stack *S)
{
    if (IsEmpty(S)) {
        return FALSE;
    }
    S->top--;
    return TRUE;
}
void Degree(int *InDegree, LGraph *lg) // 计算顶点入度
{
    ENode *p; // 临时结构体指针p
    for (int i=0; i<lg->n; i++) {
        InDegree[i] = 0; // 初始化InDegree[]数组
    }
    for (int i=0; i<lg->n; i++) { // 计算入度
        for (p=lg->a[i]; p; p=p->nextArc) { // 检查以顶点i为尾的所有邻接点
            InDegree[p->adjVex]++; // !!
        }
    }
}
int TopoSort(int *topo, LGraph *lg)
{
    int i,j,k; // 创建临时变量i、j、k
    ENode *p; // 创建临时结构体指针p
    Stack S; // 创建栈S
    int *InDegree = (int *)malloc(lg->n*sizeof(int)); // 为InDegree数组创建空间
    
    Create_stack(&S, lg->n); // 创建大小为n的栈
    Degree(InDegree, lg); // 计算顶点的入度
    for (i=0; i<lg->n; i++) {
        if (!InDegree[i]) { // 若顶点的入度为0，则入栈
            Push(&S, i);
        }
    }
    for (i=0; i<lg->n; i++) {
        if (IsEmpty(&S)) {
            return ERROR; // 若堆栈为空，说明有回路，返回ERROR
        } else {
            Top(&S, &j); // 返回栈顶元素，通过j返回
            Pop(&S); //  元素j出栈
            topo[i] = j; // 将j存入顶点序号数组
            printf("%d ", j);
            for (p=lg->a[j]; p; p=p->nextArc) { // 检查以顶点j为尾的所有邻接点
                k = p->adjVex; // k指向p的邻接点
                InDegree[k]--; // 顶点k的入度减1
                if (!InDegree[k]) { // 若顶点k的入度为0，则进栈
                    Push(&S, k);
                }
            }
        }
    }
}
void Inittopo(LGraph lg, int topo[])
{
    for (int i=0; i<lg.n; i++) { // 初始化topo数组
        topo[i] = 0;
    }
}
void calculateOutDegrees(LGraph *lg, int outDegree[])
{
    for (int i = 0; i < lg->n; i++) {
        ENode *current = lg->a[i];  // 使用current指针移动，避免结点权值无法递增
        outDegree[i] = 0; // 初始化出度为0
        while (current != NULL) {
            outDegree[i]++;
            current = current->nextArc;
        }
    }
}
int Reverse_TopoSort(int *topo, LGraph *lg, int outDegree[], int visited[])
{
    int i,j,k; // 创建临时变量i、j、k

    ENode *p; // 创建临时结构体指针p
    Stack S; // 创建栈S
    int *InDegree = (int *)malloc(lg->n*sizeof(int)); // 为InDegree数组创建空间
    
    Create_stack(&S, lg->n); // 创建大小为n的栈
    // Degree(InDegree, lg); // 计算顶点的入度 （出度已计算）
    for (i=0; i<lg->n; i++) {
        if (!outDegree[i]) { // 若顶点的出度为0，则入栈
            Push(&S, i);
            visited[i] = TRUE;
        }
    }
    for (i=0; i<lg->n; i++) {
        if (IsEmpty(&S)) {
            return ERROR; // 若堆栈为空，说明有回路，返回ERROR
        } else {
            Top(&S, &j); // 返回栈顶元素，通过j返回
            Pop(&S); //  元素j出栈
            topo[i] = j; // 将j存入顶点序号数组
            printf("%d ", j);
            for (int num=0; num<lg->n; num++) { // 检查以顶点j为尾的所有邻接点（修改）
            ENode *current = lg->a[num];  // 使用current指针移动，避免结点权值无法递增
                if (outDegree[num] == 0 && visited[num] == FALSE) { // 若顶点num的出度为0，则进栈
                    Push(&S, num);
                    visited[num] = TRUE;
                }
                if (current == NULL) {
                    outDegree[num]--;
                }
            }
        }
    }
}
int Reverse_TopoSort_copilot(int *topo, LGraph *lg, int outDegree[]) {
    int i, j, k; // 临时变量i、j、k
    ENode *p; // 临时结构体指针p
    Stack S; // 栈S
    Create_stack(&S, lg->n); // 创建大小为n的栈
    // 找到所有出度为0的顶点并入栈
    for (i = 0; i < lg->n; i++) {
        if (outDegree[i] == 0) {
            Push(&S, i);
        }
    }
    for (i = 0; i < lg->n; i++) {
        if (IsEmpty(&S)) {
            return ERROR; // 如果栈为空，说明图有回路
        } else {
            Top(&S, &j); // 返回栈顶元素，通过j返回
            Pop(&S); // 元素j出栈
            topo[i] = j; // 将j存入拓扑排序数组
            printf("%d ", j);

            // 检查所有顶点，将邻接顶点为j的顶点出度减1
            for (k = 0; k < lg->n; k++) {
                for (p = lg->a[k]; p; p = p->nextArc) {
                    if (p->adjVex == j) {
                        outDegree[k]--; // 顶点k的出度减1
                        if (outDegree[k] == 0) {
                            Push(&S, k); // 如果顶点k的出度为0，则进栈
                        }
                    }
                }
            }
        }
    }

    return TRUE;
}

