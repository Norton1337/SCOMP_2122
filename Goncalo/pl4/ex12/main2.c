#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>


//CLIENTE

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
	
	if ((sem[0] =sem_open("/sem", 0)) == SEM_FAILED) {
			perror("1Error in sem_open()");
			exit(0);
		}
	if ((sem[2] =sem_open("/sem2", 0)) == SEM_FAILED) {
			perror("2Error in sem_open() 1");
			exit(0);
		}	
	
//	sem_wait(sem)

	//--------------------
	
	
	sem_wait(sem[0]);
	

	sem_post(sem[2]);

	
	printf("%d--%d",getpid(),addr->ticket);
	fflush(stdout);

	
	

	fflush(stdout);
	

		
	
	
	
	sem_close(sem[2]);
	
	sem_close(sem[0]);
	
	
	
	
	

	return 0;
}
