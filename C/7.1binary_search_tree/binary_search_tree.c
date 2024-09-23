// 二叉搜索树（二叉排序树）
// 性质：以中序遍历一颗二叉搜索树，将得到一个以关键字值递增排列的有序序列
// 二叉搜索树递归、迭代搜索、插入（迭代）、删除运算
#include<stdio.h>
#include<stdlib.h>
#define MAX 100
#define TRUE 1
#define FALSE 0
#define OverFlow 2 // 上溢
#define UnderFlow 3 // 下溢
#define NotPresent 4 // 元素不存在
#define Duplicate 5 // 元素重复
typedef int KeyType;
typedef int ElemType;
typedef struct entry { // 动态集元素类型Entry
    KeyType Key;
    ElemType Data;
}Entry;
typedef struct bstnode { // 二叉搜索树的结点类型BSTNode及二叉搜索树类型BSTree
    Entry *Element;
    struct bstnode *LChild, *RChild;
}BSTNode, *BSTree;

void CreateBST(BSTree *T, Entry *V); // 创建二叉树根结点
BSTree RecSearchBST(BSTree T, KeyType k); // 二叉搜索树的递归搜索
BSTree IterSearchBST(BSTree T, KeyType k); // 二叉搜索树的迭代搜索
int InsertBST(BSTree T, Entry *e); // 二叉搜索树的插入（迭代）
int DeleteBST(BSTNode *T, KeyType k); // 二叉搜索树的删除运算
void InOrder(BSTree T); // 中序遍历二叉树

int main()
{
    // 二叉搜索树的插入
    BSTree T; // 定义二叉树结构体T
    Entry A, B, C, D, E, F; // 定义六个动态元素类型
    A.Data = 1; B.Data = 2; C.Data = 3; D.Data = 4; E.Data = 5; F.Data = 6;
    A.Key = 28; B.Key = 21; C.Key = 25; D.Key = 36; E.Key = 33; F.Key = 43;
    CreateBST(&T, &A); // 创建并插入二叉搜索树

    InsertBST(T, &B);
    InsertBST(T, &C);
    InsertBST(T, &D);
    InsertBST(T, &E);
    InsertBST(T, &F);
    InOrder(T); // 中序遍历二叉树
    printf("\n");

    int ret = RecSearchBST(T, 33)->Element->Key; // 二叉搜索树递归搜索测试
    printf("key %d is founded\n", ret); 
    int ret2 = IterSearchBST(T, 21)->Element->Key; // 二叉搜索树迭代搜索测试
    printf("key %d is founded\n", ret2);
    RecSearchBST(T, 32);
    IterSearchBST(T, 22);

    DeleteBST(T, 36); // 删除二叉搜索树中值为36的元素
    InOrder(T);

    return 0;
}

void CreateBST(BSTree *T, Entry *V) // 创建二叉树根结点
{
    (*T) = (BSTNode *)malloc(sizeof(BSTNode));
    (*T)->Element = V;
    (*T)->LChild = NULL;
    (*T)->RChild = NULL;
}
BSTree RecSearchBST(BSTree T, KeyType k) // 二叉搜索树的递归搜索
{
    if (!T) { // 若二叉搜索树为空，则搜索失败，返回空指针
        printf("key %d not found\n", k);
        return NULL;
    } // 若二叉搜索树不为空，则将指定关键字值k与根结点元素的关键字值比较
    if (T->Element->Key == k) { // 若k大小等于该关键字值，则搜索成功，返回根节点地址
        return T;
    } else if (k < T->Element->Key) { // 若k小于该关键字值，则以同样的方法搜索左子树，而不必搜索右子树
        return RecSearchBST(T->LChild, k);
    } else { // 若k大于该关键字值，则以同样的方法搜索右子树，而不必搜索左子树
        return RecSearchBST(T->RChild, k);
    }
}

BSTree IterSearchBST(BSTree T, KeyType k) // 二叉搜索树的迭代搜索
{
    while (T) { // 若二叉搜索树不为空，则从根节点开始搜索，将待查关键字值k与根结点关键字值比较
        if (k < T->Element->Key) {
            T = T->LChild;
        } else if (k > T->Element->Key) {
            T = T->RChild;
        } else {
            return T;
        }
    }
    printf("key %d not found\n", k);
    return NULL; // 若二叉搜索树为空，则返回空指针，搜索失败
}
int InsertBST(BSTree T, Entry *e) // 二叉搜索树的插入（构造）
{
    BSTNode *p = T;
    BSTNode *q, *r;
    KeyType k = e->Key;
    while (p) { // （与二叉树的迭代搜索相同）找到指定元素e的插入位置
        q = p;
        if (k < p->Element->Key) {
            p = p->LChild;
        } else if (k > p->Element->Key) {
            p = p->RChild;
        } else { // 插入元素是相同元素
            printf("Duplicate\n");
            return FALSE;
        }
    }
    r = (BSTNode *)malloc(sizeof(BSTNode)); // 为新结点r分配内存空间
    r->Element = e;
    r->RChild = NULL;
    r->LChild = NULL;
    if (!T) { // 若二叉树为新树
        T = r; // 将r作为根结点插入到空树中
    } else if (k < q->Element->Key) { // 否则r将成为结点q的孩子，若新元素e的关键字k小于q的关键字
        q->LChild = r; // r为q的左孩子
    } else { // 若e的key大于q的key
        q->RChild = r; // r为q的右孩子
    }
    return TRUE;
}
int DeleteBST(BSTNode *T, KeyType k)
{
    BSTNode *c, *r, *s, *p, *q; // 声明五个结构体变量
    p = T;
    while (p && p->Element->Key != k) { // 从根结点开始查找关键字值等于k的结点p
        q = p;
        if (k < p->Element->Key) {
            p = p->LChild;
        } else {
            p = p->RChild;
        }
    }
    if (!p) { // 如果找不到被删除节点则返回FALSE
        printf("NotPresent\n");
        return FALSE;
    }
    if (p->LChild && p->RChild) { // 若p有两颗非空子树
        s = p->RChild;
        r = p;
        while (s->LChild) { // 搜索p的中序直接后继结点s
            r = s;
            s = s->LChild;
        }
        p->Element = s->Element; // 令p指示被删除的结点，q指示p的双亲
        p = s; q = r;
    }
    if (p->LChild) { // 令c取代p的那棵子树
        c = p->LChild; 
    } else {
        c = p->RChild;
    }
    if (p == T) { // 如果被删除的是根结点，则结点c成为新的根
        T == c;
    } else if (p == q->LChild) { // 否则结点c将取代结点p
        q->LChild = c;
    } else {
        q->RChild = c;
    }
    free(p); // 释放p所占用的空间
    return TRUE; // 删除成功，返回TRUE
}
void InOrder(BSTNode *T)
{
    if (!T) {
        return ;
    }
    InOrder(T->LChild);
    printf("%d ", T->Element->Key);
    InOrder(T->RChild);
}