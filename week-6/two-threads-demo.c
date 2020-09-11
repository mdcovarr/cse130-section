#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define THREAD_COUNT 2

pthread_t tid[THREAD_COUNT];
int counter = 0;


void* try_this() {
    counter += 1;

    printf("\nJob %d has started\n", counter);

    // strart of threads job
    for (unsigned long i = 0; i < (0xFFFFFFF); i++) {
    }
    // end of threads job

    printf("\nJob %d has finished\n", counter);

    return NULL;
}

int main() {
    int i = 0;
    int error;

    while (i < THREAD_COUNT) {
        error = pthread_create(&tid[i], NULL, &try_this, NULL);

        // check to see if error creating thread
        if (error) {
            printf("\nThread can't be created : [%s]", strerror(error));
        }

        i++;
    }

    // Join the threads.
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
}