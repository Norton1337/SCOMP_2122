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
shm_unlink("/ex3");
	int data_size = sizeof(string_type);
	int fd = shm_open("/ex3",  O_CREAT|O_EXCL|O_RDWR,S_IRUSR|S_IWUSR);
	ftruncate(fd, data_size);
	string_type *sharedMemory = (string_type*)mmap(NULL,data_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	sem = sem_open("/semEx3", O_CREAT, 0644,1);
	sharedMemory->stringAmount=0;
	
	int amount = sharedMemory->stringAmount;
	for(int i=0;i<11;i++){
		int a = fork();
		if(a==0){

			while(amount!=50){
				sem_wait(sem);
				amount=sharedMemory->stringAmount;
				printf("amount : %d\n",amount);
				if(amount>=50)
					break;
				pid_t pid = getpid();
				char text[50];
				
				sprintf(text, "%s %d", "I'm the Father - with PID",pid);
				
				strncpy(sharedMemory->string[sharedMemory->stringAmount],text,50);
			
				printf("%s\n",sharedMemory->string[sharedMemory->stringAmount]);
				sharedMemory->stringAmount++;
				
				sem_post(sem);
				

				time_t t;
				srand((int)time(&t) % getpid());
				
				sleep((rand() % 4)+1);
								
			}
			sem_post(sem);
			exit(0);
		}
	}
	
	munmap(sharedMemory, data_size);
	shm_unlink("/ex3");
	sem_unlink("/semEx3");
	exit(0);
    return 0;
}
