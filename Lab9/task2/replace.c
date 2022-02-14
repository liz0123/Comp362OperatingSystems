/**
* Name: Isabel Valdez
* Lab/task: Lab 9 Task 2
* Date: 03/02/18
**/
#include "replace.h"
#include <time.h>

int main(int argc, char *argv[])
{
	int sizeOfRefString;
	if (argc < 4)
		oops("Usage:\n   replace <capacity> -s <reference string> \n    replace <capacity> < length of ref string > <value range>\n", 1);
	
	int numOfFrames = atoi(argv[1]);
	
	if (argv[2][0] == '-')
		sizeOfRefString = argc - 3; // prog name + num of frames + '-s'
	else
		sizeOfRefString = atoi(argv[2]);
	
	int *referenceString = calloc(sizeOfRefString, sizeof(int));
	
	if (argv[2][0] == '-')
		for (int i = 3; i < argc; i++) {
			referenceString[i - 3] = atoi(argv[i]);
		}
	else {
		int range = atoi(argv[3]);
		
		// create a random page reference sequence from [0, range-1]
		srand((unsigned int)time(NULL));
		for (int i = 0; i < sizeOfRefString; i++)
			referenceString[i] = rand() % range;
	}
	
	printf("REFERENCE STRING:\n{");
	for (int i = 0; i < sizeOfRefString; i++)
		printf("%d ", referenceString[i]);
	printf("}\n");
	
	// use the LRU replacement policy to count page faults for the sequence 
	int numOfFaults = testLRU(numOfFrames, referenceString, sizeOfRefString);
	printf("\nNumber of page faults using LRU: %d\n", numOfFaults);
	
	free(referenceString);
}