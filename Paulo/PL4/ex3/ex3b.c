#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h> 
#include <semaphore.h>
#include <string.h>
#include <time.h>


typedef struct {
	int stringAmount;
	char string[50][80];
} string_type;

int main(int argc, char *argv[]) {
	sem_t *sem;
sem_unlink("/semEx3");

	int data_size = sizeof(string_type);
	int fd = shm_open("/ex3",  O_RDWR,S_IRUSR|S_IWUSR);
	ftruncate(fd, data_size);
	string_type *sharedMemory = (string_type*)mmap(NULL,data_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	sem = sem_open("/semEx3", O_CREAT, 0644,0);
	int totalAmount=0;

	sem_wait(sem);
	totalAmount=sharedMemory->stringAmount;
	
	for(int i=0;i<totalAmount;i++){
		
		printf("text[%d] : %s\n",i,sharedMemory->string[i]);
		
	}
	
	sem_post(sem);
		
	

	if(sem_close("/semEx3")==-1){
		perror("Error in sem_unlink().\n");
		exit(1);
	}
	
	munmap(sharedMemory, data_size); /* disconnects */
	shm_unlink("/ex3"); /* closes */
	
    return 0;
}
