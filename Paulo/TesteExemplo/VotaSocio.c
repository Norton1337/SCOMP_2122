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
	int votosFeitos;
	char mocao[200];
	char voto[500];
} voto_type;

int main(int argc, char *argv[]) {

	sem_t *sem;
	sem_t *semSocios;


	int data_size = sizeof(voto_type);
	int fd = shm_open("/testeExemplo", O_RDWR,S_IRUSR|S_IWUSR);
	ftruncate(fd, data_size);
	voto_type *sharedMemory = (voto_type*)mmap(NULL,data_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	sem = sem_open("/semtesteExemplo",O_CREAT, 0644,0);
	semSocios = sem_open("/semSocios",O_CREAT, 0644,1);
		
	sem_wait(sem);
	
	for(int i=0;i<10;i++){
		int a = fork();
		if(a==0){
			pid_t pid = getpid();
			time_t t;
			srand((int)time(&t) % pid);
			while(sharedMemory->votosFeitos<500){
				printf("%d is voting\n",pid);
				sem_wait(semSocios);
				
				if(rand() % 2==0)
					sharedMemory->voto[sharedMemory->votosFeitos]='N';
				else
					sharedMemory->voto[sharedMemory->votosFeitos]='S';
				sharedMemory->votosFeitos++;
				sem_post(semSocios);
				if(sharedMemory->votosFeitos>=500)
					break;
			}
			sem_post(semSocios);
			exit(0);
		}
	}
	int status;
	for(int i=0;i<10;i++){
		wait(&status);
	}
	
	printf("jobs done");
	
	
	
	munmap(sharedMemory, data_size);
	sem_unlink("/semtesteExemplo");
	sem_unlink("/semSocios");
    return 0;
}
