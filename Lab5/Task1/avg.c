/**
* Name: Isabel Liz Valdez
* Lab/task: Lab 5 Task 1
* Date: 02/25/18
**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(int argc, char *argv){
	float alpha, next,current, previous=0.0;


	printf("Please enter alpha value (Enter -1 to exit)\n");
	scanf("%f", &alpha);
	if (alpha >1 || alpha < 0){
		printf("Alpha should be between 1 and 0\n");
		exit(0);
	}

	int index = 0;
	scanf("%f", &current);
	previous = current;

	while(current != -1){
		
		printf("Burstd %d is: %0.2f\n", index, current );
		next = (alpha * current) + (previous *(1 - alpha));
		printf("Tau %d is: %0.2f\n", index, next );
		
		previous = next;
		scanf("%f", &current);
		index++;
	}

}