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

#define MAX_CAPACITY 300
#define VIP 0
#define SPECIAL 1
#define NORMAL 2
#define WAIT_TIME 1000
typedef struct {
	int clients;
} ex17_type;

int main(int argc, char *argv[]) {
	char* semNames[3] = {"semVip","semSpecial","semNormal"};
    shm_unlink("/ex17");
    for(int i = 0; i < 3; i++)
		sem_unlink(semNames[i]);
    
	sem_unlink("/semClub");
	
	int data_size = sizeof(ex17_type);
	int fd = shm_open("/ex17",  O_CREAT|O_EXCL|O_RDWR,S_IRUSR|S_IWUSR);
	ftruncate(fd, data_size);
	ex17_type *sharedMemory = (ex17_type*)mmap(NULL,data_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	sharedMemory->clients=300;
	sem_t *sem[3];
	sem_t *semClub;
	
	for(int i=0;i<3;i++){
		
		if ((sem[i] = sem_open(semNames[i], O_CREAT, 0644,0)) == SEM_FAILED) {
			perror("Error in sem_open()");
			exit(1);
		}
	}
	
	if ((semClub = sem_open("/semClub", O_CREAT, 0644,1)) == SEM_FAILED) {
		perror("Error in sem_open()");
		exit(1);
	}
			
	

	pid_t vip = fork();
	if (vip == 0){
		time_t t;
		srand((int)time(&t) % getpid());
		while(1){
			int vipWaiting;
			sem_getvalue(sem[0], &vipWaiting);
			if(sharedMemory->clients<300 && vipWaiting>0){
				sem_wait(semClub);
				sem_wait(sem[0]);
				sharedMemory->clients++;
				sem_post(semClub);
			}else
			if(rand() % 100==0){
				if(sharedMemory->clients==300){
					sem_post(sem[0]);
				}else{
					sem_wait(semClub);
					sharedMemory->clients++;
					printf("new vip, now %d clients\n",sharedMemory->clients);
					sem_post(semClub);
				}
			}
			usleep(WAIT_TIME);
			
		}
		exit(0);
	}
	
	pid_t special = fork();
	if (special == 0){
		time_t t;
		srand((int)time(&t) % getpid());
		while(1){
			int vipWaiting;
			int specialWaiting;
			sem_getvalue(sem[0], &vipWaiting);
			sem_getvalue(sem[1], &specialWaiting);
			if(sharedMemory->clients<300 && vipWaiting==0 && specialWaiting>0){
				sem_wait(semClub);
				sem_wait(sem[1]);
				sharedMemory->clients++;
				sem_post(semClub);
			}else
			if(rand() % 50==1){
				if(sharedMemory->clients==300){
					sem_post(sem[1]);
				}else{
					sem_wait(semClub);
					sharedMemory->clients++;
					printf("new special, now %d clients\n",sharedMemory->clients);
					sem_post(semClub);
				}
			}
			usleep(WAIT_TIME);
			
		}
		exit(0);
	}
	
	pid_t normal = fork();
	if (normal == 0){
		time_t t;
		srand((int)time(&t) % getpid());
		while(1){
			int vipWaiting;
			int specialWaiting;
			int normalWaiting;
			sem_getvalue(sem[0], &vipWaiting);
			sem_getvalue(sem[1], &specialWaiting);
			sem_getvalue(sem[2], &normalWaiting);
			if(sharedMemory->clients==300)
			{
				printf("\nvipWaiting: %d\n",vipWaiting);
			printf("specialWaiting: %d\n",specialWaiting);
			printf("normalWaiting: %d\n",normalWaiting);
			}
			if(sharedMemory->clients<300 && vipWaiting==0 && specialWaiting==0 && normalWaiting>0){
				sem_wait(semClub);
				sem_wait(sem[2]);
				sharedMemory->clients++;
				sem_post(semClub);
			}else
			if(rand() % 25==2){
				if(sharedMemory->clients==300){
					sem_post(sem[2]);
				}else{
					sem_wait(semClub);
					sharedMemory->clients++;
					printf("new normal, now %d clients\n",sharedMemory->clients);
					sem_post(semClub);
				}
			}
			usleep(WAIT_TIME);
	
			
		}
		exit(0);
	}
	time_t t;
	srand((int)time(&t));
	while(1){
		
		if(rand() %20 ==0 && sharedMemory->clients>0){
			sem_wait(semClub);
			sharedMemory->clients--;
			printf("a client just left, %d clients still inside\n",sharedMemory->clients);
			sem_post(semClub);
		}
		usleep(WAIT_TIME);
		
		
	}
	
	int status;
	for (int i=0;i<3;i++){
        wait(&status);            
    }
    
    shm_unlink("/ex17");
    for(int i = 0; i < 3; i++){

		if(sem_unlink(semNames[i])==-1){
			perror("Error in close().\n");
			exit(1);
		}
	}
    
	if(sem_unlink("/semClub")==-1){
		perror("Error in sem_unlink().\n");
		exit(1);
	}
    return 0;
}
