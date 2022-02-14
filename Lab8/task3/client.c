
/**
* Name: Isabel Liz Valdez
* Lab/task: Lab 8 Task 3
* Date: 03/15/18
**/
#include "statLib.h"

extern struct invTablePage initInverted(struct invTablePage *invTable, int memSize, int frameSize);
extern int translate(struct invTablePage *invTable, int pid, int page, int offset);
extern int releaseInverted(struct invTablePage *invTable);
extern void displayTable (struct invTablePage invTable); 

void displayTable (struct invTablePage invTable);

int main(int argc, char ** argv){
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

}
