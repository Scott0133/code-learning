//字符数组和指针

#include<stdio.h>
#include<string.h>
void Print(char C[]);
void Print2(char* C);

int main()
{
    char C[] = "LOAK";
    char C2[5] = "LOAK";        //OR char C2[5] = {'L','O','A','K','\0'};
    int len = strlen(C);
    int len2 = strlen(C2);
    printf("Length = %d\n", len);
    printf("Length = %d\n", len2);
    
    Print(C);
    Print2(C);
}

void Print(char C[])
{
    int i = 0;
    while (C[i] != '\0')
    {
        printf("%c", C[i]);
        i++;
    }
}

void Print2(char* C)
{
    while (*C != '\0')
    {
        printf("%c", *C);
        C++;
    }
}