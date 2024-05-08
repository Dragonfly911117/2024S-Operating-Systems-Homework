#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/random.h>


pthread_mutex_t mutex;
int total = 0;
int inside = 0;
#define MAX 21

extern int isInsideCircle(double x, double y);
inline int isInsideCircle(double x, double y) {
        return x * x + y * y <= 1;
}

void* worker(void* para) {
    double x = (double) (random() % MAX) / 10 - 1;
    double y = (double) (random() % MAX) / 10 - 1;
    int flag = isInsideCircle(x, y);
    printf("x: %f, y: %f, flag: %d\n", x, y, flag);
    pthread_mutex_lock(&mutex);
    total += 1;
    inside += flag;
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main(int argc, char* argv[]) {
    long int n;
    if (argc != 2) {
        printf("You didn't pass the number of points as argument, Please enter one now:\n");
        char input[10];
        fgets(input, 10, stdin);
        n = abs(strtol(input, NULL, 10));
    } else {
        n = strtol(argv[1], NULL, 10);
    }
    srandom(time(NULL));
    pthread_t threads[n];

    for (int i = 0; i < n; i++) {
        pthread_create(&threads[i], NULL, worker, NULL);
    }
    for (int i = 0; i < n; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("Pi is approximately: %f\n", 4.0 * inside / total);
    return 0;
}