/**
* Name: Isabel Liz Valdez
* Lab/task: Lab 5 Task 2
* Date: 02/25/18
**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#define MAX_RUN 1000
#define size 50


typedef enum {
PRIORITY_HIGH = 99,
PRIORITY_MEDIUM = 50,
PRIORITY_LOW = 1
} PRIORITY;

/**	
pthread_t tid;
pthread_attr_t attr;

// get the default attributes
pthread_attr_init(&attr);

// specialize attributes
struct sched_param schedparam;
schedparam.sched_priority = PRIORITY;

pthread_attr_setscope(&attr, PTHREAD_SCOPE_PROCESS);
pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
pthread_attr_setschedpolicy(&attr, SCHED_RR);
pthread_attr_setschedparam(&attr, &schedparam);
pthread_create(&tid, &attr, &runner, &argv);
pthread_join(tid, NULL);
pthread_attr_destroy(&attr);
**/
void *runner (void *thread_parameter);

int main(int argc, char **argv){
	//pthread_t rr;
	pthread_attr_t rr;
	pthread_attr_init(&rr);
	struct sched_param RRsched;
	RRsched.sched_priority = PRIORITY_HIGH;
	pthread_attr_setscope(&rr, PTHREAD_SCOPE_PROCESS);
	pthread_attr_setinheritsched(&rr, PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setschedpolicy(&rr, SCHED_RR);
	pthread_attr_setschedparam(&rr, &RRsched);

	//pthread_t FCFS;
	pthread_attr_t FCFS;
	pthread_attr_init(&FCFS);
	struct sched_param FCFSsched;
	FCFSsched.sched_priority = PRIORITY_MEDIUM;
	pthread_attr_setscope(&FCFS, PTHREAD_SCOPE_PROCESS);
	pthread_attr_setinheritsched(&FCFS, PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setschedpolicy(&FCFS, SCHED_RR);
	pthread_attr_setschedparam(&FCFS, &FCFSsched);


	//pthread_t OTHER;
	pthread_attr_t OTHER;
	pthread_attr_init(&OTHER);
	struct sched_param OTHERsched;
	OTHERsched.sched_priority = PRIORITY_LOW;
	pthread_attr_setscope(&OTHER, PTHREAD_SCOPE_PROCESS);
	pthread_attr_setinheritsched(&OTHER, PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setschedpolicy(&OTHER, SCHED_RR);
	pthread_attr_setschedparam(&OTHER, &OTHERsched);


	pthread_t rrThread[size];
	pthread_t FCFSthread[size];
	pthread_t OTHERthread[size];

	for(int index = 0; index < size; index++){
		pthread_create(&rrThread[index], &rr, &runner, (void *)"HIGH");
		pthread_create(&FCFSthread[index], &FCFS, &runner, (void *)"MEDIUM");
		pthread_create(&OTHERthread[index], &OTHER, &runner, (void *)"LOW");
	}

	while(getchar() != 'q'){
		sleep(1);
	}
	exit(0);
}

void *runner(void *thread){
	char *data = (char *)thread;
	for(int i = 0; i < MAX_RUN; i++){
	}
	printf("Date: %lu rating: %s\n",pthread_self(), data );
	pthread_exit(0);
}















