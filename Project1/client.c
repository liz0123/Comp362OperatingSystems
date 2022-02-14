/**
* Name: Isabel Valdez
* Lab/task: Project 1 Task 1
* Date: 04/10/18
**/

#include "head.h"

int main(int agrc, char** argv){
	createFileSystem();

	printf("...Creating File 'short.txt'\n");
	createFile("short.txt", 0001);
	printf("...Creating File 'large.txt'\n");
	createFile("large.txt", 0010);
	printf("...Creating Directory with Files 'signIn.txt' and 'signOut.txt'\n");
	createDirectory("dir1", 0011);
	printf("Display Vit Vector: \n");
	displayBit();
	printf("Display memory\n");
	displayMemory();

	 printf("\nDELETE\n");
	 printf("...Deleting File 'large.txt'\n");
	 deleteFile("large.txt", 0010);

	printf("\n" );
	printf("Display Vit Vector: \n");
	displayBit();
	printf("\n");

	 printf("..Deleting Directory : 'dir1'\n");
	deleteDir("dir1", 0011);

	printf("\n" );
	printf("Display Vit Vector: \n");
	displayBit();
	printf("\n");

	printf("...Deleting File 'short.txt'\n");
	deleteFile("short.txt", 0001);

	printf("\n" );
	printf("Display Vit Vector: \n");
	displayBit();
	printf("Display memory\n");
	displayMemory();
	printf("\n");








	///
	// char* input = malloc(sizeof(char)* MAX_MEMORY);
	// mode_t accessRights;

	// do{
	// 	printf("Enter comman: \n");
	// 	scanf("%s",input);

	// 	if(strcmp(input,"file") == 0){
	// 		scanf("%s", input);
	// 		if(strcmp(input,"add") == 0){
	// 			printf("Enter file name: ",input);
	// 			scanf("%s", input);
	// 			printf("Enter access right to file: ");
	// 			scanf("%d", accessRights);
	// 			//
	// 			// opend file()
	// 			// createfile()
	// 			// read();

	// 		}
	// 		else if(strcmp(input,"delect") == 0){

	// 		}

	// 	}
	// 	else if(strcmp(input,"dir") == 0){
	// 		scanf("%s", input);
	// 		if(strcmp(input,"add") == 0){

	// 		}
	// 		else if(strcmp(input,"delect") == 0){

	// 		}

	// 	}
	// 	else{
	// 		printf("Help:\n\tdir add \n\tfile add\n\tdir delete\n\tfile delete");
	// 	}

	// 	printf("Would you like to continue: ");
	// 	scanf("%s",input);
	// }while(strcmp(input,"no") == 0);


	return 0;
}