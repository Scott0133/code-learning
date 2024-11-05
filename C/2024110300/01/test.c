// 计算1!+2!+3!+...+100!
// 1, 2*1, 3*2*1, 4*3*2*1 ...
#include <stdio.h>

unsigned long long factorial(int n) {
    unsigned long long result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main() {
    unsigned long long sum = 0;
    for (int i = 1; i <= 3; i++) {
        sum += factorial(i);
    }
    printf("The sum of factorials from 1! to 3! is: %llu\n", sum);
    return 0;
}



