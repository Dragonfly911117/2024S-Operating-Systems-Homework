/*
 * vars that have have race conditions:
 * - available_resources
 * - count
 *
 *
 * #define MAX_RESOURCES 5
int available_resources = MAX_RESOURCES;
int decrease_count(int count) {
    if (available_resources < count) // Race condition
        return -1;
    else {
        available_resources -= count; // Race condition
        return 0;
    }
}
int increase_count(int count) {
    available_resources += count; // Race condition
    return 0;
}*/

#include <pthread.h>

#define MAX_RESOURCES 5
int available_resources = MAX_RESOURCES;
pthread_mutex_t mutex;

int decrease_count(int count) {
    pthread_mutex_lock(&mutex);
    if (available_resources < count) {
        pthread_mutex_unlock(&mutex);
        return -1;
    } else {
        available_resources -= count;
        pthread_mutex_unlock(&mutex);
        return 0;
    }
}

int increase_count(int count) {
    pthread_mutex_lock(&mutex);
    available_resources += count;
    pthread_mutex_unlock(&mutex);
    return 0;
}
