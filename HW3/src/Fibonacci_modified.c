#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

struct thread_data {
    int n;
    int* dp;
};
int currMax = -1;

#define max(a, b) a > b ? a : b

void* fibonacci(void* arg) {
    struct thread_data* data = (struct thread_data*) arg;
    if (data->dp[data->n] != 0) {
        pthread_exit(NULL);
        return NULL;
    }
    if (data->n < 2) {
        data->dp[data->n] = data->n;
    } else {
        pthread_t thread1;
        pthread_t thread2;
        struct thread_data data1 = {data->n - 1, data->dp};
        struct thread_data data2 = {data->n - 2, data->dp};
        pthread_create(&thread1, NULL, fibonacci, &data1);
        pthread_create(&thread2, NULL, fibonacci, &data2);
        pthread_join(thread1, NULL);
        pthread_join(thread2, NULL);
        data->dp[data->n] = data->dp[data->n - 1] + data->dp[data->n - 2];
    }
    currMax = max(data->n, currMax);
    pthread_exit(NULL);
    return NULL;
}

int main(int argc, char* argv[]) {
    int n;
    if (argc != 2) {
        printf(
                "You didn't pass the target as argument, Please enter one now:\n");
        char input[10];
        fgets(input, 10, stdin);
        n = strtol(input, NULL, 10);
    } else {
        n = strtol(argv[1], NULL, 10);
    }
    if (n < 0) {
        printf("Please enter a positive number.\n");
        return 1;
    }
    pthread_t thread;
    int* dp = calloc(n + 1, sizeof(int));
    struct thread_data data = {n, dp};
    pthread_create(&thread, NULL, fibonacci, &data);

    printf("The sequence is:\n");
    for (int i = 0; i <= n; ++i) {
        while (i > currMax); // spin lock awaiting children to finish
        printf("%d ", dp[i]);
    }
    pthread_join(thread,
                 NULL); // Though this is not necessary as the program's spun till the last child to finish, I kept it for the insurance.
    free(dp);
    return 0;
}
