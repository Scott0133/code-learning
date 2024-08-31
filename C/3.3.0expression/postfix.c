// 后缀表达式求值（逆波兰表达式）

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#define FALSE 0
#define TRUE 1
#define OverFlow 2 // 上溢
#define UnderFlow 3 // 下溢
#define NotPresent 4 // 元素不存在
#define Duplicate 5 // 元素重复
#define STACKSIZE 20 // 堆栈容量
#define ITEMSIZE 20 // 操作符最大长度
#define POSTFIXSIZE 200 // 后缀表达式允许最大长度
typedef double Elemtype; // Elemtype为双精度浮点型

typedef struct stack { // 堆栈结构体的定义
    int top; // top为当前栈顶位置下标
    int maxSize; // maxSize-1为堆栈的最大栈顶位置下标
    Elemtype *element; // element为存储堆栈元素的一维数组首地址的指针
} Stack;
// ------------------------------------------------------------------------stack
void Create(Stack *S, int mSize); // 创建一个能容纳mSize个单元的空堆栈
void Destroy(Stack *S); // 销毁一个已存在的堆栈，即释放堆栈占用的数组空间
int IsEmpty(Stack *S); // 判断堆栈是否为空，若为空返回TRUE，否则返回FALSE
int IsFull(Stack *S); // 判断堆栈是否已满，若是，则返回TRUE，否则返回FALSE
int Top(Stack *S, Elemtype *x); // 获取栈顶元素，通过x返回。返回栈顶元素
int Push(Stack *S, Elemtype x); // 在栈顶插入元素x（入栈）。若操作成功，则返回TRUE，否则返回FALSE
int Pop(Stack *S); // 删除栈顶元素（出栈）。若操作成功，则返回TRUE，否则返回FALSE
// ------------------------------------------------------------------------POSTFIX
int IsLegal(char *postfix); // 判断表达式是否存在非法字符，合法字符仅包含0~9、.、+、-、*、/、^和空格
int GetItem(char *postfix, int *curPos, char *item); // 从表达式当前位置curPos获取一个元素，获取完成后，curPos移动到下一个元素首字符位置
void DoOperator(Stack *S, char oper); // 根据操作符执行由2个操作数和1个操作符构成的基础表达式的计算
double Caculating(char *postfix); // 对后缀表达式postfix进行求值

int main()
{
    char postfix[POSTFIXSIZE]; // 存储表达式中扫描元素
    printf("请输入后缀表达式（连续的操作数之间用空格隔开）：\n");
    gets(postfix); // 从输入流读入后缀表达式，连续的操作数用空格隔开
    if (!IsLegal(postfix)) { // 检查后缀表达式中是否有非法字符
        printf("异常：中缀表达式中存在非法字符！\n");
        return FALSE;
    }
    printf("%s = %.2f\n", postfix, Caculating(postfix)); // 输出计算结果（保留两位小数）
    return 0;
}

void Create(Stack *S, int mSize)
{
    S->maxSize = mSize;
    S->element = (Elemtype *)malloc(mSize*sizeof(Elemtype));
    S->top = -1;
}
void Destroy(Stack *S)
{
    S->maxSize = 0;
    free(S->element);
    S->top = -1;
}
int IsEmpty(Stack *S)
{
    return S->top == -1;
}
int IsFull(Stack *S)
{
    return S->top == S->maxSize - 1;
}
int Top(Stack *S, Elemtype *x)
{
    if (IsEmpty(S)) {
        return FALSE;
    }
    *x = S->element[S->top];
    return *x;
}
int Push(Stack *S, Elemtype x)
{
    if (IsFull(S)) {
        return FALSE;
    }
    S->top++;
    S->element[S->top] = x;
    return TRUE;
}
int Pop(Stack *S)
{
    if (IsEmpty(S)) {
        return FALSE;
    }
    S->top--;
    return TRUE;
}
// ---
int IsLegal(char *postfix)
{
    int i;
    char c;
    for (i=0; i<strlen(postfix); i++) {
        c = postfix[i];
        if (!((c>='0' && c<='9') || c=='.' || c=='+' || c=='-'
                                || c=='*' || c=='/' || c=='^' || c==' ')) {
            return FALSE;
        }
    }
    return TRUE;
}
int GetItem(char *postfix, int *curPos, char *item)
{
    int i = 0; 
    int k = *curPos;
    int flag;
    if (postfix[k] == '.') { // 元素首字符不能是小数点
        flag = -1;
    } else if (postfix[k] >= '0' && postfix[k] <= '9') {  // 若元素的首字符是数字，则当前元素为操作数
        while ((postfix[k] >= '0' && postfix[k] <= '9') || postfix[k] == '.') {
            item[i++] = postfix[k++];
        }
        item[i] = '\0';
        flag = 0;
    } else {
        item[0] = postfix[k++];
        item[1] = '\0';
        flag = 1;
    }
    while (postfix[k] == ' ') { //跳过当前元素后面的空格，下次取元素的起始位置为非空格字符
        k++;
    }
    *curPos = k;
    return flag;
}
void DoOperator(Stack *S, char oper)
{
    double oper1, oper2;
    if (!Top(S, &oper1)) { // 从栈中弹出右操作数
        printf("异常：后缀表达式出错，存在多余操作符！\n");
        exit(0);
    }
    Pop(S);
    if (!Top(S, &oper2)) { // 从栈中弹出左操作数
        printf("异常：后缀表达式出错，存在多余操作符！\n");
        exit(0);
    }
    Pop(S);
    switch(oper) {
        case '+':
            Push(S, oper2 + oper1);
            break;
        case '-':
            Push(S, oper2 - oper1);
            break;
        case '*':
            Push(S, oper2 * oper1);
            break;
        case '/':
            if (fabs(oper1) < 1e-6) { // 1e-6为极小浮点值
                printf("异常：除数不可以为0！\n");
                exit(0);
            } else {
                Push(S, oper2 / oper1);
            }
            break;
        case '^':
            Push(S, pow(oper2, oper1));
            break;
    }
}
double Caculating(char * postfix) // 对后缀表达式postfix进行求值
{
    Stack S;
    char item[ITEMSIZE]; // 存储后缀表达式中的元素
    double data;
    int flag = -1; // 标识当前扫描元素的类型，操作符标记1，操作数标记0，存在异常标记-1
    int curPos = 0; // 记录当前扫描元素的首字符下标的位置
    while (postfix[curPos] == ' ') { // 过滤postfix前面的所有空格
        curPos++;
    }
    Create(&S, STACKSIZE); // 创建堆栈，动态申请STACKSIZE大小的空间
    while (curPos < strlen(postfix)) {
        flag = GetItem(postfix, &curPos, item); // 获取当前扫描的表达式元素
        if (flag == -1) {
            printf("异常：后缀表达式元素不合法！\n");
            exit(0);
        } else if (flag == 1) { // 当前元素为操作符，则进行相应的计算
            switch(item[0]) {
                case '+':
                case '-':
                case '*':
                case '/':
                case '^':
                    DoOperator(&S, item[0]);
                    break;
            }
        } else { // 当前元素为操作数，则进栈
            data = atof(item); // atof为系统函数，将字符串item转换为浮点数并返回
            Push(&S, data);
        }
    }
    if (S.top == 0) {  // 若栈中只剩下唯一的元素，则栈顶元素即为计算结果
        Top(&S, &data);
    } else {
        printf("异常：后缀表达式出错，存在多余操作数！\n");
        exit(0);
    }
    Destroy(&S); // 释放堆栈创建时动态申请的空间
    return data;
}