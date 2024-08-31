// 中缀表达式转后缀表达式

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define FALSE 0
#define TRUE 1
#define OverFlow 2 // 上溢
#define UnderFlow 3 // 下溢
#define NotPresent 4 // 元素不存在
#define Duplicate 5 // 元素重复
#define STACKSIZE 20 // 堆栈容量
#define ITEMSIZE 20 // 操作符最大长度
#define EXPSIZE 200 // 后缀表达式允许最大长度
typedef char Elemtype;
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
//--------------------------------------------------------------------------infix to postfix
int IsLegal(char *postfix); // 表达式合法判断
int GetItem(char *postfix, int *curPos, char *item); // 从表达式当前位置curPos获取一个元素，获取完成后，curPos移动到下一个元素首字符位置
int ICP(char c); // 获取操作符的栈外优先级
int ISP(char c); // 获取操作符的栈内优先级
void InfixToPostfix(char *infix, char *postfix); // 中缀表达式转后缀表达式，后缀表达式中相邻元素（操作符或操作数）用空格分隔

int main()
{
    char infix[EXPSIZE]; // 存储用户输入的中缀表达式
    char postfix[EXPSIZE]; // 存储转换生成的后缀表达式
    printf("请输入中缀表达式：%s\n", infix);
    gets(infix);
    if (!IsLegal(infix)) {
        printf("异常：中缀表达式中存在非法字符！\n");
        return FALSE;
    }
    InfixToPostfix(infix, postfix);
    printf("%s ===> %s \n", infix, postfix); // 取栈顶元素，得结果输出 

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
                                || c=='*' || c=='/' || c==' ' || c=='(' || c==')')) {
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
int ICP(char c)
{
    if (c == '#')
        return 0;
    else if (c == '(')
        return 7;
    else if (c == '*' || c == '/')
        return 4;
    else if (c == '+' || c == '-')
        return 2;
    else if (c == ')')
        return 1;
    else {
        printf("后缀表达式不支持操作符%c！\n", c);
        exit(0);
    }
}
int ISP(char c)
{
    if (c == '#')
        return 0;
    else if (c == '(')
        return 1;
    else if (c == '*' || c == '/')
        return 5;
    else if (c == '+' || c == '-')
        return 3;
    else if (c == ')')
        return 7;
    else {
        printf("后缀表达式不支持操作符%c！\n", c);
        exit(0);
    }
}
void InfixToPostfix(char *infix, char *postfix)
{
    Stack S;
    char item[ITEMSIZE]; // 存储中缀表达式中的元素
    int flag = -1; // 标识当前扫描元素的类型，操作符标记1，操作数标记0，存在异常标记-1
    int curPos = 0; // 记录当前扫描元素的首字符下标位置
    int k = 0;
    int i;
    char ch, curOP;

    while (infix[curPos] == ' ') { // 过滤infix最前面的所有空格
        curPos++;
    }
    Create(&S, STACKSIZE);
    Push(&S, '#');
    while (curPos < strlen(infix))
    {
        flag = GetItem(infix, &curPos, item); // 获取当前扫描的表达式元素
        if (flag == -1) 
        {
            printf("异常：中缀表达式不合法！\n");
            exit(0);
        } 
        else if (flag == 1) 
        { // 当前元素为操作符或界符
            curOP = item[0];
            if (curOP == ')') 
            { // 扫描到右括号的处理，连续出栈输出，直到遇到左括号
                do 
                {
                    Top(&S, &ch);
                    Pop(&S);
                    if (ch == '#') 
                    {
                        printf("异常：中缀表达式不合法！\n");
                        exit(0);
                    }
                    if (ch != '(') 
                    { // 左括号不输出
                        postfix[k++] = ch;
                        postfix[k++] = ' '; // 相邻元素用空格分隔
                    }
                } while (ch != '('); 
            } 
            else {
                Top(&S, &ch); // 获取当前栈顶操作符
                while (ICP(curOP) <= ISP(ch)) 
                {
                    Pop(&S);
                    postfix[k++] = ch;
                    postfix[k++] = ' '; // 相邻元素用空格分隔
                    Top(&S, &ch);
                }
                Push(&S, curOP); // 当前扫默奥的操作符进栈
            }
        } 
        else 
        {
            for (i=0; i<strlen(item); i++,k++) {
                postfix[k] = item[i];
            }
            postfix[k++] = ' '; // 相邻元素用空格分隔
        }
    }
    while(!IsEmpty(&S)) { // 输出栈中剩余操作符
        Top(&S, &ch);
        Pop(&S);
        if (ch != '#') {
            postfix[k++] = ch;
            postfix[k++] = ' ';
        }
    }
    postfix[--k] = '\0'; // 去除最后一个多余的空格
}

