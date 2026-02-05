#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    else if (pid == 0) {
        printf("Child process running 'ls'...\n");
        execl("/bin/ls", "ls", "-l", (char *)0);
        perror("execl failed");
        exit(1);
    }
    else {
        printf("Parent process waiting for child...\n");
        wait(NULL);
        printf("Child finished.\n");
    }

    return 0;
}

