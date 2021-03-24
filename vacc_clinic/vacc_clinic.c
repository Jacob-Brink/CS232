/*
 * Your info here.
 */

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define NUM_VIALS 30
#define SHOTS_PER_VIAL 6
#define NUM_CLIENTS (NUM_VIALS * SHOTS_PER_VIAL)
#define NUM_NURSES 10
#define NUM_STATIONS NUM_NURSES
#define NUM_REGISTRATIONS_SIMULTANEOUSLY 4

/* global variables */
sem_t nurse_ready;
sem_t client_ready;
sem_t vaccine_storage;

int vials_left = NUM_VIALS;

int get_rand_in_range(int lower, int upper) {
    return (rand() % (upper - lower + 1)) + lower;
}

char *time_str;
char *curr_time_s() {
    time_t t;
    time(&t);
    time_str = ctime(&t);
    // replace ending newline with end-of-string.
    time_str[strlen(time_str) - 1] = '\0';
    return time_str;
}

// lower and upper are in seconds.
void walk(int lower, int upper) {
    // TODO: fill in code here.  Use usleep() and get_rand_in_range() from
    // above.
    usleep(get_rand_in_range(lower, upper)*1000000);
}

// arg is the nurses station number.
void *nurse(void *arg) {
    long int id = (long int)arg;

    fprintf(stderr, "%s: nurse %ld started\n", curr_time_s(), id);

    // Walk to vaccine
    walk(3, 10);

    // check if no more vials, if not exit clinic
    sem_wait(&vaccine_storage);
    if (vials_left == 0) {
      fprintf(stderr, "%s: nurse %ld realizes there are no more vaccines left, and goes home to party\n", curr_time_s(), id);
      pthread_exit(NULL);
    };
    sem_post(&vaccine_storage);
    
    sem_wait(&client_ready);
    sem_post(&nurse_ready);
    
    fprintf(stderr, "%s: nurse %ld is done\n", curr_time_s(), id);

    pthread_exit(NULL);
}

void *client(void *arg) {
    long int id = (long int)arg;

    fprintf(stderr, "%s: client %ld has arrived and is walking to register\n",
            curr_time_s(), id);

    walk(3, 10);
    
    sem_post(&client_ready);
    sem_wait(&nurse_ready);
    
    fprintf(stderr, "%s: client %ld leaves the clinic!\n", curr_time_s(), id);

    pthread_exit(NULL);
}

int main() {
    srand(time(0));

    sem_init(&vaccine_storage, 1, 1); /* vaccines start as available */
    sem_init(&client_ready, 1, 0);
    sem_init(&nurse_ready, 1, 0);
    
    pthread_t client_thread_id;

    int client_t = pthread_create(&client_thread_id, NULL, client, NULL);

    if (client_t == 0) {
      /* fprintf(stderr, "Success!"); */
    }


    pthread_t nurse_thread_id;

    int nurse_t = pthread_create(&nurse_thread_id, NULL, nurse, NULL);

    if (nurse_t == 0) {
    	/* fprintf(stderr, "Success! A nurse has been born to us in a lowly manger"); */
    }


    pthread_exit(0);
}
