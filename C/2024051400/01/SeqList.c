//线性表

#include<stdio.h>
#include<stdlib.h>
#define ERROR 0;
#define OK 1;
#define Overflow 2;
#define Underflow 3;
#define NotPresent 4;
#define Duplicate 5;
typedef int ElemType;       //将ElemType定义为整型
typedef int Status;         //将Status定义为整型
Status Init();              //线性表初始化
Status Find();              //线性表查找
Status Insert();            //线性表插入
Status Delete();            //线性表删除
Status Output();            //线性表输出
void Destroy();             //线性表撤销

typedef struct seqList      //线性表顺序表示结构体定义
{
    int n;
    int maxLength;
    ElemType *element;      //*element顺序表存储空间首地址
} SeqList;

//-------------------------------------------------------------
void main()
{
    int i;
    SeqList list;               //创建一个list结构表
    Init(&list,10);             //初始化线性表，长度为10
    for (i=0; i<10; i++)
        Insert(&list, i-1, i);      //i-1
    Output(&list);
    Delete(&list,0);
    Output(&list);
    Destroy(&list);
}
//-------------------------------------------------------------

Status Init(SeqList *L,int mSize)              //线性表初始化
{
    L->maxLength = mSize;
    L->n = 0;
    L->element = (ElemType *)malloc(sizeof(ElemType)*mSize);
        if (!L->element)
            return ERROR;
                return OK;
}

Status Find(SeqList L,int i,ElemType *x)       //线性表查找
{
    if (i<0 || i>L.n-1)
        return ERROR;
    *x = L.element[i];
        return OK;
}

Status Insert(SeqList *L,int i,ElemType x)     //线性表插入 for (i=0; i<10; i++)   Insert(&list, i-1, i);
{
    int j;
    if (i<-1 || i>L->n-1)
        return ERROR;
    if (L->n == L->maxLength)
        return ERROR;
    for (j=L->n-1; j>i; j--)
        L->element[j+1] = L->element[j];       //!!
    L->element[i+1] = x;
    L->n = L->n+1;
    return OK;
}

Status Delete(SeqList *L,int i)                //线性表删除
{
    int j;
    if (i<0 || i>L->n-1)
        return ERROR;
    if (!L->n)
        return ERROR;
    for (j=i+1; j<L->n; j++);
        L->element[j-1] = L->element[j];       //!!
    L->n--;
    return OK;
}

Status Output(SeqList *L)                      //线性表输出
{
    int i;
    if (L->n == 0)
        return  ERROR;
    for (i=0; i<=L->n-1; i++)
        printf("%d \n",L->element[i]);
        return OK;
}
 
void Destroy(SeqList *L)                       //线性表撤销
{
    L->n = 0;
    L->maxLength = 0;
    free(L->element);
}