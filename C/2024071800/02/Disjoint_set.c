//并查集
//使用双亲表示法创建
#include<stdio.h>
#define size 13
#define MAX_TREE_SIZE 100
typedef char ElemType;

typedef struct {                        //树的结点定义
    ElemType data;
    int parent;
}ParentNode;

typedef struct {                        //树的类型定义
    ParentNode S[MAX_TREE_SIZE];
    int n;
}ParentTree;

//int UFsets[size];                           //集合元素数组

void Initial(ParentTree *T);                      //初始化并查集
int Find(ParentTree T, int x);                   //“查”操作，找到x所属集合（返回x的根结点）
void Union(ParentTree *T, int root1, int root2);  //“并”操作，将两个集合为一个
int Find_2(ParentTree T, int x);                 //查操作的路径优化
void Union_2(ParentTree *T, int root1, int root2); //并操作的优化，小树合并到大树，该方法构造的树高不超过[log2n]+1，log2n向下取整


int main()
{
    ParentTree T;
    //手动创建集合
    T.S[0].data = 'A';    T.S[0].parent = -6;
    T.S[1].data = 'B';    T.S[1].parent = 0;
    T.S[2].data = 'C';    T.S[2].parent = -2;
    T.S[3].data = 'D';    T.S[3].parent = -5;
    T.S[4].data = 'E';    T.S[4].parent = 1;
    T.S[5].data = 'F';    T.S[5].parent = 1;
    T.S[6].data = 'F';    T.S[6].parent = 2;
    T.S[7].data = 'G';    T.S[7].parent = 3;
    T.S[8].data = 'H';    T.S[8].parent = 3;
    T.S[9].data = 'I';    T.S[9].parent = 3;
    T.S[10].data = 'J';   T.S[10].parent = 4;
    T.S[11].data = 'K';   T.S[11].parent = 4;
    T.S[12].data = 'L';   T.S[12].parent = 7;

    //Initial(&T);
    int ret = Find(T, 10);
    int ret_2 = Find_2(T, 10);
    printf("%c\n", T.S[ret].data);
    printf("%c\n", T.S[ret_2].data);
    //Union(&T, 0, 2);
    Union_2(&T, 0, 2);

    return 0;
}

void Initial(ParentTree *T)
{
    for (int i=0; i<size; i++)
    {
        T->S[i].parent = -1;
    }
}
int Find(ParentTree T, int x)
{
    while (T.S[x].parent >= 0)
    {
        x = T.S[x].parent;
    }
    return x;
}
int Find_2(ParentTree T, int x)
{
    int root = x;
    while (T.S[root].parent >= 0)
    {
        root = T.S[root].parent;
    }
    while (x != root)
    {
        int t = T.S[x].parent;
        T.S[x].parent = root;
        x = t;
    }
    return root;                                    //返回根节点编号
}
void Union(ParentTree *T, int root1, int root2)
{
    if (root1 == root2)
        return;
    T->S[root2].parent = root1;
}
void Union_2(ParentTree *T, int root1, int root2)       //并操作的优化，小树合并到大树
{
    if (root1 == root2)
        return;
    if (T->S[root2].parent > T->S[root1].parent)
    {
        T->S[root1].parent += T->S[root2].parent;
        T->S[root2].parent = root1;
    }
    else
    {
        T->S[root2].parent += T->S[root1].parent;
        T->S[root1].parent = root2;
    }
}