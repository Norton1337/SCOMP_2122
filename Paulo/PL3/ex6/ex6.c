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

#define AMOUNT 100000

typedef struct {
	int writing;
	int num;
} ex6_type;


int main(int argc, char *argv[]) {

	int array[AMOUNT];
	for(int i=0;i<AMOUNT;i++){
		array[i]=i;	
	}
	int data_size = sizeof(ex6_type);
	int fd = shm_open("/ex6", O_CREAT|O_EXCL|O_RDWR,S_IRUSR|S_IWUSR);
	ftruncate(fd, data_size);
	ex6_type *sharedMemory = (ex6_type*)mmap(NULL,data_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	pid_t pid = fork();
	sharedMemory->writing=1;
	
	clock_t t;
    t = clock();
    
    
	if(pid==0){

		for(int i=0;i<AMOUNT;i++){
			while(sharedMemory->writing==0);
			sharedMemory->num=array[i];
			sharedMemory->writing=0;
		}
		
		exit(0);
	}else{
		
		ex6_type array2[AMOUNT];
		for(int i=0;i<AMOUNT;i++){
			while(sharedMemory->writing==1);
			array2[i].num=sharedMemory->num;
			sharedMemory->writing=1;
			printf("[%d]\n",array2[i].num);
			
		}
		
		
	}
	int status;
	wait(&status);
	t = clock() - t;
	double time_taken = ((double) t) / CLOCKS_PER_SEC;
	printf("\nit took %f seconds\n",time_taken);
	

	shm_unlink("/ex6");
	return 0;
}

