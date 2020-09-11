#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

pthread_mutex_t lock;

void* try_this(void* arg) {
    pthread_mutex_lock(&lock);

    /*
        Critical Section Entry
    */
    int* counter = (int *) arg;
    *counter += 1;
    int my_counter = *counter; // 1
    /*
        Critical Section Exit
    */

    pthread_mutex_unlock(&lock);

    printf("\nJob %d has started\n", my_counter);

    // start my job
    for (unsigned long i = 0; i < (0xFFFFFFF); i++) {
    }
    // finish my job

    printf("\nJob %d has finished\n", my_counter);

    return NULL;
}

int main() {
    int counter = 0;
    int i = 0;
    int error;
    pthread_t tid[2];

    // 1. executing a PUT newfile
    // 2. executing a GET otherfile

    error = pthread_mutex_init(&lock, NULL);

    if (error) {
        printf("Mutex init failed.\n");
        return EXIT_FAILURE;
    }

    while (i < 2) {
        error = pthread_create(&tid[i], NULL, &try_this, &counter);

        if (error) {
            printf("\nThread can't be created : [%s]", strerror(error));
            return EXIT_FAILURE;
        }

        i++;
    }

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
}