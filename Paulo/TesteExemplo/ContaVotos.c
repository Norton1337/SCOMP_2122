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
	char mocao[100];
	char voto[500];
} voto_type;

int main(int argc, char *argv[]) {

	sem_t *sem;
	
	shm_unlink("/testeExemplo");
	sem_unlink("/semtesteExemplo");
	int data_size = sizeof(voto_type);
	int fd = shm_open("/testeExemplo",  O_CREAT|O_EXCL|O_RDWR,S_IRUSR|S_IWUSR);
	ftruncate(fd, data_size);
	voto_type *sharedMemory = (voto_type*)mmap(NULL,data_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	sem = sem_open("/semtesteExemplo", O_CREAT, 0644,1);
	
	sem_wait(sem);
	
	strcpy(sharedMemory->mocao,"Moção muito boa\n");

	sem_post(sem);
	
	getchar();
	
	int amountS=0;
	int amountN=0;
	
	for(int i=0;i<500;i++){
		if(sharedMemory->voto[i]=='S'){
			amountS++;
		}else{
			amountN++;
		}
		//printf("%c\n",sharedMemory->voto[i]);
	
	}
	
	printf("Votes for: %d\n",amountS);
	printf("Votes against: %d\n",amountN);
	
	
	
	
	
	munmap(sharedMemory, data_size);
	shm_unlink("/testeExemplo");
	sem_unlink("/semtesteExemplo");
    return 0;
}
