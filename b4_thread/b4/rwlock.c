#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int data = 0;
pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;

void* reader(void* arg) {
    int id = *(int*)arg;
    pthread_rwlock_rdlock(&rwlock);
    printf("Reader %d: data = %d\n", id, data);
    sleep(1);
    pthread_rwlock_unlock(&rwlock);
    return NULL;
}

void* writer(void* arg) {
    int id = *(int*)arg;
    pthread_rwlock_wrlock(&rwlock);
    data++;
    printf("Writer %d: data = %d\n", id, data);
    pthread_rwlock_unlock(&rwlock);
    return NULL;
}

int main() {
    pthread_t r[5], w[2];
    int rid[5] = {1,2,3,4,5};
    int wid[2] = {1,2};
    
    for(int i = 0; i < 5; i++)
        pthread_create(&r[i], NULL, reader, &rid[i]);
    
    for(int i = 0; i < 2; i++)
        pthread_create(&w[i], NULL, writer, &wid[i]);
    
    for(int i = 0; i < 5; i++)
        pthread_join(r[i], NULL);
    
    for(int i = 0; i < 2; i++)
        pthread_join(w[i], NULL);
    
    return 0;
}
