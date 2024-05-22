//函数指针成员

#include<stdio.h>

struct MathOperations {
    int (*add)(int, int);
    int (*substract)(int, int);
};

int add (int a,int b);
int substract(int a, int b);

int main(){
    struct MathOperations math;

    math.add = add;
    math.substract = substract;

    int result1 = math.add(5,3);
    int result2 = math.substract(10,4);
    
    printf("Addition result :%d\n", result1);
    printf("Substraction result:%d\n",result2);

    return 0;
}

int add (int a,int b){
    return a+b;
}

int substract(int a, int b){
    return a-b;
}