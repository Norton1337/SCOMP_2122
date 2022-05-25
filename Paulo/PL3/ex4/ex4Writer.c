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


	fd = shm_open ("/ex4", O_CREAT|O_RDWR,S_IRUSR|S_IWUSR);
	int i;
	srand(time(NULL));
	
	if (fd == -1){
		perror("Error in shm_open().\n");
		return 1;
	}
	ftruncate(fd, data_size);

	sharedMemorytype *sharedMemory=(sharedMemorytype *)mmap(NULL,data_size,PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	
	sharedMemory->writing=0;
	for(i=0;i<100;i++){
		sharedMemory->charArray[i]= rand() % 26 + 'A';
		printf("%c\n",sharedMemory->charArray[i]);
	}
	sharedMemory->writing=1;
	

	munmap(sharedMemory, data_size);

	close(fd);
	
	return 0;
}
	
