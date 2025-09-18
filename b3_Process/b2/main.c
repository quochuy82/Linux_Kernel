#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

int main(void) {
    const char *env_name = "MY_COMMAND";
    const char *env_value = "ls";

    printf("Parent process (PID: %d) is setting environment variable '%s=%s'\n", getpid(), env_name, env_value);

    if (setenv(env_name, env_value, 1)!= 0) {
        perror("setenv failed");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        printf("Parent process (PID: %d) created child process (PID: %d)\n", getpid(), pid);
        printf("Parent process is waiting for the child to complete...\n");

        int status;
        waitpid(pid, &status, 0);

        printf("Parent process: Child has finished. Parent will now exit.\n");
    } else {
        printf("--> Child process (PID: %d) starting execution.\n", getpid());

        const char *command = getenv(env_name);

        if (command == NULL) {
            fprintf(stderr, "--> Child process: Could not find environment variable '%s'.\n", env_name);
            exit(EXIT_FAILURE);
        }

        printf("--> Child process: Read environment variable: %s = %s\n", env_name, command);
        printf("--> Child process: Will execute command '%s' using execlp()...\n", command);
        printf("--------------------------------------------------\n");

        if (strcmp(command, "ls") == 0) {
            execlp(command, command, "-l", "-h", NULL);
        } else {
            execlp(command, command, NULL);
        }

        perror("execlp failed");
        exit(EXIT_FAILURE);
    }

    return 0;
}