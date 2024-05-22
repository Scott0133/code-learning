//指向指针的指针
#include<stdio.h>
int main()
{
    int x = 5;

    int *p;     //int* p = &x;
    p = &x;

    int **q;    //int** q = &p;
    q = &p;

    int ***r;   //int*** r = &q;
    r = &q;

    *p = 6;
    printf("the address of x is %d\n\n",&x);    //44

    printf("the address of p is %d\n",&p);      //32
    printf("the value of p is %d\n",p);         //44
    printf("the value of *p is %d\n\n",*p);     //6

    printf("the address of q is %d\n",&q);      //24
    printf("the value of q is %d\n",q);         //32
    printf("the value of *q is %d\n",*q);       //44
    printf("the value of **q is %d\n\n",**q);   //6

    printf("the address of r is %d\n",&r);      //16
    printf("the value of r is %d\n",r);         //24
    printf("the value of *r is %d\n",*r);       //32
    printf("the value of **r is %d\n",**r);     //44
    printf("the value of ***r is %d\n\n",***r); //6

    printf("*(*q) = %d",*(*q));

    return 0;
}