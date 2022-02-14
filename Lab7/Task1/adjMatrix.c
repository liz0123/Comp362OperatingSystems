
/**
* Name: Isabel Valdez
* Lab/task: Lab 2 Task 3
* Date: 09/17/12
**/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define STRING_MAX_SIZE 50
#define MAX_NUMBER_OF_VERTICES 20

char *vertex_names[MAX_NUMBER_OF_VERTICES];
bool adjacency_matrix[MAX_NUMBER_OF_VERTICES][MAX_NUMBER_OF_VERTICES];
int number_of_vertices = 0;

int get_index_of_vertex(char *vertex_name);
bool is_cycle_Util(int index, bool *visited, bool *recStack);
bool check_existence_of_vertex_name(char *vertex_name);
bool check_for_cycle();
void add_vertex(char *vertex_name);
void add_edge(char *from_vertex_name, char *to_vertex_name);
void remove_edge(char *from_vertex_name, char *to_vertex_name);
void display_adjacency_matrix();
void initializationCode();
void display_help();
void free_names();

int main(int argc, char *argv[])
{
	initializationCode();
	char *input = malloc(sizeof(char*)  * STRING_MAX_SIZE);
	char *from = malloc(sizeof(char*)  * STRING_MAX_SIZE);
	
	do{
		printf("Enter command: ");
		scanf("%s", input);
		if(strcmp(input,"quit") == 0){
		 	printf("program exiting, BYE FELICIA!\n");
		 	//exit(0);
		}
		else if(strcmp(input,"check") == 0){
			if(check_for_cycle()){
				printf(">> DEADLOCK <<\n");
			}
			else{
				printf(">> NO DEADLOCK <<\n");
			}
		}
		else if(strcmp(input,"display") == 0){
			display_adjacency_matrix();
		}
		else if(strcmp(input,"remove") == 0){
			scanf("%s", input);
			if(strcmp(input, "edge") == 0){
				scanf("%s", from);
				scanf("%s", input);

				if( strcmp(from, input) != 0){
					if(check_existence_of_vertex_name(from) && check_existence_of_vertex_name(input)){
						remove_edge(from, input);
					}
					else{
					printf("one or more of those vertices does not exist\n");
					}
				}	
				else{
					printf("A vertex cannot be connected to itself so no edge can be remove\n");
				}
			}
		
		}
		else if(strcmp(input,"add") == 0){
			scanf("%s", input);

			if(strcmp(input,"vertex") == 0){
				scanf("%s", input);
				if(number_of_vertices < MAX_NUMBER_OF_VERTICES){
					if(!check_existence_of_vertex_name(input)){
						add_vertex(input);
					}
					else{
						printf("There is already a vertex with the name %s\n",input );
					}
				}
				else{
					printf("The maximum limit of vertices (%d) has been already reached\n",MAX_NUMBER_OF_VERTICES );
				}
			}
			else if(strcmp(input,"edge") == 0){
				scanf("%s", from);
				scanf("%s", input);
				if( strcmp(from, input) != 0){
					if(check_existence_of_vertex_name(from) && check_existence_of_vertex_name(input)){
						add_edge(from, input);
					}
					else{
						printf("one or more of those vertices does not exist\n");
					}
				}
				else{
					printf("A vertex cannot be connected to itself\n");
				}
			}
		}
		else{
		 	display_help();
		}
	}while(strcmp(input,"quit") != 0);
	free_names();
	free(from);	
	free(input);

}
bool check_existence_of_vertex_name(char *name){
	bool result = false;
	
	for (int i = 0; i < number_of_vertices; ++i){
		if(strcmp(vertex_names[i], name) == 0){
			result = true;
		}
	}

	return result;
}
void add_vertex(char *vertex_name){

	strcpy(vertex_names[number_of_vertices], vertex_name);
	printf("Added a new vertex named %s at index %d\n",vertex_names[number_of_vertices], number_of_vertices);
	number_of_vertices++;
}
void add_edge(char *from_vertex_name, char *to_vertex_name){
	int from = get_index_of_vertex(from_vertex_name);
	int to = get_index_of_vertex(to_vertex_name);

	if(!adjacency_matrix[from][to]){
		adjacency_matrix[from][to] = true;
		printf("Added an edge from vertex %s to vertex %s\n", from_vertex_name, to_vertex_name );
	}
	else{
		printf("That edge already exists\n");
	}
}
void remove_edge(char *from_vertex_name, char *to_vertex_name){
	int from = get_index_of_vertex(from_vertex_name);
	int to = get_index_of_vertex(to_vertex_name);

	if(adjacency_matrix[from][to]){
		adjacency_matrix[from][to] = false;
		printf("Removed the edge form vertex %s to vertex %s\n", from_vertex_name, to_vertex_name );
	}
	else{
		printf("No edge exists between those two vertex\n");
	}
}
int get_index_of_vertex(char *vertex_name){
	int i;

	for(i = 0; i < number_of_vertices; i++){
		if(strcmp(vertex_names[i], vertex_name) == 0){
			break;
		}
	}
	return i;
}
bool check_for_cycle(){
	bool *visited= malloc(sizeof(bool)* number_of_vertices);
	bool *recStack= malloc(sizeof(bool)* number_of_vertices);
	int i;
	for(i = 0; i < number_of_vertices; i++){
		visited[i] = false;
		recStack[i] = false;
	}

	for(i = 0; i < number_of_vertices; i++){
		if(is_cycle_Util(i, visited, recStack)){
			return true;
		}
	}
	
	return false;
}
bool is_cycle_Util(int index, bool *visited, bool *recStack){

	if(!visited[index]){
		visited[index] = true;
		recStack[index] = true;
		
		for(int i = 0; i < number_of_vertices; i++){
			if(adjacency_matrix[index][i] == true){
				if(!visited[i] && is_cycle_Util(i, visited, recStack)){
				return true;
			}
			else if ( recStack[i])
				return true;
			}
		}
	}
	recStack[index] = false;
	return false;
}
void free_names(){
	for( int i = 0; i < MAX_NUMBER_OF_VERTICES; i++){
		free(vertex_names[i]);
	}
}
void display_help(){
	printf("\n");
	printf("The following commands are available for use:\n\tadd vertex <vertex_name>\n");
	printf("\tadd edge <from_vertex_name> <to_vertex_name>\n");
	printf("\tdisplay\n\tcheck\n\thelp\n\tquit\n");
	printf("Angled brackets such as: <info> represent user defined information.\n");
	printf("\n");
}
void display_adjacency_matrix(){

	if(number_of_vertices > 0){
		printf("\n");
		printf("%10s" ,"");
		for (int i = 0; i < number_of_vertices; ++i){
			printf("%10s",vertex_names[i]);
		}
		printf("\n");
		for(int i = 0; i < number_of_vertices; i++){
			printf("%10s", vertex_names[i]);
			for(int j = 0; j < number_of_vertices; j++){
				printf("%10d", adjacency_matrix[i][j] );
			}
			printf("\n");
		}
	}else{
		printf("Unable to display adjacency matrix. There are no vertices yet\n");
	}
}
void initializationCode(){
	for(int i = 0; i < MAX_NUMBER_OF_VERTICES; i++){
		vertex_names[i] = malloc(sizeof(char) * STRING_MAX_SIZE);
	}
}











