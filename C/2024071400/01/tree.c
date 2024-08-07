/*
树的基本定义和术语
1. 空树 -- 结点为0的树   注：除了根节点外，任何一个结点都只有一个前驱
2. 树是递归定义的数据结构
3. 结点、树的属性描述
        属性：
        结点的层次（深度）————从上往下数
        结点的高度————从下往上数
        树的高度（深度）————总共多少层
        结点的度————有几个分支
        树的度————各结点度的最大值
4. 有序树和无序树   注：有序树不可互换
5. 森林是m（m>=0）棵互不相交的树的集合

树的常考性质
1. 结点数 = 总度数 + 1
2. 树的度————各结点度的最大值 m叉树————每个结点最多m个孩子的树
3. 度为m的树第i层至多有m^(i-1)个结点（i>=1）
4. 高度为h的m叉树至多有m^h-1/m-1个结点
5. 高度为h的m叉树至少有h个结点；高度为h、度为m的树至少有h+m-1个结点
6. 具有n个结点的m叉树的最小高度为logm(n(m-1)+1) （注:向上取整）

二叉树的定义和基本术语
1. 二叉树的五种状态
2. 满二叉树，按层序从1开始编号，结点i的左孩子为2i，右孩子为2i+1；结点i的父节点为[i/2]（若存在）
3. 完全二叉树：仅当结点编号1~n（中间无空隙）对应满二叉树的树
4. 二叉排序树
5. 平衡二叉树：树上任一结点的左子树和右子树的深度之差不超过1

二叉树常考性质
1. 设非空二叉树中度为0，度为1，度为2的结点个数分别为n0、n1和n2，则n0 = n2 + 1
2. 二叉树第i层至多有2^(i-1)个结点（i>=1）;m叉树第i层至多有2^(m-1)个结点（i>=1）
3. 高度为h的2叉树至多有2^h-1个结点（满二叉树）
完全二叉树常考性质
1. 完全二叉树的高度h为log2(n+1)（注：向上取整）或log2n+1(注：log2n向下取整)
2. 完全二叉树可由结点总数n推出n0、n1和n2

二叉树顺序存储————只适合存储完全二叉树
基本操作：
            i的左孩子————2i
            i的右孩子————2i+1
            i的父节点————i/2（注：向下取整）
            i所在的层次————log2(n+1)（注：向上取整）或log2n+1(注：log2n向下取整)
*/































































