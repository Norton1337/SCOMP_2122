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

#define SENSOR_AMOUNT 5

typedef struct {
	int measurement[SENSOR_AMOUNT];
	int sensorsAlarm;
} ex19_type;

int main(int argc, char *argv[]) {
	
	int data_size = sizeof(ex19_type);
	char* semNames[SENSOR_AMOUNT] = {"semEx19_1","semEx19_2","semEx19_3","semEx19_4","semEx19_5"};
	char* semNames2[SENSOR_AMOUNT] = {"semEx19_1v2","semEx19_2v2","semEx19_3v2","semEx19_4v2","semEx19_5v2"};
	
	for(int i = 0; i < SENSOR_AMOUNT; i++)
		sem_unlink(semNames[i]);
	
    shm_unlink("/ex19");
	sem_unlink("/semEx19");
	
	if(fork()==0){
		//Controller
		int fd = shm_open("/ex19",  O_CREAT|O_EXCL|O_RDWR,S_IRUSR|S_IWUSR);
		ftruncate(fd, data_size);
		ex19_type *sharedMemory = (ex19_type*)mmap(NULL,data_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
		sharedMemory->sensorsAlarm = 0;
		sem_t *sem;
		sem_t *sensorSem[SENSOR_AMOUNT];
		sem_t *sensorSem2[SENSOR_AMOUNT];
		
		if ((sem = sem_open("/semEx19", O_CREAT, 0644,1)) == SEM_FAILED) {
			perror("Error in sem_open()");
			exit(1);
		}
		
		for(int i=0;i<SENSOR_AMOUNT;i++){
			
			if ((sensorSem[i] = sem_open(semNames[i], O_CREAT, 0644,0)) == SEM_FAILED) {
				perror("Error in sem_open()");
				exit(1);
			}
			if ((sensorSem2[i] = sem_open(semNames2[i], O_CREAT, 0644,0)) == SEM_FAILED) {
				perror("Error in sem_open()");
				exit(1);
			}
		}
		int test=0;
		while(1){
			
			int count=0;
			for(int i=0;i<6;i++){
				if(sem_trywait(sensorSem2[i])==0){
					printf("trywait worked\n");
					count++;
					printf("%d\n",count);
					sem_post(sensorSem[i]);
				}
			}
	
		}
		
		
		
	}else{
	
		for(int i=0;i<SENSOR_AMOUNT;i++){
			
			if(fork()==0){

				int fd = shm_open("/ex19", O_RDWR,S_IRUSR|S_IWUSR);
				ftruncate(fd, data_size);
				ex19_type *sharedMemory = (ex19_type*)mmap(NULL,data_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
				sem_t *sem;
				sem_t *semSensor;
				sem_t *semSensor2;
				sem = sem_open("/semEx19", O_CREAT,0644,1);
				semSensor = sem_open(semNames[i], O_CREAT,0644,1);
				semSensor2 = sem_open(semNames2[i], O_CREAT,0644,0);
				
				time_t t;
				srand((int)time(&t) % getpid());
				int inAlarmState=0;
				
				for(int k=0;k<6;k++){
					
					
					sem_wait(semSensor);
					printf("[%d] before post\n",k);
					sem_post(semSensor2);
					printf("[%d] after post\n",k);
					sleep(1);
				}
				
				munmap(sharedMemory, data_size);
				exit(0);
			}
			
		}
	}

	
	for(int i = 0; i < SENSOR_AMOUNT; i++){

		if(sem_unlink(semNames[i])==-1){
			perror("Error in close().\n");
			exit(1);
		}
		if(sem_unlink(semNames2[i])==-1){
			perror("Error in close().\n");
			exit(1);
		}
	}
	

    shm_unlink("/ex19");
	sem_unlink("/semEx19");
    return 0;
}
