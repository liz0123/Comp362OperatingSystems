/**
* Name: Isabel Liz Valdez
* Lab/task: Lab 2 Task 2
* Date: 02/05/18
**/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *getStrToPrint(char *);

#define STR_BOYS "Boys!"
#define STR_GIRLS "Girls!"

int main(void)
{
   printf("To the boys: %s\n", getStrToPrint(STR_BOYS));
   printf("To the girls: %s\n", getStrToPrint(STR_GIRLS));
}

char *getStrToPrint(char *to)
{
   char *ptr = malloc( sizeof(char *) );
   sprintf(ptr, "Hello %s!", to);
   return ptr;
}
