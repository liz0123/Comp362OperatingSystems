
/**
* Name: Isabel Liz Valdez
* Lab/task: Lab 8 Task 3
* Date: 03/15/18
**/
#include "statLib.h"


int main(int argc, char ** argv){
	void *dylibHandle;
   char *error;

	dylibHandle = dlopen("./liblab3.so",RTLD_LAZY);
	if(!dylibHandle){
		fprintf(stderr, "ERR: %s\n", dlerror());
		exit(1);
	}
	// clear any existing errors
	dlerror();
	int (*lab3)() = dlsym(dylibHandle, "lab3");
	printf("hhhhhhh\n");
	int n = (*lab3)();
	if((error = dlerror()) != NULL){
		fprintf(stderr, "ERR: %s\n",error );
		exit(1);
	}
	//
	printf("rrrrrrr\n");
	dlclose(dylibHandle);

}
