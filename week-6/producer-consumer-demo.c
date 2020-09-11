#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#define NUMTHREADS 2

int data_ready;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition_variable = PTHREAD_COND_INITIALIZER;
int thread_id[NUMTHREADS]  = {0, 1};

/*
    Consumer thread
    worker threads

    worker 1 thread
    worker 2 thread 
    ...
    worker n - 1  thread
*/
void* consumer(void* notused) {
    printf("\033[0;32m[+] In Consumer thread...\n\033[0m");

    while (true) {
        pthread_mutex_lock(&mutex);
        printf("\033[0;32m[+] Consumer has the lock\n\033[0m");
        printf("\033[0;32m[+] Consumer startes executing critical section\n\033[0m");

        while (!data_ready) {
            // sleeping
            printf("\033[0;32m[+] Consumer going to Sleep\n\033[0m");
            pthread_cond_wait(&condition_variable, &mutex);

            printf("\033[0;32m[+] Consumer Signaled to WAKE UP\n\033[0m");
        }

        printf("\033[0;32m[+] Consumer: got data from producer\n\033[0m");
        printf("\033[0;32m[+] Consumer processiong data...\n\033[0m");

        for (int i = 0; i <= 100; i += 25) {
            printf("\033[0;32m[+] %d%%\t\t\tComplete\n\033[0m", i);
            sleep(1);
        }
        printf("\033[0;32m[+] Consumer Done consuming...\n\033[0m");

        data_ready = 0;
        pthread_cond_signal(&condition_variable);
        pthread_mutex_unlock(&mutex);
    }
}

/*
    Producer thread
    1 producer - accept reqeusts, handoff job to consumer
*/
void* producer(void* notused) {
    printf("\033[0;33m[-] In Producer thread...\n\033[0m");

    while (true) {
        pthread_mutex_lock(&mutex);

        while(data_ready) {
            // sleeping
            printf("\033[0;33m[-] Producer going to Sleep\n\033[0m");
            pthread_cond_wait(&condition_variable, &mutex);
            // data_ready = 0
            printf("\033[0;33m[-] Producer Signaled to WAKE UP\n\033[0m");
        }

        printf("\033[0;33m[-] Producer: getting data from h/w\n\033[0m");
        for (int i = 0; i <= 100; i += 20) {
            printf("\033[0;33m[-] %d%%\t\tComplete reading data...\n\033[0m", i);
            sleep(1);
        }

        data_ready = 1; // true
        pthread_cond_signal(&condition_variable);
        pthread_mutex_unlock(&mutex);
    }
}

int main() {
  pthread_t thread[NUMTHREADS];
  /*
    pthread_create(&thread[2], NULL, (void *)watch, &thread_id[2]);
  */

  /* create one consumer and one producer */
  pthread_create(&thread[0], NULL, &consumer, &thread_id[0]);
  pthread_create(&thread[1], NULL, &producer, &thread_id[1]);
  
  for(int i = 0; i< NUMTHREADS ; i++) {
      pthread_join(thread[i], NULL);
    }
}