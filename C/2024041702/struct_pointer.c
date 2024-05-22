#include<stdio.h>
typedef struct Birthday {
    int year;
    int month;
    int day;
} Birthday;

typedef struct Student {
    int id;             //学号
    char *name;         //姓名
    int age;            //年龄
    float score;        //成绩
    Birthday Birthday;  //生日，嵌套的结构体
} Student;

void printStudentInfo(Student *pStu)        //打印信息，通过指针传递
{
    printf("学号%d\t姓名%s\t年龄%d\t成绩%.2f\t生日%d-%d-%d\n",
            pStu->id,pStu->name,pStu->age,pStu->score,
                pStu->Birthday.year,pStu->Birthday.month,pStu->Birthday.day);   //注意Birthday是普通结构体，用.访问成员
}

int main()
{
    Student stu1 = {1,"niko",20,100,2000,2,1};  //定义学生一并填写学生一信息
    Student stu2 = {2,"mike",21,99,2001,9,2};   //定义学生二并填写学生二信息

    Student *pStu = &stu1;      //结构体指针，指向stu1, == struct Student *pStu = &stu1;
    printStudentInfo(pStu);     //打印学生一信息
    pStu = &stu2;               //将结构体指针重新指向stu2
    printStudentInfo(pStu);     //打印学生二信息
}