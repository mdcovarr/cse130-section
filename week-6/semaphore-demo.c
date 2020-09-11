#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

sem_t mutex;

void* thread(void* arg) {
    // Wait
    sem_wait(&mutex);
    printf("\nEnter Critical Section\n");

    sleep(4);

    // Signal
    printf("\nExit Critical Section\n");
    sem_post(&mutex);
}
int main() {
    sem_init(&mutex, 0, 1);
    pthread_t t1;
    pthread_t t2;

    pthread_create(&t1, NULL, &thread, NULL);
    sleep(2);
    pthread_create(&t2, NULL, &thread, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    sem_destroy(&mutex);

    return EXIT_SUCCESS;
}
