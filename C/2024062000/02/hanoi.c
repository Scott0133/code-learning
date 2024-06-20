//递归版
#include<stdio.h>

int hanoi(int n, char from, char to, char via)
{
    if (n == 1) {
        printf("%c --> %c\n", from, to);
        return 1;
    } else {
        int c1 = hanoi(n - 1, from, via, to);
        hanoi(1, from, to, via);
        int c2 = hanoi(n - 1, via, to, from);
        return c1 + c2 + 1;
    }
}

int main()
{
    char A = 'A';
    char B = 'B';
    char C = 'C';
    hanoi(5, A, B, C);
}