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
	int finalVector[5000];
	int amount;
} ex18_type;

int main(int argc, char *argv[]) {



	int data_size = sizeof(ex18_type);
	int fd = shm_open("/ex18",  O_CREAT|O_EXCL|O_RDWR,S_IRUSR|S_IWUSR);
	ftruncate(fd, data_size);
	ex18_type *sharedMemory = (ex18_type*)mmap(NULL,data_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	sharedMemory->amount=0;
	sem_t *sem1;
	sem_t *sem2;
	if ((sem1 = sem_open("semEx18N1", O_CREAT, 0644,1)) == SEM_FAILED) {
		perror("Error in sem_open()");
		exit(1);
	}
	if ((sem2 = sem_open("semEx18N2", O_CREAT, 0644,0)) == SEM_FAILED) {
		perror("Error in sem_open()");
		exit(1);
	}
	
	int initialVector[10000];
	time_t t;
	srand((int)time(&t) % getpid());
	for(int i=0;i<10000;i++)
		initialVector[i] = (rand() % 5000)+1;
	
	
	if(fork()==0){
		//P1
		while(sharedMemory->amount<5000){
			sem_wait(sem1);
			if(sharedMemory->amount==5000)
				break;
			int newPos = sharedMemory->amount *2; 
			sharedMemory->finalVector[sharedMemory->amount]=initialVector[newPos]*initialVector[newPos+1];
			sharedMemory->amount++;
			sem_post(sem2);
		}
		sem_post(sem2);
		exit(0);
	}

	if(fork()==0){
		//P2
		while(sharedMemory->amount<5000){
			sem_wait(sem2);
			if(sharedMemory->amount==5000)
				break;
			int newPos = sharedMemory->amount *2; 
			sharedMemory->finalVector[sharedMemory->amount]=initialVector[newPos]*initialVector[newPos+1];
			sharedMemory->amount++;
			sem_post(sem1);
		}
		sem_post(sem1);
		exit(0);
	}
	int largestNumber=0;	
	if(fork()==0){
		//P3
		
		while(sharedMemory->amount<5000){
			for(int i=0;i<sharedMemory->amount;i++){
				if(sharedMemory->finalVector[i]>largestNumber){
					largestNumber=sharedMemory->finalVector[i];
					printf("new largestNumber:%d\n",largestNumber);
				}
				
			}
		}
	}

	
	int status;
	
	for (int i=0;i<2;i++){
        wait(&status);            
    }
    
    printf("largest Number: %d\n",largestNumber);
    printf("last Number: %d\n",sharedMemory->finalVector[4999]);
    
    shm_unlink("/ex18");
    
    
	sem_unlink("/semEx18N1");
	
	sem_unlink("/semEx18N2");
    return 0;
}
