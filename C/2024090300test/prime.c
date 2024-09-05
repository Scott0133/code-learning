#include <stdio.h>
#include <time.h>

int is_prime(int num) {
    if (num <= 1) return 0;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return 0;
    }
    return 1;
}

int main() {
    int limit;
    printf("请输入要计算的范围上限: ");
    scanf("%d", &limit);

    clock_t start = clock();

    printf("素数: ");
    for (int i = 200000000; i <= limit; i++) {
        if (is_prime(i)) {
            printf("%d ", i);
        }
    }

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    printf("\n计算时间: %f 秒\n", time_spent);

    return 0;
}
