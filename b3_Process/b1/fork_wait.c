// fork_wait.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        printf("[Child ] PID=%d, PPID=%d\n", getpid(), getppid());
        exit(10); 
    } else {
        printf("[Parent] PID=%d, child PID=%d\n", getpid(), pid);

        int status = 0;
        pid_t w = waitpid(pid, &status, 0);
        if (w == -1) {
            perror("waitpid");
            return 1;
        }

        if (WIFEXITED(status)) {
            printf("[Parent] Child %d exited normally with code %d\n",
                   w, WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("[Parent] Child %d killed by signal %d\n",
                   w, WTERMSIG(status));
        } else {
            printf("[Parent] Child %d ended abnormally\n", w);
        }
    }
    return 0;
}
