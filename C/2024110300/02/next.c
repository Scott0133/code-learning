// copilot
// 求next[]数组
// bug?
#include <stdio.h>
#include <string.h>

void computeNextArray(char *pattern, int *next) {
    int m = strlen(pattern);
    int j = 0; // length of previous longest prefix suffix
    int i = 1;

    next[0] = 0; // next[0] is always 0

    while (i < m) {
        if (pattern[i] == pattern[j]) {
            j++;
            next[i] = j;
            i++;
        } else {
            if (j != 0) {
                j = next[j - 1];
            } else {
                next[i] = 0;
                i++;
            }
        }
    }
}

int main() {
    char pattern[] = "abcabaab";
    int m = strlen(pattern);
    int next[m];

    computeNextArray(pattern, next);

    printf("Next array:\n");
    for (int i = 0; i < m; i++) {
        printf("%d ", next[i]);
    }
    printf("\n");

    return 0;
}
