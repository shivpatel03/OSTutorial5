#define _XOPEN_SOURCE 600
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NUM_STUDENTS 5

void *bellcurve(void *grade_ptr) {
    int *grade = (int *)grade_ptr;
    double curved_grade = (*grade) * 1.50;
    printf("Curved grade: %.2f\n", curved_grade);
    pthread_exit(NULL);
}

int main(void) {
    int grades[NUM_STUDENTS];
    pthread_t threads[NUM_STUDENTS];

    printf("Enter the grades of 5 students:\n");
    for (int i = 0; i < NUM_STUDENTS; i++) {
        printf("Student %d: ", i + 1);
        scanf("%d", &grades[i]);
    }


    for (int i = 0; i < NUM_STUDENTS; i++) {
        pthread_create(&threads[i], NULL, bellcurve, (void *)&grades[i]);
    }

    for (int i = 0; i < NUM_STUDENTS; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;


}