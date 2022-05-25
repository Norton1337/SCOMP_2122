#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>




int main(){
	pid_t p;
	int fd;
	int d,e,a;
	sem_t *sem,*sema;
	
	
	
	
	if ((sem =sem_open("semaf", O_CREAT, 0644,0)) == SEM_FAILED) {
		perror("Error in sem_open()");
		exit(0);
	}
	
	if ((sema =sem_open("sem", O_CREAT, 0644,1)) == SEM_FAILED) {
		perror("Error in sem_open()");
		exit(0);
	}
	p=fork();
	
	for(d=0;d<15;d=d+1){
	
	
		if(p==0){
			sem_wait(sema);
			write(STDOUT_FILENO,"im the child\n",14);
			sem_post(sem);
			
		}
		
		
		else{
			sem_wait(sem);
			write(STDOUT_FILENO,"im the father\n",15);
			sem_post(sema);
			
			}
	
	
	}
		
		
		
		
		
	sem_unlink("sem");
	sem_unlink("semaf");

	return 0;
}
