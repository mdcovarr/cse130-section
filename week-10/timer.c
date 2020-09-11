#include <err.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdbool.h>

int ports[3] = {8080, 8081, 8082};

struct thread_data {
    pthread_mutex_t* lock;
    pthread_cond_t* cond_var;
    int flag;
};

void* simple(void *ptr_td) {
    struct thread_data *td = (struct thread_data*) ptr_td;
    struct timespec ts;
    struct timeval now;

    while (true) {
        pthread_mutex_lock(td->lock);
        memset(&ts, 0, sizeof(ts));

        gettimeofday(&now, NULL);
        ts.tv_sec = now.tv_sec + 5;

        pthread_cond_timedwait(td->cond_var, td->lock, &ts);

        if (td->flag) {
            pthread_mutex_unlock(td->lock);
        }

        printf("Still Waiting: %d\n", td->flag);
        pthread_mutex_unlock(td->lock);

        // ----------------

        struct sockaddr_in server_addr;
        int connfd = socket(AF_INET, SOCK_STREAM, 0);

        if (connfd < 0) {
            return NULL;
        }

        memset(&server_addr, 0, sizeof(server_addr));

        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(ports[0]);

        inet_pton(AF_INET, "127.0.0.1", &(server_addr.sin_addr));

        if (connect(connfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
            return NULL;
        }

        printf("Established Connection to httpserver on port: %d\n", ports[0]);

        uint8_t buffer[4096];
        int ret = dprintf(connfd, "GET /healthcheck HTTP/1.1\r\n\r\n");

        if (ret < 0) {
            return NULL;
        }

        sleep(1);

        int bytes = read(connfd, buffer, sizeof(buffer));
        int length;
        int errors;
        int entries;

        int nscan = sscanf(buffer, "HTTP/1.1 200 OK\r\nContent-Length: %d\r\n%d\n%d", &length, &errors, &entries);

        printf("Errors: %d\nEntries: %d\n", errors, entries);

    }

    return NULL;
}

int main() {
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t cond_var = PTHREAD_COND_INITIALIZER;

    struct thread_data data;
    data.lock = &mutex;
    data.cond_var = &cond_var;
    pthread_t t1;
    printf("Starting Example...\n");
    data.flag = 0;

    pthread_create(&t1, NULL, simple, &data);
    printf("Starting Wait\n");
    getchar();
    data.flag = 1;
    pthread_cond_signal(data.cond_var);
    printf("Done Waiting...\n");

    return 0;
}
