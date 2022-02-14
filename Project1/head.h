/**
* Name: Isabel Valdez
* Lab/task: Project 1 Task 1
* Date: 04/10/18
**/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define BLOCK_SIZE 256
#define MAX_NAME_LENGTH 128
#define DATA_SIZE 254
#define INDEX_SIZE 127
#define MAX_MEMOTY 20

#define oops(msg, errn) { perror(msg); exit(errn); }


typedef char data_t;
typedef unsigned short index_t;

typedef enum
{
   NONE,
   DIR,
   FIL,
   INDEX,
   DATA,
} NODE_TYPE;

typedef struct fs_node
{
   char name[MAX_NAME_LENGTH];
   time_t create_t; // creation time
   time_t access_t; // last access
   time_t mod_t; // last modification
   mode_t access; // access rights for the file
   unsigned short owner; // owner ID
   unsigned short size;
   index_t block_ref; // reference to the data or index block
} FS_NODE;

typedef struct node
{
   NODE_TYPE type;
   union
   {
      FS_NODE fd;
      data_t data[DATA_SIZE];
      index_t index[INDEX_SIZE];
   } content;
} NODE;

char* bitVector;
int sizeOfBitVector;
NODE* memory; // allocate 2^16 blocks (in init)
//
void clearBit(int index);
void clearFS(unsigned short index);
void initIndex(unsigned short index);
void setBit(unsigned short bitIndex);
void display( unsigned short index);
void displayMemory();
void displayBit();
unsigned short findSpaceBit();
unsigned short findSpaceIndex(unsigned short index);
unsigned short search(char* fileName, unsigned short owner);


void createFileSystem();
short createDirectory(char* fileName, unsigned short owner);
short createFile(char* fileName, unsigned short owner);

void deleteDir(char *fileName, unsigned short );
void deleteFile(char* fileName, unsigned short owner);
void deleteInfo(unsigned short index);


// // global table

// typedef struct open_file_global_type // elements of the hash table (in-memory "directory")
// {
//    unsigned short fd; // reference to the file descriptor node
//    unsigned short data; // reference to the data or index node (depending on the size)
//    mode_t access; // access rights for the file
//    unsigned short size; // size of the file
//    unsigned short reference_count; // reference count
//    struct open_file_global_type *next;
// } OPEN_FILE_GLOBAL_TYPE;

// #define GLOBAL_TABLE_SIZE 65521 // prime number for hashing
// OPEN_FILE_GLOBAL_TABLE global_table[GLOBAL_TABLE_SIZE];

// // local table

// typedef struct open_file_local_type // a node for a local list of open files (per process)
// {
//    mode_t access_rights; // access rights for this process
//    unsigned_short global_ref; // reference to the entry for the file in the global table
// } OPEN_FILE_LOCAL_TYPE;

// #define MAX_OPEN_FILES_PER_PROCESS 16
// OPEN_FILE_LOCAL_TYPE local_table[MAX_OPEN_FILES_PER_PROCESS];