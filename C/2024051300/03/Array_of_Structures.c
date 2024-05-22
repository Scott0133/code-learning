//结构体数组

#include<stdio.h>

struct Student {
    char name[20];
    int age;
    float gpa;
};

int main()
{
    struct Student students[3];

    for (int i=0; i<3; i++) {
        printf("Enter name for student %d:", i+1);
        scanf("%s", &students[i].name);

        printf("Enter age for student %d:", i+1);
        scanf("%d", &students[i].age);

        printf("Enter GPA for student %d:", i+1);
        scanf("%f", &students[i].gpa);
    }

    printf("Student Details:\n");
    for (int i=0; i<3; i++) {
        printf("Name: %s\n",students[i].name);
        printf("Age: %d\n",students[i].age);
        printf("GPA: %.2f\n",students[i].gpa);
        printf("\n");

    }

    return 0;
}