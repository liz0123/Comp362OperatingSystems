/**
* Name: Isabel Valdez
* Lab/task: Lab 6 Task 3
* Date: 03/01/18
**/
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#define DEFUALT_NUM_OF_SEATS 5
#define DEFUALT_NUM_OF_TURNS 4
#define DELAY ( (rand() % 5 + 1) * 1000)

enum {THINKING, HUNGRY, EATING} states[5];
pthread_cond_t *self;
pthread_mutex_t table;

int isEating(int philosopher);
int getLeft(int philosopher);
int getRight(int philosopher);
void tryToEat(int philosopher);
void tryToPickup(int philosopher);
void putDownChopsticks(int philosopher);
void initializationCode();
void *philosopher(void *philosopherIndex);

int main()
{
  initializationCode();
  self = calloc(DEFUALT_NUM_OF_SEATS, sizeof(pthread_cond_t));

  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
 
  printf ("Start a dinner for %d diners\n", DEFUALT_NUM_OF_SEATS);
  
  pthread_t philoshopher_tid[DEFUALT_NUM_OF_SEATS];

  pthread_mutex_init(&table, NULL);
  long i;
  for(i = 0; i < DEFUALT_NUM_OF_SEATS; i++){
    pthread_cond_init(&self[i], NULL);
  }
  for(i = 0; i < DEFUALT_NUM_OF_SEATS; i++){
    pthread_create(&philoshopher_tid[i], NULL, philosopher, (void *) i);
  }
  for(i = 0; i < DEFUALT_NUM_OF_SEATS; i++){
    pthread_join(philoshopher_tid[i], NULL);
  }
  for(i = 0; i < DEFUALT_NUM_OF_SEATS; i++){
    pthread_cond_destroy(&self[i]);
  }
  pthread_mutex_destroy(&table);

  
  return 0;
}
int isEating(int philosopher){
  if(states[philosopher] == EATING){
    //printf ("Philsopher no. %d is eating\n", philosopher);
  }
  return states[philosopher] == EATING;
}

int getLeft(int philosopher){
  return ( philosopher + 4 ) % DEFUALT_NUM_OF_SEATS;
}
int getRight(int philosopher){
  return ( philosopher + 1 ) % DEFUALT_NUM_OF_SEATS;
}

void tryToEat(int philosopher){
  printf ("Philsopher no. %d trys to eat\n", philosopher);
  int left = getLeft(philosopher);
  int right = getRight(philosopher);

  if(states[philosopher] == HUNGRY && (!isEating(left)) && (!isEating(right))){
    states[philosopher] = EATING;
    printf ("Philsopher no. %d is eating\n", philosopher);
    pthread_cond_signal(&self[philosopher]);
  }
}
void tryToPickup(int philosopher){
   printf ("Philsopher no. %d trys to pick up chopsticks\n", philosopher);
   pthread_mutex_lock(&table);

   states[philosopher] = HUNGRY;
  
   tryToEat(philosopher);

   if(!isEating(philosopher)){
    pthread_cond_wait(&self[philosopher], &table);
   }

   pthread_mutex_unlock(&table);
}
void putDownChopsticks(int philosopher){
printf ("Philsopher no. %d puts down chopsticks.\n", philosopher);
  pthread_mutex_lock(&table);

  states[philosopher] = THINKING;
  int left = getLeft(philosopher);
  int right = getRight(philosopher);
  tryToEat(left);
  tryToEat(right);

  pthread_mutex_unlock(&table);
}
void initializationCode(){
  for(int i = 0; i < 5; i++){
    states[i] = THINKING;
  }
}
void *philosopher(void *philosopherIndex){
  int id = (long)philosopherIndex;
  printf ("Philsopher no. %d sits at the table.\n", id);
  for(int i = 0; i < DEFUALT_NUM_OF_TURNS; i++){
    usleep (DELAY);
    tryToPickup( id);
    usleep (DELAY * 2);
    putDownChopsticks(id);
    printf ("Philsopher no. %d is done eating.\n", id);
  }
  pthread_exit(NULL);

}















