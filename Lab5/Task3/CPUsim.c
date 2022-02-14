/**
* Name: Isabel Liz Valdez
* Lab/task: Lab 5 Task 3
* Date: 02/25/18
**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_NUM_OF_PROCESS 100
enum events{ END_PROCESS, NEW_PROCESS};

int process[MAX_NUM_OF_PROCESS];
int full_quantum;
int remaining_quantum= MAX_NUM_OF_PROCESS;
int (*scheduler)(int);
char *type;
int rr(int current_process);
int srtf(int current_process);
int sjf(int current_process);
int fcfs(int current_process);
int work_remains();
void set_scheduling_algorithm();
void simulation();
void dispaly_CPU( int current_time, int current_processs, int scan_index);
int count_waiting_process(int current_process, int scan_index);
int check_for_event(int current_process, int current_time, int next_incoming_process_time);


int main(int argc, char **argv){

	set_scheduling_algorithm();
	simulation();
	
	
	
}
void set_scheduling_algorithm(){
	type = malloc(sizeof(char)* MAX_NUM_OF_PROCESS); // How should I malloc
	scanf("%s", type);

	if(strcmp(type,"RR")==0){
		printf("\nScheduler RR\n");
		scanf("%d",&full_quantum);
		remaining_quantum = full_quantum;
		scheduler = &rr;
	
	}
	else{
		if(strcmp(type, "FCFS") == 0){
			printf("\nScheduler FCFS\n");
			scheduler = &fcfs;
		}
		else if(strcmp(type, "SJF") == 0){
			printf("\nScheduler SJF\n");
			scheduler = &sjf;
		}
		else if(strcmp(type, "SRTF") == 0){
			printf("\nScheduler SRTF\n");
			scheduler = &srtf;
		}
		else{
			printf("Not a type < %s >\n",type );
			exit(0);
		}
	}

}
int rr(int current){
	int next = 0;
	int result = current;
	remaining_quantum --;

	 if(remaining_quantum == 0){
	 	next = 2;
	 }
	 else if(process[current] == 0){
	 	next = 2;
	 	remaining_quantum = full_quantum;
	 }

	 int index = current;
	 while( next > 0){
	 	index++;
	 	if( process[index]>0){
 			result = index;
 			next = 0;
 			break;
	 	}
	 	else if( index == MAX_NUM_OF_PROCESS){
	 		printf("wererereerere\n");
	 		index = -1;
	 		next --;
	 	} 	
	 }
	 return result;
}
int srtf(int current){
	int min;
	int result = current;
	min = process[current];
		for(int index = 0; index < MAX_NUM_OF_PROCESS; index++){
				if(process[index] > 0 && process[index]< min){
					min = process[index];
					result = index;
				}
			}


	return result;
}
int sjf(int current){
	int min;
	int result = current;

	if(process[current] == 0){
		min = process[current];
		for(int index = 0; index < MAX_NUM_OF_PROCESS; index++){
				if(process[index] > 0 && process[index]< min){
					printf("min %d vs p[%d]\n",min, process[index] );
					min = process[index];
					result = index;
				}
			}
	}
	return result;
}
int fcfs(int current){
	int result = current;
	if(process[current] == 0){
		for(int index = 0; index < MAX_NUM_OF_PROCESS; index++){
			if(current != index && process[index] > 0){
				result = index;
				break;
			}
		}
	}

	return result;
}
int work_remains(){
	int result = 1;
	for(int index =0; index < MAX_NUM_OF_PROCESS; index++){
	
		if(process[index] == -1){
		result = 0;
		break;
		}
	}
	return result;
}
int count_waiting_process(int current_process, int scan_index){
	
	return (scan_index- process[current_process]- current_process );
}
void simulation(){
	for(int i = 0; i< MAX_NUM_OF_PROCESS; i++){
		process[i] = -2;
	}
	int clock = 0;
	int timeWaited = 0;
	int currentProcess,newProcess,check;
	int nextProcess, nextBurst= 0;

	scanf("%d", &currentProcess);
	nextProcess = currentProcess;
	while( work_remains() == 1 ){
		check = check_for_event(currentProcess, clock, nextProcess);

		if(check == NEW_PROCESS){
			scanf("%d", &nextBurst);
			process[nextProcess] = nextBurst;
			if(strcmp(type, "SRTF") == 0){
			currentProcess = scheduler(currentProcess);
			}

			dispaly_CPU(clock, currentProcess, nextProcess);
			scanf("%d", &nextProcess);
		}
		else if( check == END_PROCESS){
			currentProcess = scheduler(currentProcess);
			dispaly_CPU(clock, currentProcess, nextProcess);
		}
		newProcess = scheduler(currentProcess);
		timeWaited += count_waiting_process(currentProcess, clock);
		process[currentProcess] --;
		clock++;
		currentProcess = newProcess;

		if( remaining_quantum == 0){
			remaining_quantum = full_quantum;
			dispaly_CPU(clock, currentProcess, nextProcess);
		}
	}
	//dispaly_CPU(clock, currentProcess, nextProcess);
	printf("Average Time Waited: %d\n", timeWaited );

}
void dispaly_CPU( int current_time, int current_process, int scan_index){
	printf("\n");
	printf("T %d:\nCPU: %d\nqueue:\n",current_time, process[current_process]);
	for(int i =0; i<=scan_index; i++){
		if(process[i]>0 && i != current_process)
		printf("process[%d] = %d\n",i ,process[i]);
	}

}
int check_for_event(int current_process, int current_time, int next_incoming_process_time){
	int check = -1;
	if(process[current_process] == 0){
		check = END_PROCESS;
	}
	else if( current_time == next_incoming_process_time){
		check = NEW_PROCESS;
	}
	
	return check;
}











