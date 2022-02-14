/**
* Name: Isabel Valdez
* Lab/task: Project 1 Task 1
* Date: 04/10/18
**/
#include "head.h"
void setBit(unsigned short bitIndex){
	unsigned short i = bitIndex/8;  //gives the corresponding index in the array A
	unsigned short pos = bitIndex%8; //gives the corresponding bit position in A[i]
	unsigned char flag = 1; // flag = 0000...0001
	flag = flag << pos; // flag = 00.. 01...0000
	bitVector[i] = bitVector[i] | flag;
}
void clearBit(int index){
	bitVector[(index/8)] &= ~(1 << (index%8));
}
unsigned short findSpaceBit(){

	for(int i = 0; i < sizeOfBitVector; ++i){
		unsigned char mask = 1 ;
		for(int j = 0; j < 8; ++j){
			if((mask & bitVector[i]) != mask){
				return (i*8)+j;
			}
			mask <<= 1;
		}
	}
	return -1;
}
void displayBit(){
	printf("\n");
	printf("Bit Vector:\n");

	for(int i = 0; i < sizeOfBitVector; ++i){
		for(int j = 0; j < 8; ++j){
			printf("%d", !!((bitVector[i] << j) & 0x80) );
		}
		printf("\n");
	}
	printf("\n");
}
void initIndex(unsigned short index){
	for(short i = 0; i < INDEX_SIZE; ++i){
		memory[index].content.index[i] = 1;
	}
}
unsigned short findSpaceIndex(unsigned short index){
	for(short i = 0; i < INDEX_SIZE; ++i){
		if(memory[index].content.index[i] == 1){
			return i;
		}
	}
	return 0;
}
void createDATA( unsigned short index, FILE** fp, unsigned short fileSize){
	memory[index].type = DATA;
	for( int i = 0; i < fileSize; ++i){
		fscanf(*fp,"%[^\n]s",&memory[index].content.data[i]);
	}
}
short createFile(char* fileName, unsigned short owner){
	FILE* fp;
	NODE* newFile;
	unsigned short fileSize, spaceBit, mainRef, ref, indexSpace, currentFileSize;
	fp = fopen(fileName, "r");
	if(!fp){
		oops("Can't open file", 1);
	}
	fseek(fp, 0 , SEEK_END);
	fileSize = ftell(fp);
	rewind(fp);
	//
	newFile = malloc(sizeof(NODE));

	newFile->type = FIL;
	strcpy(newFile->content.fd.name, fileName);
	newFile->content.fd.create_t = time(NULL);
	newFile->content.fd.access = 1111;
	newFile->content.fd.owner = owner;
	newFile->content.fd.size = fileSize;
	//
	spaceBit = findSpaceBit();
	setBit(spaceBit);
	ref = findSpaceBit();
	setBit(ref);
	mainRef = spaceBit;
	//
	newFile->content.fd.block_ref =  ref;
	memory[spaceBit] = *newFile;
	//
	if(fileSize >= DATA_SIZE){
		memory[ref].type = INDEX;
		initIndex(ref);

		//
		currentFileSize = fileSize;
		while(currentFileSize >=fileSize ){
			indexSpace = findSpaceIndex(ref);
			spaceBit = findSpaceBit();
			memory[ref].content.index[indexSpace] = spaceBit;
			setBit(spaceBit);
			ref = spaceBit;
			memory[ref].type = DATA;
			for( int i = 0; currentFileSize >= fileSize ; ++i){
				fscanf(fp,"%[^\n]s",&memory[ref].content.data[i]);
				currentFileSize --;
			}
		}
	}
	createDATA(ref,&fp, fileSize);
	return mainRef;
}
short createDirectory(char* fileName, unsigned short owner){
	NODE *newDir;
	unsigned short mainRef,ref, indexBit, memIndex;

	newDir = malloc(sizeof(NODE));
	newDir->type = DIR;
	strcpy(newDir->content.fd.name, fileName);
	newDir->content.fd.create_t = time(NULL);
	newDir->content.fd.access = 1111;
	newDir->content.fd.owner = owner;
	memIndex = findSpaceBit();
	setBit(memIndex);
	memory[memIndex] = *newDir;
	mainRef = memIndex;
	//
	indexBit = findSpaceBit();
	setBit(indexBit);
	memory[memIndex].content.fd.block_ref = indexBit;

	memory[indexBit].type = INDEX;
	initIndex(indexBit);
	//
	memIndex = findSpaceIndex(indexBit);
	ref = findSpaceBit();
	memory[indexBit].content.index[memIndex] = ref;
	createFile("signIn.txt", owner);
	//
	memIndex = findSpaceIndex(indexBit);
	ref = findSpaceBit();
	memory[indexBit]. content.index[memIndex] = ref;
	createFile("signOut.txt", owner);

	return mainRef;
}
void createFileSystem(){
	sizeOfBitVector = MAX_MEMOTY/8;
	memory = malloc(sizeof(NODE*)* MAX_MEMOTY);
	bitVector = calloc(sizeOfBitVector, sizeof( char));
	
//	set up super block
	NODE* superBlock;
	superBlock = malloc(sizeof(NODE));
	superBlock->type = FIL;
	strcpy((superBlock->content.fd.name),"/");
	superBlock->content.fd.create_t = 0;
	superBlock->content.fd.access_t = 0;
	superBlock->content.fd.mod_t = 0;
	superBlock->content.fd.access = 0000;
	superBlock->content.fd.size = 0;
	superBlock->content.fd.block_ref = 1;
	memory[0] = *superBlock;
	setBit(0);

// set up super block index
	NODE* superBlockIndex;
	superBlockIndex = malloc(sizeof(NODE));
	superBlockIndex->type = INDEX;
	memory[1]= *superBlockIndex;
	initIndex(1);
	setBit(1);
}
void display( unsigned short index){
	NODE_TYPE type = memory[index].type;
	unsigned short zero = 0;
	switch(type){
		case DIR:
			printf("%d: DIRECTORY\n\tName: %s\n\tOwner = %d\n\tAccess: %d\n\tReference block: %d\n",index,memory[index].content.fd.name,memory[index].content.fd.owner,memory[index].content.fd.access ,memory[index].content.fd.block_ref);
			break;
		case FIL:
			printf("%d: FILE\n\tName: %s\n\tOwner = %d\n\tAccess: %d\n\tReference block: %d\n",index,memory[index].content.fd.name,memory[index].content.fd.owner,memory[index].content.fd.access ,memory[index].content.fd.block_ref);
			break;
		case DATA:
			printf("%d: DATA\n\t", index);
			for(int i = 0; i < 15; ++i){
				printf("%c",memory[index].content.data[i]);
			}
			printf("\n");
			break;

		case INDEX:
			printf("%d: INDEX\n\t Pointing to: ", index);
			for(unsigned short i = 0; i < INDEX_SIZE; ++i){
				if(memory[index].content.index[i] != 1){
					printf("%d,", memory[index].content.index[i]);
				}
			}
			printf("\n");
		break;
		default:
		break;
	}
}
void displayMemory(){
	unsigned short index;
	for(int i = 0; i < sizeOfBitVector; ++i){
		unsigned char mask = 1;
		for( int j = 0; j < 8; ++j){
			if((mask & bitVector[i]) == mask){
			index = (i*8)+j;
			display(index);
			}
		}
	}

}
void clearFS(unsigned short index){
	strcpy(memory[index].content.fd.name, "");
		memory[index].content.fd.create_t = 0;
		memory[index].content.fd.access_t = 0;
		memory[index].content.fd.mod_t = 0;
		memory[index].content.fd.access = 1111;
		memory[index].content.fd.owner = -1;
		memory[index].content.fd.size = 0;
		memory[index].content.fd.block_ref = 0;
		memory[index].type = NONE; 
}
void deleteInfo(unsigned short index){
	NODE_TYPE type = memory[index].type;
	switch(type){
		case DIR:
			deleteInfo(memory[index].content.fd.block_ref);
			clearFS(index);
		break;
		case FIL:
			deleteInfo(memory[index].content.fd.block_ref);
			clearFS(index);
		break;
		case INDEX:
			for(short i = 0; i < 1; ++i){
				if(memory[index].content.index[i] != 1 ){
					deleteInfo(memory[index].content.index[i]);
					memory[index].content.index[i] = 1;
				}
			}

		break;
		case DATA:
			for(short i = 0; i < DATA_SIZE; ++i){
				memory[index].content.data[i] = ' ';
			}
		break;
		default:
		break;
	}
	memory[index].type = NONE;
	clearBit(index);
}
unsigned short search(char* fileName, unsigned short owner){
	for (short i = 0; i < MAX_MEMOTY; ++i)
	{
		if(strcmp(memory[i].content.fd.name, fileName) == 0 && memory[i].content.fd.owner == owner){
			if(memory[i].content.fd.access != 0){
				return i;
			}
			else{
				printf("Don't have access to %s\n",fileName);
				return 1;
			}
		}
	}
	return 1;
}
void deleteFile(char* fileName, unsigned short owner){
	unsigned short memIndex;
	memIndex = search(fileName, owner);
	if(memIndex == 1){
		oops("Can not find file\n", 1);
	}
	deleteInfo( memIndex);
}
void deleteDir(char *fileName, unsigned short owner){
	unsigned short memIndex;
	memIndex = search(fileName, owner);
	if(memIndex == 1){
		oops("Can not find file\n", 1);
	}
	deleteInfo( memIndex);
}






