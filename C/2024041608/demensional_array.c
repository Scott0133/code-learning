#include<stdio.h>
int AB[2][3];                   //创建一个多维数组，两行三列
int main()
{
    int i;
    int j;
    int AB[2][3] = {1,2,3,4,5,6};   //定义多维数组赋值
                                    //列出有数组元素
    for( i=0; i<2; i++)
        for( j=0; j<3; j++)
            printf("AB[%d][%d] = %d\n",i,j,AB[i][j]);
    //寻找每个元素的地址
    for( i=0; i<2; i++)
        for( j=0; j<3; j++)
            printf("the address of AB[%d][%d] is = %d\n",i,j,&AB[i][j]);
    //每首行测试,由此可见AB[0]、AB[1]为指针
    printf("AB[0] is %d\n",AB[0]);      //AB[0] = &AB[0][0]
    printf("AB[1] is %d\n",AB[1]);      //AB[1] = &AB[1][0]
    //通过*AB[0]、*AB[1]访问每首行的值
    printf("*AB[0] is %d\n",*AB[0]);
    printf("*AB[1] is %d\n",*AB[1]);
    return 0;

}