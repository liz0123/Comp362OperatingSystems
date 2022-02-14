/*
 *  Isabel Valdez
 *  Lab 9 Task 1
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <errno.h>

#define oops(msg, errn)    { perror(msg); exit(errn); }

int main(int argc, char *argv[])
{
    int fd, offset;
    char *data;
    char *fileName, line[256];
    struct stat sbuf;
    int stop;

    long pagesize = sysconf(_SC_PAGESIZE);
    printf("Playing with pages of size %ld\n", pagesize);

    printf("Enter file name: ");
    scanf("%s", line);
    fileName = line;

    if ((fd = open(fileName, O_RDWR)) == -1)
        oops("Failed to open file!", 1);

    if (stat(fileName, &sbuf) == -1)
        oops("Failed to stat file!", 1);
    do{
        printf("Enter file offset between 0 and %d: ", (int) sbuf.st_size - 1);
        scanf("%d", &offset);

        if (offset < 0 || offset > sbuf.st_size - 1)
        {
            fprintf(stderr, "mmapdemo: offset must be in the range 0-%d\n",
                    (int) sbuf.st_size - 1);
            exit(1);
        }

        // try "man mmap"
        // NULL ==> the OS will choose the address
        // MAP_SHARED allows for sharing with other processes; otherwise: MAP_PRIVATE
        // the last "0" means that we share the file starting at offset 0
        data = (char*)mmap(NULL, sbuf.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

        if (data == MAP_FAILED)
            oops("mmap failed!", 1);

        printf("Byte at offset %d is '%c'\n", offset, data[offset]);

        char replacementChar;
        printf("With what would you like to replace the character: ");
        scanf(" %c", &replacementChar);
        data[offset] = replacementChar;

        printf("Byte at offset %d is '%c'\n", offset, data[offset]);

        // unmap part of the file; NOTE: OS works with pages, so if the length
        // is less then the page length, then it will be raised automatically
        if (munmap(data, pagesize) < 0)
                oops("Failed to unmap file!", 1);


        printf("\nWould you like to continue: (1(yes)/0(no)): ");
        scanf("%d", &stop);
        }while(stop);

    return 0;
}
