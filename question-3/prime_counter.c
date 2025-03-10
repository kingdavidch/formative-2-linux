#include <stdio.h>
#include <pthread.h>
#include <math.h>

#define TOTAL_THREADS 20
#define MAX_NUM 10000

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int global_count = 0;

typedef struct {
    int start;
    int end;
} ThreadData;

int is_prime(int n) {
    if (n <= 1) return 0;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

void* count_primes(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    int local_count = 0;
    for (int i = data->start; i < data->end; i++) {
        if (is_prime(i)) local_count++;
    }
    pthread_mutex_lock(&mutex);
    global_count += local_count;
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t threads[TOTAL_THREADS];
    ThreadData thread_data[TOTAL_THREADS];
    int chunk = MAX_NUM / TOTAL_THREADS;

    for (int i = 0; i < TOTAL_THREADS; i++) {
        thread_data[i].start = i * chunk;
        thread_data[i].end = (i == TOTAL_THREADS - 1) ? MAX_NUM : (i + 1) * chunk;
        pthread_create(&threads[i], NULL, count_primes, &thread_data[i]);
    }

    for (int i = 0; i < TOTAL_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Total primes: %d\n", global_count);
    return 0;
}
