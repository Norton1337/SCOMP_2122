#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h> 
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>


typedef struct{
	int writing;
	char charArray[100];
} sharedMemorytype;

int main(int argc, char *argv[]) {
	int fd;
	int data_size = sizeof(sharedMemorytype);


	fd = shm_open ("/ex4", O_RDWR, S_IRUSR|S_IWUSR);

	
	ftruncate(fd, data_size);
	
	sharedMemorytype *sharedMemory=(sharedMemorytype *)mmap(NULL,data_size,PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	

	while(!sharedMemory->writing);
	int asciiSum=0;
	for(int i =0;i<100;i++){
		asciiSum+=sharedMemory->charArray[i];
	}
	
	printf("asciiSum: %d\n", asciiSum);
	
	for(int i=0;i<100;i++){
		printf("Char nº: %d\n", sharedMemory->charArray[i]);
	}
	
	printf("Average: %d\n", asciiSum/100);


	munmap(sharedMemory, data_size);
   
    shm_unlink("/ex4");
	return 0;
}
