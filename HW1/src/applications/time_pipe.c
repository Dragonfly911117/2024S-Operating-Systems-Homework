#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int pipefd[2];
    pid_t pid;
    int status;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command>\n", argv[0]);
        exit(1);
    }

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }

    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        clock_t start;
        // child process
        close(pipefd[0]);
        start = time(NULL);
        write(pipefd[1], &start, sizeof(start));
        close(pipefd[1]);
        execvp(argv[1], &argv[1]);
        perror("exec");
        exit(1);
    } else {
        // parent process
        clock_t start, end;
        close(pipefd[1]);
        wait(&status);
        read(pipefd[0], &start, sizeof(start));
        close(pipefd[0]);
        end = time(NULL);
        printf("Elapsed time: %ld s\n", (end - start));
    }

    return 0;
}
