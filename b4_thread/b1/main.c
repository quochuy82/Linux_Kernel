#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* thread_function(void* arg) {
    pthread_t thread_id = pthread_self();
    printf("Thread with ID %lu is running!\n", (unsigned long)thread_id);
    sleep(1);
    printf("Thread with ID %lu finished!\n", (unsigned long)thread_id);
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    
    printf("Program started\n");
    printf("Main thread ID: %lu\n\n", (unsigned long)pthread_self());
    
    if (pthread_create(&thread1, NULL, thread_function, NULL) != 0) {
        printf("Error: Cannot create thread 1\n");
        return 1;
    }
    
    if (pthread_create(&thread2, NULL, thread_function, NULL) != 0) {
        printf("Error: Cannot create thread 2\n");
        return 1;
    }
    
    printf("Created 2 threads successfully\n");
    printf("Thread 1 ID: %lu\n", (unsigned long)thread1);
    printf("Thread 2 ID: %lu\n\n", (unsigned long)thread2);
    
    printf("Main thread waiting for thread 1...\n");
    pthread_join(thread1, NULL);
    printf("Thread 1 completed\n");
    
    printf("Main thread waiting for thread 2...\n");
    pthread_join(thread2, NULL);
    printf("Thread 2 completed\n");
    
    printf("\nAll threads completed. Program finished.\n");
    
    return 0;
}
