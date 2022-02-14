/**
* Name: Isabel Liz Valdez
* Lab/task: Lab 2 Task 1
* Date: 02/05/18
**/

#include <stdio.h>


int offensiveFunc(int , int );

int main(void)
{
   printf("The next line will cause core dump.\n");
   printf("ERROR: %d\n\n", offensiveFunc(3.0, 0.0));
   
   printf("TEST1: input 0.9, 1 Result: %d\n", offensiveFunc(.9, 1));
   printf("TEST2: input 0, 0  Result:%d\n", offensiveFunc(0, 0));
   printf("TEST3: input 10.5, 2  Result:%d\n", offensiveFunc(10.5, 2));

   return 0;
}

int offensiveFunc(int x, int y)
{
	int z = -1;

   if(y != 0)
	{
		z = x / y;
	}
   return z;
}


