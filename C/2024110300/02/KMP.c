#define _CRT_SECURE_NO_WARNINGS

// KMP算法

/**
 * name:KMP
 * time:2012-11-22
 * 字符串快速匹配
 */
#include<stdio.h>
#include<string.h>
typedef struct seqstring {
	char string[100];
	int length;
}seqstring;

void getnext(seqstring p, int next[]) {
	int i, j;
	i = 0;//指向字符串每个字符的下标
	j = -1;
	next[i] = j;//next[0]放上-1 
	while (i < p.length) {//没有到达结尾的话 
		if (j == -1 || p.string[i] == p.string[j]) {//如果是第一个字符或遇到相同的字符
			next[++i] = ++j;
		}
		else {
			j = next[j];
		}
	}
	for (i = 0;i < p.length;i++) {//输出next[]值 
		printf("%d ", next[i]);
	}
}

int kmp(seqstring t, seqstring p, int next[]) {
	int i, j;
	i = j = 0;
	while (i < t.length && j < p.length) {
		if (j == -1 || t.string[i] == p.string[j]) {
			i++;j++;
		}
		else {
			j = next[j];
		}
	}
	if (j == p.length) return i - p.length;
	else return -1;
}
void  main() {
	seqstring t, p;
	int next[50];
	printf("please input string t:");
	//scanf("%s", t.string);
	strcpy(t.string, "abdaaeabdaaeaeaeffd"); // T
	printf("%s\n", t.string);
	t.length = strlen(t.string);

	printf("please input string p:");
	//scanf("%s", p.string);
	strcpy(p.string, "aaab"); // P
	printf("%s\n", p.string);
	p.length = strlen(p.string);
	printf("next:");
	getnext(p, next);
	printf("\n%d\n", kmp(t, p, next));
}