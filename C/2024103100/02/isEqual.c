// 判断两棵二叉树是否相等

#define TRUE 0
#define FALSE 1

typedef struct BstNode {            //定义二叉树结构
    int data;
    struct BstNode *Lchild;
    struct BstNode *Rchild;
}BstNode;
int isEaqul(BstNode *t1, BstNode *t2) {
    if (!t1 && !t2) {
        return TRUE; // 如果t1和t2都不存在，相等
    }
    if (!t1 || !t2) {
        return FALSE; // 如果t1和t2有一个不存在，不相等
    } else {
        if (t1->data == t2->data) {
            // return isEaqul(t1->Lchild, t2->Lchild) && isEaqul(t1->Rchild, t2->Rchild);
            if (isEaqul(t1->Lchild, t2->Lchild) && isEaqul(t1->Rchild, t2->Rchild)) {  // 递归判断t1的左端和t2的左端，t1的右端和t2的右端
                return TRUE;
            } else {
                return FALSE;
            }
        }
    }
}