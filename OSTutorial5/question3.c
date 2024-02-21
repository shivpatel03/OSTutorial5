#define _XOPEN_SOURCE 600
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NUM_STUDENTS 5

struct student {
    char name[50];
    int student_id;
    int grade;
};

void *bellcurve(void *student_ptr) {
    struct student *s = (struct student *)student_ptr;
    double curved_grade = s->grade * 1.5;
    printf("Name: %s, ID: %d, Curved Grade: %.2f\n", s->name, s->student_id, curved_grade);
    pthread_exit(NULL);

}

int main() {
    struct student students[NUM_STUDENTS];
    pthread_t threads[NUM_STUDENTS];

    printf("Enter the details of five students:\n");
    for (int i = 0; i < NUM_STUDENTS; i++) {
        printf("Student %d:\n", i + 1);
        printf("Name: ");
        scanf("%s", students[i].name);

        printf("Student ID: ");
        scanf("%d",&students[i].student_id);

        printf("Grade: ");
        scanf("%d", &students[i].grade);
    }

    for (int i = 0; i < NUM_STUDENTS; i++) {
        pthread_create(&threads[i], NULL, bellcurve, (void *)&students[i]);
    }

    for (int i = 0; i < NUM_STUDENTS; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;

}