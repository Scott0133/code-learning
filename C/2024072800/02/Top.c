//对有向无环图(Directed Acyclic Graph, DAG)进行拓扑排序
//拓扑排序(Topological Order)
//拓扑排序实现：栈、邻接表
#define MAXSIZE 100

#include<stdio.h>
int Top()
{
    int indegree[MAXSIZE]; // 记录每个结点入度
    int print[MAXSIZE]; // 记录拓扑序列
}