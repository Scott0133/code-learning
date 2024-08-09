// 冒泡排序
#include<stdio.h>
#define TRUE 0
#define FALSE 1
#define OK 0



int bubble_sort(int Arr[], int length);
void swap(int *a, int *b);
void Print(int Arr[]);

int main()
{
    // test
    // int a = 3;
    // int b = 4;
    // swap(&a, &b);
    int Arr[] = {49, 38, 65, 97, 76, 13, 27, 49};
    int length = sizeof(Arr) / sizeof(Arr[0]);
    bubble_sort(Arr, length);
    Print(Arr);
    return 0;
}

void swap(int *a, int *b) // 定义交换
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
int bubble_sort(int Arr[], int length)
{
    for (int i=0; i<length-1; i++) {
        int flag = FALSE; // 当发生交换，flag置为TURE
        for (int j=length-1; j>i; j--) {
            if (Arr[j-1] > Arr[j]) {
                swap(&Arr[j-1], &Arr[j]);
                flag = TRUE;
            }
        }
        if (flag == FALSE) {
            return OK;
        }
    }
}
void Print(int Arr[])
{
    for (int i=0; i<8; i++)
    {
        printf("%d ", Arr[i]);
    }
}