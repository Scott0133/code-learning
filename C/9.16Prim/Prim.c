// Prim算法实现最小代价生成树
// 引入以下辅助数据结构：
    // 一维数组closeVex[]，存放与v距离最近的顶点编号u
    // 一维数组lowWeight[]，存放closeVex的权值
    // 一维数组isMark[]，用于标记顶点是否在树中，isMark == 0则未加入生成树
// 邻接表的实现
// 使用头插法
// 带权的边结点

#include<stdio.h>
#include<stdlib.h>
#define ERROR 0
#define OK 1
#define Overflow 2
#define Underflow 3
#define NotPresent 4
#define Duplicate 5
#define INFTY 32767 // 定义权值的极大值
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
void Print(LGraph lg); // 仅打印权值

int Prim(int k, int closeVex[], int lowWeight[], LGraph g);

int main()
{
    // 测试图9.10 (c)带权有向图G6的邻接表
    // LGraph lg;
    // Init(&lg, 4);
    // Insert(&lg, 1, 2, 3);
    // Insert(&lg, 1, 0, 1);
    // Insert(&lg, 2, 3, 9);
    // Insert(&lg, 3, 0, 4);
    // Remove(&lg, 3, 0);
    // Print(lg);

    // 图9.17 (a)带权连通图G(无向图)
    LGraph lg;
    int closeVex[10]; // 声明closeVex[]
    int lowWeight[10]; // 声明lowWeight[]
    Init(&lg, 6);
    Insert(&lg, 0, 1, 10); Insert(&lg, 1, 0, 10);
    Insert(&lg, 0, 2, 7); Insert(&lg, 2, 0, 7);
    Insert(&lg, 0, 5, 4); Insert(&lg, 5, 0, 4);
    Insert(&lg, 2, 5, 6); Insert(&lg, 5, 2, 6);
    Insert(&lg, 2, 3, 8); Insert(&lg, 3, 2, 8);
    Insert(&lg, 1, 4, 2); Insert(&lg, 4, 1, 2);
    Insert(&lg, 5, 4, 7); Insert(&lg, 4, 5, 7);
    Insert(&lg, 5, 3, 5); Insert(&lg, 3, 5, 5);
    Insert(&lg, 4, 3, 9); Insert(&lg, 3, 4, 9);

    Print(lg);
    printf("\n");
    Prim(0, closeVex, lowWeight, lg); // 从顶点0的构造顺序为0->5->3->2->4->1
    
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
int Prim(int k, int closeVex[], int lowWeight[], LGraph lg)
{
    ENode *p; // 定义临时结构体指针p
    int i, j;
    int min; // min变量用于在每轮循环中跟踪生成树外部顶点中，具有最小lowWeight值的顶点。通过每次迭代更新min，算法确保在下一步选择到权值最小的边，将新的顶点加入生成树。
    int *isMark = (int *)malloc(sizeof(int)*lg.n); // 动态生成数组isMark
    if (k<0 || k>lg.n-1) {
        return ERROR;
    }
    for (i=0; i<lg.n; i++) { // 初始化三个辅助数组
        closeVex[i] = -1;           // closeVex[]存放与v距离最近的顶点编号
        lowWeight[i] = INFTY;       // lowWeight[]存放边(closeVex[v],v)的权值
        isMark[i] = 0;              // 标记顶点v是否在生成树中
    }
    lowWeight[k] = 0; closeVex[k] = k; isMark[k] = 1; // 源点加入生成树
    for (i=1; i<lg.n; i++) { // 选择其余n-1条边加入生成树
        for (p = lg.a[k]; p; p=p->nextArc) {
            j = p->adjVex; // j为p的邻接结点
            if ((!isMark[j]) && (lowWeight[j]>p->w)) { // 如果j不在生成树中，且边(k,j)的权值比lowWeight[j]小，更新生成树外顶点的lowWeight值
                lowWeight[j] = p->w;
                // printf("lowWeight[j] %d\n", p->w);
                closeVex[j] = k;
                // printf("closeVex[j] %d\n", k);
            }
        }
        min = INFTY; // min初始化为INFTY，为了确保在第一次比较时，任何实际的边权值都可以替代它
        for (j=0; j<lg.n; j++) { // 找生成树外顶点中，具有最小lowWeight值的顶点k
            if ((!isMark[j]) && (lowWeight[j]<min)) {
                min = lowWeight[j]; // 将权值最小的边设置为min
                k = j;
            }
        }
        isMark[k] = 1; // 将顶点k加到生成树上
        // printf("min = %d\n", min); 
    } // 注：以下仅为最终输出结果
    for (i=0; i<lg.n; i++) {
        printf("%d ", closeVex[i]);
        printf("%d ", i);
        printf("%d ",lowWeight[i]);
        printf("\n");
    }
    return OK;
}