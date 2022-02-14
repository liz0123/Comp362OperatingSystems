/**
* Name: Isabel Liz Valdez
* Lab/task: Lab 2 Task 3
* Date: 02/05/18
**/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MIN_NUMBER_OF_ARGV 2


void main(int argc, char **argv) 
{
	char replaced_char;
	char replacement_char;
	char c;
// SECTION 1:
// Setting up replaced_char and replacement_char
// Check that there are at least the minimum number of arguments	

	if(argc > MIN_NUMBER_OF_ARGV)
	{
// Get replaced_char and replacement_char from argv.		
		replaced_char = *argv[ MIN_NUMBER_OF_ARGV - 1 ];
		replacement_char = *argv[ MIN_NUMBER_OF_ARGV ];

//SECTION 2:
// Process the remaining arguments (if any)
// Use a while loop to process any input or output file arguments using freopen.
// Be sure to check whether freopen was successful.		
		int index = 3;
		while(argc > index) 
		{
			if(strcmp(argv[index], "-f" ) == 0 )
			{
				if(argv[index+1])
				{
					if(freopen(argv[index+1], "r", stdin)) //stdin is taken from file name
					{
						index++;
					}
					else
					{
						printf(">> Unable to open Input File <<\n");
						exit(0);
					}
				}
				else
				{
					printf(">> No Input File Name <<\n");
					exit(0);
				}
			}
			else if(strcmp(argv[index], "-o") == 0)
			{
				if(argv[index+1])
				{
					if(freopen(argv[index+1], "w", stdout)) // stdout is taken from file name
					{
						index++;
					}
					else
					{
						printf(">> Unable to open Output File <<\n");
						exit(0);
					}
				}
				else
				{
					printf(">> No Output File Name <<\n");
					exit(0);
				}
			}
			else
			{
				printf("sub replaced_char replacement_char [-f inputFile] [-o outputFile]\n");
				exit(0);
			}
			index++;
		}//end while
	}
	else
	{
		printf("sub replaced_char replacement_char [-f inputFile] [-o outputFile]\n");
		exit(0);
	}

// SECTION 3:
// Use a while loop to process the entire input stream and perform the main substitution functionality.	
	c = fgetc(stdin); 
	while (c != EOF)
	{
		if(replaced_char == c)
		{
			fputc(replacement_char, stdout);
		}
		else
		{
			fputc(c, stdout);
		}
		c = fgetc(stdin);
	}
// SECTION 4:
// Close the input and output streams.
	fclose(stdin);
	fclose(stdout);
	printf("\n");
	//return 0;
}