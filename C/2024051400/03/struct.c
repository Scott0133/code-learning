//链表结构表示框架
typedef struct LNode {
    int data;
    struct LNode *next;
}LNode,*LinkList;           //定义结点指针p： LNode *p（常用） 或 LinkList p
                            //定义链表L：LinkList L（常用） 或 LNode *L



//例：存储学生学号、姓名、成绩的单链表结点类型定如下:
typedef struct student {
    char num[8];
    char name[8];
    int score;
    struct student *next;
}LNode,*LinkList;
//为统一链表操作，通常定义如下：
typedef struct ElemType {
    char num[8];
    char name[8];
    int score;
}ElemType;

typedef struct LNode {
    ElemType data;
    struct LNode *next;
}LNode,*LinkList;
