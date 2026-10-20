#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define NUM_CHAIRS 3
#define NUM_CUSTOMERS 10

sem_t customers;
sem_t barber;
pthread_mutex_t mutex;

int waiting = 0;
int customers_served = 0;

void* barber_thread(void* arg) {
    while (1) {
        sem_wait(&customers); 

        pthread_mutex_lock(&mutex);
        waiting--;
        sem_post(&barber); 
        pthread_mutex_unlock(&mutex);

        printf("Barber: cutting hair...\n");
        usleep(rand() % 100000); 
        
        pthread_mutex_lock(&mutex);
        customers_served++;
        if (customers_served >= NUM_CUSTOMERS) {
            pthread_mutex_unlock(&mutex);
            break;
        }
        pthread_mutex_unlock(&mutex);
    }
    printf("Barber shop is closing for the day.\n");
    return NULL;
}

void* customer_thread(void* arg) {
    int id = *((int*)arg);
    usleep(rand() % 200000); 
    pthread_mutex_lock(&mutex);
    if (waiting < NUM_CHAIRS) {
        waiting++;
        printf("Customer %d arrived and sat in the waiting room. (Waiting: %d)\n", id, waiting);
        sem_post(&customers);
        pthread_mutex_unlock(&mutex);

        sem_wait(&barber);
        printf("Customer %d is getting a haircut.\n", id);
    } else {
        pthread_mutex_unlock(&mutex);
        printf("Customer %d found no empty chairs and left the shop.\n", id);
    }
    return NULL;
}

int main() {
    pthread_t b_thread;
    pthread_t c_threads[NUM_CUSTOMERS];
    int c_ids[NUM_CUSTOMERS];

    srand(time(NULL));

    pthread_mutex_init(&mutex, NULL);
    sem_init(&customers, 0, 0);
    sem_init(&barber, 0, 0);

    pthread_create(&b_thread, NULL, barber_thread, NULL);

    for (int i = 0; i < NUM_CUSTOMERS; i++) {
        c_ids[i] = i + 1;
        pthread_create(&c_threads[i], NULL, customer_thread, &c_ids[i]);
    }

    for (int i = 0; i < NUM_CUSTOMERS; i++) {
        pthread_join(c_threads[i], NULL);
    }

    pthread_join(b_thread, NULL);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&customers);
    sem_destroy(&barber);

    return 0;
}