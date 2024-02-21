#define _XOPEN_SOURCE 600
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NUM_STUDENTS 10

int total_grade = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void class_total(int grade) {
    pthread_mutex_lock(&mutex);
    total_grade += grade;
    pthread_mutex_unlock(&mutex);
}

void *student_thread(void *arg) {
    int *grade_ptr = (int *)arg;
    int grade = *grade_ptr;
    class_total(grade); // adds grade to total_grade
}

int main() {
    pthread_t threads[NUM_STUDENTS];
    int grades[NUM_STUDENTS];

    printf("Enter the grades of all 10 students: \n");
    for (int i = 0; i < NUM_STUDENTS; i++) {
        printf("Student %d ", i + 1);
        scanf("%d", &grades[i]);
    }

    // create threads for each student
    for (int i = 0; i < NUM_STUDENTS; i++) {
        pthread_create(&threads[i], NULL, student_thread, (void *)&grades[i]);
    }

    for (int i = 0; i < NUM_STUDENTS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Total Grade: %d\n", total_grade);

    return 0;
}