#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

#define ARRAYS_AMOUNT 100

typedef struct {
	int writing;
	int number;
	char string[20];
} ex3_type;

int main(int argc, char *argv[]) {

	ex3_type array[ARRAYS_AMOUNT];
	for(int i=0;i<ARRAYS_AMOUNT;i++){
		array[i].number=i;
		strcpy(array[i].string, "ISEP-SCOMP 2020"); 	
	}
	int data_size = sizeof(ex3_type);
	int fd = shm_open("/ex3", O_CREAT|O_EXCL|O_RDWR,S_IRUSR|S_IWUSR);
	ftruncate(fd, data_size);
	ex3_type *sharedMemory = (ex3_type*)mmap(NULL,data_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	pid_t pid = fork();
	sharedMemory->writing=1;
	
	clock_t t;
    t = clock();
	if(pid==0){

		for(int i=0;i<ARRAYS_AMOUNT;i++){
			while(sharedMemory->writing==0);
			sharedMemory->number=i;
			strcpy(sharedMemory->string, array[i].string); 
			sharedMemory->writing=0;

			
		}

		exit(0);
		
	}else{
		
		ex3_type array2[ARRAYS_AMOUNT];
		for(int i=0;i<ARRAYS_AMOUNT;i++){
			while(sharedMemory->writing==1);
			array2[i].number=sharedMemory->number;
			strcpy(array2[i].string, sharedMemory->string); 
			sharedMemory->writing=1;
			printf("[%d] - %s\n",array2[i].number,array2[i].string);

		}
	
		
	}
	int status;
	wait(&status);
	t = clock() - t;
	double time_taken = ((double) t) / CLOCKS_PER_SEC;
	printf("\nit took %f seconds\n",time_taken);
	
	
	
	
	

	shm_unlink("/ex3");
	return 0;
}

