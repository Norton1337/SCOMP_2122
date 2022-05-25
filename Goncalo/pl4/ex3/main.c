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
	char var[50][80];
} shared_data_type;


//existe o main2.c para testar o funcionamento do programa

int main(){
	pid_t p;
	int fd;
	int d,e,a;
	sem_t *sem;
	
	
	
	shared_data_type *addr;
	fd = shm_open("/ok", O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);
	ftruncate (fd, sizeof(shared_data_type)+5);
	addr = mmap(NULL, sizeof(shared_data_type)+5,PROT_READ|PROT_WRITE,MAP_SHARED, fd, 0);
	
	addr->index=0;
	
	if ((sem =sem_open("sem", O_CREAT, 0644,0)) == SEM_FAILED) {
		perror("Error in sem_open()");
		exit(0);
	}
	
	sem_post(sem);
	sem_getvalue(sem,&a);
	
	printf("pronto %d\n",a);
	

	while ((addr->index)< 50){
		sem_wait(sem);
		
		
		
		
		sprintf(addr->var[addr->index], "I m the Father - with PID %d\n", getpid());
		
		addr->index++;
		printf("%d--%d\n",getpid(),addr->index);
		fflush(stdout);
		sem_post(sem);
		sleep(3);
		}
	

	

	return 0;
}
