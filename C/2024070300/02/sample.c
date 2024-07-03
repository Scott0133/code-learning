#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#define  STACK_INIT_SIZE 100
#define STACKINCREMENT 10
typedef char ElemType;

typedef struct
{
    ElemType *base;
    ElemType *top;
    int stackSize;
}SqStack;

//创建一个栈
void initStack(SqStack *s) {
    s->base = (ElemType *)malloc(sizeof(ElemType));
    if (!s->base)
    {
        exit(0);
    }
    s->top = s->base;   //最开始 栈底就是栈顶
    s->stackSize = STACK_INIT_SIZE;
}

void Push(SqStack *s, ElemType e) {
    //如果栈满  追加空间
    if (s->top - s->base >= s->stackSize)
    {
        s->base = (ElemType *)realloc(s->base, (s->stackSize + STACKINCREMENT) * sizeof(ElemType));
        if (!s->base)
        {
            exit(0);
        }
        s->top = s->base + s->stackSize;  //设置栈顶
        s->stackSize = s->stackSize + STACKINCREMENT;
    }
    *(s->top) = e;
    s->top++;
}

void Pop(SqStack *s, ElemType *e) {
    if (s->top == s->base)
    {
        return;
    }
    *e = *--(s->top);
}

int StackLen(SqStack s) {
    return (s.top - s.base);
}

int main() {
    char cal[50];
    char c, e;
    SqStack s;
    initStack(&s);
    printf("请输入中缀表达式 输入#表示结束\n");
    scanf("%c", &c);
    while (c != '#')
    {
        while (c>='0' && c<='9')
        {
            printf("%c ", c);
            scanf("%c", &c);
            if (c<'0' || c>'9')
            {
                printf(" ");
            }
        }
        if (c == ')')
        {
            Pop(&s, &e);
            while (e != '(')
            {
                printf("%c ", e);
                Pop(&s, &e);
            }
        }
        else if (c == '+' || c == '-')
        {
            if (!StackLen(s))
            {
                Push(&s, c);
            }
            else {
                do
                {
                    Pop(&s, &e);
                    if (e == '(')
                    {
                        Push(&s, e);
                    }
                    else {
                        printf("%c ", e);
                    }
                } while (StackLen(s) && e!='(');
                Push(&s, c);
            }
        }else if (c=='*' || c=='/' || c=='(')
        {
            Push(&s, c);
        }else if (c=='#')
        {
            break;
        }
        else {
            printf("出错，输入格式错误");
            return -1;
        }
        scanf("%c", &c);
    }
    while (StackLen(s))
    {
        Pop(&s, &e);
        printf("%c ", e);
    }
    return 0;
}