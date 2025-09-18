#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>

int main(void){
    pid_t pid = fork();
    if(pid == 0){
        for(int i=0;i<8;i++){             
            printf("child=%d ppid=%d\n", getpid(), getppid());
            sleep(1);
        }
        _exit(0);
    }
    _exit(0);                              
}
