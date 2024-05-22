#include<stdio.h>
#include<string.h>  //使用strlen()
char str[] = "hello";
char str2[] = "niko";

int main()
{
    int a = 0;

    printf("the length of string is %d\n",strlen(str));
    printf("the size of str[] is %d\n",sizeof(str));
    printf("%s\n",str);

    //判断字符是否读取到\0,输出字符，非字符串
    while( str2[a] != '\0')
    {
        for ( a=0; a<4; a++ )
            printf("%c",str2[a]);       //使用字符输出%c，若使用%s输出会出现
    }                                   //Segmentation fault

    //str2测试
    printf("\nstr[0] is %c\n",str2[0]);
    //*str2 == str2[0]
    printf("*str2 is %c\n",*str2);
    return 0;
}
