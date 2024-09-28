// 拓扑排序
// AOV网（顶点活动网）,AOV网为有向无环图
// 以邻接表作为存储结构
// 使用栈和顶点入度数组InDegree[]，顶点序号数组topo[]

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
typedef int ElemType;
// 结点和图
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
// 栈（链栈）
typedef struct stack { // 堆栈结构体的定义
    int top; // top为当前栈顶位置下标
    int maxSize; // maxSize-1为堆栈的最大栈顶位置下标
    ElemType *element; // element为存储堆栈元素的一维数组首地址的指针
}Stack;

int Init(LGraph *lg, int nSize); // 初始化邻接表
void Destroy(LGraph *lg); // 邻接表撤销
int Exist(LGraph *lg, int u, int v); // 查询边
int Insert(LGraph *lg, int u, int v, ElemType w); // 插入边
int Remove(LGraph *lg, int u, int v); // 删除边
void Print(LGraph lg); // 仅打印权值

void Create_stack(Stack *S, int mSize); // 创建一个能容纳mSize个单元的空堆栈
void Destroy_stack(Stack *S); // 销毁一个已存在的堆栈，即释放堆栈占用的数组空间
int IsEmpty(Stack *S); // 判断堆栈是否为空，若为空返回TRUE，否则返回FALSE
int IsFull(Stack *S); // 判断堆栈是否已满，若是，则返回TRUE，否则返回FALSE
int Top(Stack *S, ElemType *x); // 获取栈顶元素，通过x返回。返回栈顶元素
int Push(Stack *S, ElemType x); // 在栈顶插入元素x（入栈）。若操作成功，则返回TRUE，否则返回FALSE
int Pop(Stack *S); // 删除栈顶元素（出栈）。若操作成功，则返回TRUE，否则返回FALSE
void Clear(Stack *S); // 清除堆栈中全部元素，但并不释放空间
void Print_stack(Stack S); // 打印栈中元素

void Degree(int *InDegree, LGraph *lg); // 求所有顶点入度，并存入数组InDegree[]
int TopoSort(int *topo, LGraph *lg); // 拓扑排序，参数为：顶点序号数组、图指针
void Inittopo(LGraph lg, int topo[]);

void test_Print_topo(int *topo, LGraph lg);
void test_Print_indegree(LGraph lg, int *InDegree);

int main()
{
    // 邻接表，数组下标从0开始
    LGraph lg; // 声明图的结构体变量lg
    int *topo;
    topo = (int *)malloc(lg.n*sizeof(int)); // 创建topo[]
    Init(&lg, 9); // 初始化邻接表
    Inittopo(lg, topo);
    Insert(&lg, 0, 7, Connect); Insert(&lg, 0, 2, Connect);
    Insert(&lg, 1, 4, Connect); Insert(&lg, 1, 2, Connect);
    Insert(&lg, 2, 3, Connect);
    Insert(&lg, 3, 6, Connect); Insert(&lg, 3, 5, Connect);
    Insert(&lg, 4, 5, Connect); Insert(&lg, 4, 3, Connect);
    Insert(&lg, 7, 8, Connect); Insert(&lg, 8, 6, Connect);
    
     Print(lg);
    // test_Print_topo(topo, lg);
    printf("\n");
    TopoSort(topo, &lg);


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

void Create_stack(Stack *S, int mSize)
{
    S->maxSize = mSize;
    S->element = (ElemType *)malloc(mSize*sizeof(ElemType));
    S->top = -1;
}

void Destroy_stack(Stack *S)
{
    S->maxSize = 0;
    free(S->element);
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
void Clear(Stack *S)
{
    S->top = -1;
}
void Print_stack(Stack S)
{
    while (S.top != -1) {
        printf("%d\n", S.element[S.top]);
        S.top--;
    }
}

void Degree(int *InDegree, LGraph *lg) // 计算顶点入度
{
    ENode *p; // 临时结构体指针p
    for (int i=0; i<lg->n; i++) {
        InDegree[i] = 0; // 初始化InDegree[]数组
    }
    for (int i=0; i<lg->n; i++) {
        for (p=lg->a[i]; p; p=p->nextArc) { // 检查以顶点i为尾的所有邻接点
            InDegree[p->adjVex]++;
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
        if (!InDegree[i]) {
            Push(&S, i);
        }
    }
    // // test 
    // printf("InDegree[]:");
    // test_Print_indegree(*lg, InDegree);
    // printf("\n");

    for (i=0; i<lg->n; i++) {
        if (IsEmpty(&S)) {
            return ERROR; // 若堆栈为空，说明有回路，返回ERROR
        } else {
            Top(&S, &j); // 返回栈顶元素，通过j返回
            Pop(&S); //  元素j出栈
            topo[i] = j; // 将j存入顶点序号数组
            printf("%d ", j);
            for (p=lg->a[j]; p; p=p->nextArc) { // 检查以顶点j为尾的所有邻接点
                k = p->adjVex; // 顶点j赋值给k
                InDegree[k]--; // 顶点k的入度减1
                if (!InDegree[k]) { // 若顶点k的入度为0，则进栈
                    Push(&S, k);
                }
            }
        }
    }
    // // test
    // printf("\n");
    // printf("InDegree[]:");
    // test_Print_indegree(*lg, InDegree);

}
void Inittopo(LGraph lg, int topo[])
{
    for (int i=0; i<lg.n; i++) { // 初始化topo数组
        topo[i] = 0;
    }
}
void test_Print_topo(int *topo, LGraph lg)
{
    for (int i=0; i<lg.n; i++) {
        printf("%d ", topo[i]);
    }
}
void test_Print_indegree(LGraph lg, int *InDegree)
{
    for (int i=0; i<lg.n; i++) {
        printf("%d ", InDegree[i]);
    }
}