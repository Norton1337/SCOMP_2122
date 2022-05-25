#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>

//VENDEDOR

//EXERCICIO COM PROBLEMAS DE FUNCIONAMENTO 
typedef struct {
	int ind;
	int ticket;
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
	
	addr->ind=0;
	if ((sem[0] =sem_open("/sem", O_CREAT, 0644,1)) == SEM_FAILED) {
		perror("Error in sem_open()");
		exit(0);
	}
	if ((sem[2] =sem_open("/sem2", O_CREAT, 0644,0)) == SEM_FAILED) {
		perror("Error in sem_open() 1");
		exit(0);
	}	

	int tickets=50;
	
	char bb;

	
	while(1){
		
		
	
		fflush(stdout);
		
		
		sem_wait(sem[2]);
		
	
		fflush(stdout);
						
		//while(addr->ind==0){}
		//addr->ind=0;

		
		
		
		printf("servido\n");
		fflush(stdout);
		addr->ticket=tickets;
		tickets=tickets-1;
		sem_post(sem[0]);
		
		
		

		
	
		
	}

	
	
	
	
	
	
	sem_unlink("sem");
	
	sem_unlink("sem2");
	
	
	
	
	

		
		
		
		
	
	

	return 0;
}
