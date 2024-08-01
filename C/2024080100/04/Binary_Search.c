// 二分查找————只适合有序顺序表
#include<stdio.h>
#define MAXSIZE 100 // 顺序表最大长度100
typedef struct SqList {
    int data[MAXSIZE];
    int length;
}SqList;

int count = 0;
int Binary_Search(SqList S, int key); // 二分查找，在有序表S中查找关键字key
void SetData(SqList *S, int x); // 顺序设置data，数组下标起始为0

int main()
{
    SqList S; // 定义顺序表
    S.length = 0;
    // 初始化顺序表
    SetData(&S, 7);
    SetData(&S, 10);
    SetData(&S, 13);
    SetData(&S, 16);
    SetData(&S, 19);
    SetData(&S, 29);
    SetData(&S, 32);
    SetData(&S, 33);
    SetData(&S, 37);
    SetData(&S, 41);
    SetData(&S, 43);
    //SetData(&S, 44);
    int ret = Binary_Search(S, 41);

    return 0;
}

void SetData(SqList *S, int x)
{
    S->data[count] = x;
    S->length++;
    count++;
}
int Binary_Search(SqList S, int key)
{
    int low, high, mid; // 声明三个变量代表数组下标
    low=0; high=S.length-1; // high指向数组最高位，low指向数组最低位
    while (low < high) // low > high则未找到key
    {
        mid =(low+high)/2; // mid向下取整
        if (S.data[mid] == key)
            return mid; // 找到key，返回数组下标
        else if (S.data[mid] > key)
            high = mid - 1;
        else
            low = mid + 1;
    }
    return -1; // 未找到
}