#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 10
#define GRADES_FILE "grades.txt"
#define BELLCURVE_FILE "bellcurve.txt"

int grades[NUM_THREADS];
int total_grade = 0;
double total_bellcurve = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t barrier;

void read_grades() {
    FILE *file = fopen(GRADES_FILE, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Unable to open file %s\n", GRADES_FILE);
        exit(1);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        fscanf(file, "%d", &grades[i]);
    }

    fclose(file);
}

// Function to bell curve the grade and save to file
void *save_bellcurve(void *arg) {
    int *grade_ptr = (int *)arg;
    int grade = *grade_ptr;
    double bellcurved_grade = grade * 1.50;

    pthread_mutex_lock(&mutex);
    total_grade += grade;
    total_bellcurve += bellcurved_grade;
    pthread_mutex_unlock(&mutex);

    FILE *file = fopen(BELLCURVE_FILE, "a");
    if (file == NULL) {
        fprintf(stderr, "Error: Unable to open file %s\n", BELLCURVE_FILE);
        exit(1);
    }

    fprintf(file, "%.2f\n", bellcurved_grade);
    fclose(file);

    pthread_barrier_wait(&barrier);

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];

    pthread_barrier_init(&barrier, NULL, NUM_THREADS + 1);

    read_grades();

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, save_bellcurve, (void *)&grades[i]);
    }

    pthread_barrier_wait(&barrier);

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    double class_total_before = total_grade;
    double class_total_after = total_bellcurve;
    double class_average_before = class_total_before / NUM_THREADS;
    double class_average_after = class_total_after / NUM_THREADS;

    printf("Total Grade before bellcurve: %d\n", total_grade);
    printf("Class Average before bellcurve: %.2f\n", class_average_before);
    printf("Total Bellcurved Grade: %.2f\n", total_bellcurve);
    printf("Class Average after bellcurve: %.2f\n", class_average_after);

    pthread_barrier_destroy(&barrier);

    return 0;
}
