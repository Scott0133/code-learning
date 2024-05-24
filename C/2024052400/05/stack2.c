#include <stdio.h>
#include <stdlib.h>
#define TRUE         1
#define FALSE        0
#define OK           1
#define ERROR        0
#define INFEASIBLE  -1
#define OVERFLOW    -2
 
typedef int Status;             //给int定义别名为status
#define StackInitSize    10     //顺序栈存储空间的初始分配量
#define StackAddSize     10     //顺序栈存储空间每次增加的分配量

typedef struct {      //定义顺序栈的结构体
    int *base;
    int *top;
    int StackSize;
}SqStack;

Status InitStack(SqStack *S);       //初始化一个空顺序栈 
Status DestroyStack(SqStack *S);    //销毁一个顺序栈 
Status ClearStack(SqStack *S);      //清空顺序栈
Status EmptyStack(SqStack S);       //判断顺序栈是否为空
Status FullStack(SqStack S);        //判断顺序栈是否已满
int StackLength(SqStack S);              //求当前顺序栈的长度
Status Push(SqStack *S,int e);      //插入元素e为新的栈顶元素
Status Pop(SqStack *S,int *e);      //删除栈顶元素，并用e返回
Status GetTop(SqStack S,int *e);    //获取栈顶元素，并用e返回
void PrintStack(SqStack S);        //打印顺序栈的元素
 
        int main(){
            SqStack S;
            InitStack(&S);
            Push(&S,1);
            Push(&S,2);
            Push(&S,3);
            Push(&S,4);
            Push(&S,5);
            Push(&S,6);
            Push(&S,7);
            Push(&S,8);
            Push(&S,9);
            Push(&S,10);
            Push(&S,11);
            int a;
            GetTop(S,&a);
            printf("此时栈顶的元素为%d\n",a);
            printf("%d\n",FullStack(S));
            printf("%d\n",EmptyStack(S));
            PrintStack(S);
            int e;
            Pop(&S,&e);
            printf("删除的元素为%d\n",e);
            GetTop(S,&a);
            printf("此时栈顶的元素为%d\n",a);
            printf("%d\n",StackLength(S));
            DestroyStack(&S);
        }
 
Status InitStack(SqStack *S) {
    S->base=(int *)malloc(StackInitSize*(sizeof(int))); //动态分配数组空间
    if(!S->base)
        exit(OVERFLOW);                                 //存储空间分配失败
    S->top=S->base;
    S->StackSize=StackInitSize;                         //初始化后最大容量为StackInitSize
    return OK;
}
 
Status DestroyStack(SqStack *S) {
    if (S==NULL) 
        exit(OVERFLOW);
    free(S->base);                  //释放动态开辟的空间
    S->base=NULL;
    S->top=NULL;
    S->StackSize=0;
    return OK;
}

Status ClearStack(SqStack *S) {
    if (!S->base) 
        exit(OVERFLOW);   //只需将顺序栈的top指针指向base指针即可清空
    S->top=S->base;
    return OK;
}

Status EmptyStack(SqStack S) {
    if (S.base==S.top) 
        return TRUE;
    return FALSE;
}

Status FullStack(SqStack S) {
    return S.top-S.base>=S.StackSize;
}

int StackLength(SqStack S) {
    return S.top-S.base;
}
//----------------------------------------------------入栈
Status Push(SqStack *S,int e) {
    if (S->top-S->base>=S->StackSize)
    {
        S->base=(int *)realloc(S->base,(S->StackSize+StackAddSize)*sizeof(int));
        if(!S->base) 
            exit(OVERFLOW);                 //存储空间分配失败
        S->top=S->base+S->StackSize;        //此时top指针在新分配的存储空间的StackSize位置上
        S->StackSize+=StackAddSize;
    }
    *(S->top)=e;
    S->top++;
    return OK;
}
//----------------------------------------------------出栈
Status Pop(SqStack *S,int *e) {
    if (S->top==S->base)
    {
        return ERROR;
    }
    S->top--;                   //先自减，到达删除元素的位置
    *e = *(S->top);
    return OK;
}

Status GetTop(SqStack S,int *e) {
    if (S.top==S.base)
    {
        printf("此栈为空\n");
        return ERROR;
    }
    *e=*(S.top-1);
    return OK;
}

void PrintStack(SqStack S) {
    if (EmptyStack(S))
    {
        printf("此栈为空,不能读取\n");
        exit(OVERFLOW);
    }
    int *p = S.top - 1;
    printf("栈顶\n");
    while (p >= S.base) {
        printf("%d\n", *p);
        p--;
    }
    printf("栈底\n");
}