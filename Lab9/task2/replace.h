/**
* Name: Isabel Valdez
* Lab/task: Lab 9 Task 2
* Date: 03/02/18
**/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define oops(msg, errcode) { perror(msg); exit(errcode); }
typedef struct node{
	int data;
	struct node* prev;
	struct node* next;
}NODE;

 int testLRU(int, int[], int);



