#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>




typedef struct {
	int index;
} shared_data_type;



int main(){
	pid_t p;
	int fd;
	int d,e,a;
	sem_t *sem[3];
		
	
		shared_data_type *addr;
	fd = shm_open("/ok", O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);
	ftruncate (fd, sizeof(shared_data_type)+5);
	addr = mmap(NULL, sizeof(shared_data_type)+5,PROT_READ|PROT_WRITE,MAP_SHARED, fd, 0);
	
	
	if ((sem[0] =sem_open("sem", O_CREAT, 0644,1)) == SEM_FAILED) {
		perror("Error in sem_open()");
		exit(0);
	}
	if ((sem[1] =sem_open("sem1", O_CREAT, 0644,1)) == SEM_FAILED) {
		perror("Error in sem_open()");
		exit(0);
	}	
	if ((sem[2] =sem_open("sem2", O_CREAT, 0644,1)) == SEM_FAILED) {
		perror("Error in sem_open()");
		exit(0);
	}	
	//numero de passageiros
	addr->index=200;
	
	for(d=0;d<400;d=d+1){
		if(fork()==0){
			//primeiros 50 passageiros saem pela porta 1 sendo o semaforo responsavel sem[0]
			if (d<50){
				sem_wait(sem[0]);
				addr->index--;
				sem_post(sem[0]);
				
				}
			
			if (d>=50 && d<100){
				sem_wait(sem[1]);
				addr->index--;
				sem_post(sem[1]);
				}
				
			
			if (d>=100 && d<150){
				sem_wait(sem[2]);
				
				addr->index--;
				sem_post(sem[2]);
				}
				
			if (d>=150 && d<233 ){
				sem_wait(sem[0]);
				
				addr->index++;
				if (addr->index<200)sem_post(sem[0]);
				}
			if (d>=233 && d<316){
				sem_wait(sem[1]);
				
				addr->index++;
				if (addr->index<200)sem_post(sem[1]);
				}
				
			if (d>=316 && d<400){
				sem_wait(sem[1]);
				
				addr->index++;
				if (addr->index<200)sem_post(sem[2]);
				}
		printf("%d\n",addr->index);
		exit(0);
		}
	
	}
	for (e=0;e<400;e=e+1)wait(NULL);
	
	
	
	
	sem_unlink("sem");
	sem_unlink("sem1");
	sem_unlink("sem2");
	
	
	
	
	

		
		
		
		
	
	

	return 0;
}
