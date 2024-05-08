#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <thread_db.h>
#include <sys/random.h>

typedef struct farmer farmer;
pthread_mutex_t bridge;

struct farmer {
    int id;
};

void* north_farmer(void* para) {
    farmer* pFarmer = (farmer*) para;
    while (pthread_mutex_trylock(&bridge) != 0) {
        printf("North farmer %d is waiting\n", pFarmer->id);
        sleep(random() % 3);
    }
    printf("North farmer %d is crossing the bridge\n", pFarmer->id);
    sleep(random() % 3);
    printf("North farmer %d has crossed the bridge\n", pFarmer->id);
    pthread_mutex_unlock(&bridge);

    pthread_exit(NULL);
    return NULL;
}

void* south_farmer(void* para) {
    farmer* pFarmer = (farmer*) para;
    while (pthread_mutex_trylock(&bridge) != 0) {
        printf("South farmer %d is waiting\n", pFarmer->id);
        sleep(random() % 3);
    }
    printf("South farmer %d is crossing the bridge\n", pFarmer->id);
    sleep(random() % 3);
    printf("South farmer %d has crossed the bridge\n", pFarmer->id);
    pthread_mutex_unlock(&bridge);

    pthread_exit(NULL);
    return NULL;
}

int main(int argc, char** argv) {
    pthread_t* north_farmers;
    pthread_t* south_farmers;
    long n;
    long m;
    if (argc != 3) {
        printf("You didn't pass the number of north and south farmers as argument, Please enter them now:\n");
        char input[10];
        fgets(input, 10, stdin);
        n = labs(strtol(input, NULL, 10));
        north_farmers = calloc(n, sizeof(pthread_t));
        fgets(input, 10, stdin);
        m = labs(strtol(input, NULL, 10));
        south_farmers = calloc(m, sizeof(pthread_t));
    } else {
        n = strtol(argv[1], NULL, 10);
        m = strtol(argv[2], NULL, 10);
        north_farmers = calloc(n, sizeof(pthread_t));
        south_farmers = calloc(m, sizeof(pthread_t));
    }
    struct farmer* farmers = calloc(n + m, sizeof(struct farmer));
    srandom(time(NULL));
    pthread_mutex_init(&bridge, NULL);
    for (int i = 0; i < n; i++) {
        farmers[i].id = i;
        pthread_create(&north_farmers[i], NULL, north_farmer, &farmers[i]);
    }
    for (int i = 0; i < m; i++) {
        farmers[i + n].id = i;
        pthread_create(&south_farmers[i], NULL, south_farmer,  &farmers[n+i]);
    }
    for (int i = 0; i < n; i++) {
        pthread_join(north_farmers[i], NULL);
    }
    for (int i = 0; i < m; i++) {
        pthread_join(south_farmers[i], NULL);
    }
    pthread_mutex_destroy(&bridge);
    return 0;
}