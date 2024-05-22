#include<stdio.h>
void bianli();
int a[3][3] = {{1,1,1},{1,1,1},{1,1,1}};
int main()

{
    bianli();
    return 0;
}

void bianli()
{
    int i;
    int j;
    for ( i=0; i<3; i++)
        for( j=0; j<3; j++)
            printf("a[%d][%d]=%d\n",i,j,a[i][j]);
}

