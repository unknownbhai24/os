#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t wrt;
pthread_mutex_t mutex;

int read_count = 0;
int shared_data = 0;

void* reader(void* arg) {
    int id = *((int*)arg);
    while (1) {
        pthread_mutex_lock(&mutex);
        read_count++;
        if (read_count == 1)
            sem_wait(&wrt);
        pthread_mutex_unlock(&mutex);

        printf("Reader %d read data: %d\n", id, shared_data);

        pthread_mutex_lock(&mutex);
        read_count--;
        if (read_count == 0)
            sem_post(&wrt);
        pthread_mutex_unlock(&mutex);

        sleep(1);
    }
    return NULL;
}

void* writer(void* arg) {
    int id = *((int*)arg);
    while (1) {
        sem_wait(&wrt);

        shared_data++;
        printf("Writer %d wrote data: %d\n", id, shared_data);

        sem_post(&wrt);
        sleep(2);
    }
    return NULL;
}

int main() {
    pthread_t rtid[3], wtid[2];
    int rids[3] = {1, 2, 3};
    int wids[2] = {1, 2};

    sem_init(&wrt, 0, 1);
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < 3; i++)
        pthread_create(&rtid[i], NULL, reader, &rids[i]);
    for (int i = 0; i < 2; i++)
        pthread_create(&wtid[i], NULL, writer, &wids[i]);

    for (int i = 0; i < 3; i++)
        pthread_join(rtid[i], NULL);
    for (int i = 0; i < 2; i++)
        pthread_join(wtid[i], NULL);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}
