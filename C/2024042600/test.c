#include<stdio.h>
int main()
{
    int i;
    int j;
    int m = 1;
    int s = 0;
    for (i=1;i<3;i++)
        for (j=3;j>0;j--)
        {
            m = i*j;
            s = s+m;
        }
        printf("s=%d\n",s);

        return 0;
}
