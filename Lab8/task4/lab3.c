
/**
* Name: Isabel Liz Valdez
* Lab/task: Lab 8 Task 3
* Date: 03/15/18
**/
#include "statLib.h"

void displayTable (struct invTablePage invTable){
	printf("%20s","pid");
	printf("%20s", "page");
	printf("%20s", "time stamp");
	printf("\n");
	for(int i = 0; i <invTable.pageSize; ++i){
		printf("%20d",invTable.table[i].pid);
		printf("%20d",invTable.table[i].page);
		printf("%20ld",invTable.table[i].timeStamp);
		printf("\n");
	}
}
int searchInvTable(struct invTablePage *invTable,int pid, int page){
	int result = -1;
	
	for(int i = 0; i < invTable->pageSize; ++i){
		if(invTable->table[i].pid == pid && invTable->table[i].page == page){
			return i;
		}
	}
	
	return result;
}
int getOldestTime( struct invTablePage  invTable){
	int index =0;
	long oldestTime = invTable.table[0].timeStamp;

	for(int i = 1; i < invTable.pageSize; ++i){
		if(oldestTime > invTable.table[i].timeStamp){
			oldestTime = invTable.table[i].timeStamp;
			index = i;
		}
	}
	return index;
}
int translate(struct invTablePage *invTable, int pid, int page, int offset){ 
/* 
* translates a logical address <pid, page, offset> into a physical address 
* if the address is invlid it returns -1 
* if there is no entry for the pid and the page number in the table, it has to be added 
* if there is no room in the table for the new entry, then the oldest entry has to be removed 
*/
	int frameIndex = searchInvTable(invTable, pid, page);
	if(frameIndex < 0){
	
		struct timeval currentTime;
		gettimeofday(&currentTime, NULL);
		frameIndex = searchInvTable(invTable, 0, 0);

		if(frameIndex < 0){
			frameIndex = getOldestTime(*invTable);
		}
		invTable->table[frameIndex].pid = pid;
		invTable->table[frameIndex].page = page;
		invTable->table[frameIndex].timeStamp = currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
		 
		 displayTable(*invTable);		
	}
	return frameIndex;
}
struct invTablePage initInverted(struct invTablePage *invTable, int memSize, int frameSize){ 
/* 
* allocates and initializes the table for the given sizes of the memory and frame 
* to ensure that the library is thread-safe, the table should be a struct that 
* includes metadata such as page size and the number of pages along the translation 
* table (that can be a 2-dimensional array, or a one-dimensional array of structs) 
*/
	// initulize invTablePage
	//invTable = malloc(sizeof(struct invTablePage*));
	invTable->memSize = memSize;
	invTable->frameSize = frameSize;
	invTable->pageSize = memSize / frameSize;
	// initualize table in invTablePage

	invTable->table = malloc(sizeof(DATA) * invTable->pageSize);
	struct timeval currentTime;
	srand(time(NULL));
	for( int i = 0; i < invTable->pageSize; ++i){
		invTable->table[i].pid = rand()%3;
		
		if(invTable->table[i].pid == 0){
			invTable->table[i].page = 0;
			invTable->table[i].timeStamp = 0;
		}
		else{
			invTable->table[i].page = (rand()%3)+6;
			gettimeofday(&currentTime, NULL);
			invTable->table[i].timeStamp = currentTime.tv_sec * (int)1e6 + currentTime.tv_usec + rand()%100;
		}
	}
	return *invTable;
	
	
}
void releaseInverted(struct invTablePage *invTable){
/* 
* releases the inverted table and sets the reference to NULL 
*/
	free(invTable->table);
}
int lab3(){
	int num1, num2, offset, frameIndex;
	char stop[2] ;
	struct invTablePage invTable;

	printf("Enter memory size: ");
	scanf("%d", &num1);
	printf("Enter frame size: ");	
	scanf("%d", &num2);
	invTable = initInverted(&invTable, num1, num2);
	displayTable(invTable);

	do{
		// get address
		printf("Enter < pid page offset > : ");
		scanf("%d %d %d", &num1, &num2, &offset);
		frameIndex = translate(&invTable, num1, num2, offset);
		printf("Index of frame returned is %d\n", frameIndex);
		printf("Physical Address: %d\n", ((frameIndex * invTable.pageSize) + offset));
		printf("\n");
		//
		printf("Would you like to continue? (yes/no): ");
		scanf("%s", stop);

	}while(strcmp(stop,"no") != 0);
	printf("\n");
	releaseInverted(&invTable);
	return 0;
}






