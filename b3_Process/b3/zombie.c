#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>

int main(void){
    pid_t pid = fork();
    if(pid == 0){ _exit(0); }             
    if(pid > 0){                          
        printf("parent=%d child=%d\n", getpid(), pid);
        sleep(60);                        
    }
    return 0;
}
