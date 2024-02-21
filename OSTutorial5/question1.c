#define _XOPEN_SOURCE 600
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

void *hello_world() {
    srand(time(NULL));
    int random_sleep = rand() % 5 + 1;
    sleep(random_sleep);
    printf("\nhello world\n");
    pthread_exit(NULL);
}

void *goodbye() {
    srand(time(NULL));
    int random_sleep = rand() % 5 + 1;
    sleep(random_sleep);
    printf("\ngoodbye\n");
    pthread_exit(NULL);
}

int main(void) {
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, hello_world, NULL);
    pthread_create(&thread2, NULL, goodbye, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}