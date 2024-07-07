/*
首先，S.ch 是一个字符数组，而你试图将字符串 "test" 直接赋值给 S.ch[5]。这是不允许的，因为字符数组的元素只能一个一个地赋值，而不是整体赋值。你可以使用 strcpy 函数将字符串复制到 S.ch 中。
下列代码实现strcpy()
*/
#include <stdio.h>
#define MAXLEN 255

typedef struct {
    char ch[MAXLEN];
    int length;
} SString;

void copyString(SString *S, char *src);

int main() {
    SString S;
    char src[] = "test";                  //定义源串

    copyString(&S, src);

    printf("S.ch: %s\n", S.ch);
    printf("S.length = %d\n", S.length);

    return 0;
}

void copyString(SString *S, char *src) {       //S为目标串，src为源串
    int i;
    for (i=0; src[i] != '\0'; i++) 
    {
        S->ch[i] = src[i];
    }
    S->ch[i] = '\0';                     // 添加字符串结尾的空字符
    S->length = i;
}