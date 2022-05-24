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




typedef struct{
	int nums[10];
	int itemsLeft;
	int writing;
} ex14_type;

int main(void) {
	int data_size = sizeof(ex14_type);

	pid_t pid = fork();
	
	if(pid>0){
		//producer
		int fd = shm_open("/ex14", O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);
		ftruncate (fd, data_size);
		ex14_type *sharedMemory = (ex14_type*) mmap(NULL, data_size, PROT_READ|PROT_WRITE,MAP_SHARED, fd, 0);
		sharedMemory->itemsLeft = 30;
		sharedMemory->writing = 1;
		int newNumber=0;
		while(sharedMemory->itemsLeft>0){
			while(sharedMemory->writing==0);
			for(int i=0;i<10;i++){
				sharedMemory->nums[i]=newNumber;
				newNumber++;
				sharedMemory->itemsLeft--;
			}
			sharedMemory->writing = 0;
		}
		
	}else{
		//consumer
		int fd = shm_open("/ex14", O_RDWR, S_IRUSR|S_IWUSR);
		ftruncate (fd, data_size);
		ex14_type *sharedMemory = (ex14_type*) mmap(NULL, data_size, PROT_READ|PROT_WRITE,MAP_SHARED, fd, 0);
		while(1){
			while(sharedMemory->writing==1);
			for(int i=0;i<10;i++){
				printf("%d\n",sharedMemory->nums[i]);
			}
			sharedMemory->writing = 1;
			printf("printed 10 nums, %d remaining\n",sharedMemory->itemsLeft);
			if(sharedMemory->itemsLeft==0)
				break;
		}
		
		exit(1);
	}
		int status;
		wait(&status);

	
	
	shm_unlink("/ex14");

	return 0; 
}
