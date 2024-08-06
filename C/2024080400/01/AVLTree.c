// 平衡二叉树(Balanced Binary Tree)，又称AVL树，首先是二叉排序树
// 树上的任一结点的左右子树高度差不超过1
// 结点平衡因子=左子树高-右子树高
// 最小不平衡子树 LL/RR/LR/RL，失衡二叉树调整原则：1、降低高度 2、保持二叉排序树性质

// 平衡二叉树结点
typedef struct AVLNode{
    int key; // 数据域
    int balanced; // 平衡因子
    struct AVLNode *lchild, *rchild;
}AVLNode, *AVLTree;