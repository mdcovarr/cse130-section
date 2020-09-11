#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void* thread_func(void* void_ptr) {
    int* x_ptr = (int *)void_ptr;

    while (++(*x_ptr) < 100);
    printf("x incremented finished\n");

    return NULL;
}

int main() {
    int x = 101;
    int y = 0;
    pthread_t inc_x_thread;
    printf("x: %d, y: %d\n", x, y);

    // 1. pointer to a thread_id
    // 2. refers to a specified attribute
    // 3. the name of function to be executed for the created thread
    // 4. argument that is passed to the function
    int error = pthread_create(&inc_x_thread, NULL, thread_func, &x);

    if (error) {
        fprintf(stderr, "Error creating thread\n");
        return EXIT_FAILURE;
    }

    while (++y < 100);
    printf("y increment finished\n");

    error = pthread_join(inc_x_thread, NULL);

    if (error) {
        fprintf(stderr, "Error joining thread\n");
        return EXIT_FAILURE;
    }

    printf("x: %d: y: %d\n", x, y);
}
