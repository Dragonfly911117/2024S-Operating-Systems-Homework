#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    clock_t start, end;
    pid_t pid;
    int status;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command>\n", argv[0]);
        exit(1);
    }

    // fork a child process
    start = time(NULL);
    pid = fork();

    if (pid == 0) { // inside the child process
        execvp(argv[1], &argv[1]);
        status = 0;
    } else if (pid < 0) {
        perror("fork");
        exit(1);
    } else { // inside the child process
        wait(&status);
        end = time(NULL);
        printf("Elapsed time: %ld s\n", (end - start));
    }
    return 0;
}
