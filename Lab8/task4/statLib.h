/**
* Name: Isabel Liz Valdez
* Lab/task: Lab 8 Task 3
* Date: 03/15/18
**/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <dlfcn.h>


typedef struct data
{
	int pid;
	int page;
	long timeStamp;
	
}DATA;

typedef struct invTablePage
{
	int pageSize;
	int memSize;
	int frameSize;
	DATA* table;
	
}INV_TABLE_PAGE;
