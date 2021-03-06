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
sem_t registration_desk_open;

sem_t queue_lock;
sem_t queue_full;
sem_t queue_empty;
int queue[NUM_NURSES];
int next_nurse_id = 0;
int next_free_space = 0;


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


  while(1) {
      
    // Walk to vaccine
    walk(1, 3);

    // check if no more vials, if not exit clinic

    fprintf(stderr, "%s: nurse %ld is waiting for vaccine storage room to be clear\n", curr_time_s(), id);
    sem_wait(&vaccine_storage);

    if (vials_left == 0) {
      fprintf(stderr, "%s: nurse %ld realizes there are no more vaccines left, and goes home to party\n", curr_time_s(), id);
      sem_post(&vaccine_storage);
      pthread_exit(NULL);
    } else {
      fprintf(stderr, "%s: nurse %ld takes 1 vial, leaving %d vials left\n", curr_time_s(), id, vials_left);
      vials_left = vials_left - 1;
    };
    
    sem_post(&vaccine_storage);

    // walk back
    fprintf(stderr, "%s: nurse %ld walks back from the vaccine storage room to the vaccination room\n", curr_time_s(), id);
    walk(1, 3);

    for (int i = 0; i < 6; i++) {

      // produce on buffer
      sem_wait(&queue_empty);

      sem_wait(&queue_lock);

      fprintf(stderr, "%s: nurse %ld writes her name down for next person to get in line\n", curr_time_s(), id);
      queue[next_free_space] = id;
      next_free_space = (next_free_space + 1) % NUM_NURSES;
      
      sem_post(&queue_lock);
      sem_post(&queue_empty);
      sem_post(&queue_full);      
      
      // wait for client to be ready
      fprintf(stderr, "%s: nurse %ld waits for client to be ready\n", curr_time_s(), id);
      sem_wait(&client_ready);

      // tell client we are ready
      fprintf(stderr, "%s: nurse %ld informs client nurse is ready for vaccinating\n", curr_time_s(), id);
      sem_post(&nurse_ready);

      //give vaccine
      fprintf(stderr, "%s: nurse %ld begins vaccination\n", curr_time_s(), id);
      //usleep(5*1000000);
    }

  }
    
  fprintf(stderr, "%s: nurse %ld is done\n", curr_time_s(), id);

  pthread_exit(NULL);
}

void *client(void *arg) {
  long int id = (long int)arg;

  fprintf(stderr, "%s: client %ld has arrived and is walking to register\n",
	  curr_time_s(), id);

  // walks to registration desk
  walk(3, 10);

  // waits in line to get to registration desk
  sem_wait(&registration_desk_open);
    
  // registers
  walk(3, 10);

  sem_post(&registration_desk_open); // leave registration desk open
    
  // walk to station-assignment queue
  walk(3, 10);

  // wait for station assignment
  sem_wait(&queue_full);
  sem_wait(&queue_lock);

  long int nurse_id = queue[next_nurse_id];
  next_nurse_id = (next_nurse_id + 1) % NUM_NURSES;
  
  fprintf(stderr, "%s: client %ld gets vaccine from nurse %ld\n", curr_time_s(), id, nurse_id);
		       
  sem_post(&queue_lock);
  sem_post(&queue_empty);
    
  // walk to nurse's station
  walk(1, 2);
    
  // inform nurse you are ready for vaccine
  fprintf(stderr, "%s: client %ld informs nurse %ld he/she is ready to take the vaccine\n", curr_time_s(), id, nurse_id);
  sem_post(&client_ready);

  // wait for nurse to give vaccine
  fprintf(stderr, "%s: client %ld waits on nurse %ld for vaccine...\n", curr_time_s(), id, nurse_id);
  sem_wait(&nurse_ready);

  // leave vaccine
  fprintf(stderr, "%s: client %ld leaves the clinic!\n", curr_time_s(), id);

  pthread_exit(NULL);
}

int main() {
  srand(time(0));

  sem_init(&queue_lock, 1, 1);
  sem_init(&queue_full, 1, 0);
  sem_init(&queue_empty, 1, NUM_NURSES);
	   
  sem_init(&vaccine_storage, 1, 1); /* vaccines start as available */
  sem_init(&client_ready, 1, 0);
  sem_init(&nurse_ready, 1, 0);
  sem_init(&registration_desk_open, 1, 4);

  pthread_t nurse_threads[NUM_NURSES];
  pthread_t client_threads[NUM_CLIENTS];
  
  for (int i = 0; i < NUM_NURSES; i++) {
    int nurse_t = pthread_create(&nurse_threads[i], NULL, nurse, (void *) (long int) i);

    if (nurse_t == 0) {
      fprintf(stderr, "Created nurse %d\n", i);
    }
    
  }
  
  for (int i = 0; i < NUM_CLIENTS; i++) {
    //usleep(get_rand_in_range(0, 1));
    int client_t = pthread_create(&client_threads[i], NULL, client, (void *) (long int) i);

    if (client_t == 0) {
      fprintf(stderr, "Created client %d\n", i);
    }
  }
  


  pthread_exit(0);
}
