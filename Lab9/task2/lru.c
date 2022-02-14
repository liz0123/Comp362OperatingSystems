/**
* Name: Isabel Valdez
* Lab/task: Lab 9 Task 2
* Date: 03/02/18
**/
#include "replace.h"

int* referenceString;
int sizeOfRefString;
int capacity;
int numOfFaults = 0;


void printList(NODE *node)
{
    NODE *last;
    //printf("\nTraversal in forward direction \n");
    
     while (node != NULL)
    {
        printf(" %d ", node->data);
        last = node;
        node = node->next;
    }
    printf("\n");
}
void push(NODE **head_ref, int new_data)
{
	NODE * new_node = (NODE*)malloc(sizeof(NODE));

	new_node->data = new_data;

	new_node->next = (*head_ref);
	new_node->prev = NULL;

	if((*head_ref) != NULL){
		(*head_ref)->prev = new_node;
	}
	(*head_ref) = new_node;
}
void deleteNode(NODE** head_ref, NODE *del){
	if(*head_ref == NULL || del == NULL)
    return;

	if(*head_ref == del)
    *head_ref = del->next;

	 if(del->next != NULL)
    del->next->prev = del->prev;
	
	if(del->prev != NULL)
    del->prev->next = del->next;

	free(del);
  return;


}
void deleteNodeAtGivenPos(NODE** head_ref, int n)
{
    /* if list in NULL or invalid position is given */
    if (*head_ref == NULL || n < 0)
        return;
 
    NODE* current = *head_ref;
    int i;
 
    /* traverse up to the node at position 'n' from
       the beginning */
    for (int i = 0;  i < n; i++){
        current = current->next;
    }
 
    /* if 'n' is greater than the number of nodes
       in the doubly linked list */
    if (current == NULL)
        return;
 
    /* delete the node pointed to by 'current' */
    deleteNode(head_ref, current);
}
int searchNodes(NODE** head_ref, int searchValue){
	NODE* current = *head_ref;
	int i = 0;
	while(current != NULL){
		if( current->data == searchValue){
			return i;
		}
		i++;
		current = current->next;
	
	}
	return -1;

}
int findLRUmax(int* time ){
    int i, minimum = time[0], pos = 0;
 
    for(i = 0; i < capacity; ++i){
        if(time[i] == -1){
        	return i;
        }
        else if(time[i] > minimum){
            minimum = time[i];
            pos = i;
        }
    }
    
    return pos;
}
int findLRU(NODE** head_ref , int index){
	int* time = calloc(capacity, sizeof(int));
	NODE* current = *head_ref;
	int counter;
	int stop;
	for(int j = 0; j < capacity; ++j){
		time[j] = -1;
		stop = 1;
		counter = 1;;
		for(int i = index -1 ; stop && i >= 0 ; --i){
			if(current->data == referenceString[i]){
				time[j] = counter;
				stop = 0;
			}
			counter++;
		}
		current = current->next;
	}

	return findLRUmax(time);
}
int testLRU(int numOfFramesInput, int* referenceStringInput, int sizeOfRefStringInput){	
	sizeOfRefString = sizeOfRefStringInput;
	referenceString = referenceStringInput;
	capacity = numOfFramesInput;


	NODE *head = NULL;
	for(int i = 0; i < sizeOfRefString; ++i){
		if(searchNodes(&head,referenceString[i]) > -1){
			deleteNodeAtGivenPos(&head, searchNodes(&head,referenceString[i]));
			printf("->");		
		}
		else if(i < capacity){
			printf( " *");
			numOfFaults++;
		}
		else{
			int n = findLRU(&head, i);
			deleteNodeAtGivenPos(&head, n);
			numOfFaults++;
			printf(" *");
		}
		push(&head, referenceString[i]);
		printList(head);

	}
		
	return numOfFaults;
}
 