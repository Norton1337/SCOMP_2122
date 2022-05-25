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
	sem_t *sem[3];
		
	sem_unlink("sem");
	sem_unlink("sem1");
	sem_unlink("sem2");
	
	
	
	if ((sem[0] =sem_open("sem", O_CREAT, 0644,1)) == SEM_FAILED) {
		perror("Error in sem_open()");
		exit(0);
	}
	
	
	a=0;
	if (fork()==0){
		while(1){
			if (a==0)sem_wait(sem[0]);
			write(STDOUT_FILENO,"C",1);
			
			
			if (rand() % 10 <5 && a==0){
				a=a+1;
				}
			else{
				a=0;
				sem_post(sem[0]);
				sleep(1);
				
				}
			
			
			
			}
		
		
		}
	else{
		while(1){
			
			if (a==0)sem_wait(sem[0]);
			write(STDOUT_FILENO,"S",1);

			
			
			if (rand() % 10 <5 && a==0){
				a=a+1;
				}
			else{
				a=0;
				sem_post(sem[0]);
				sleep(1);
				
				}
			
			
			}
		
		
		
		
		
		}
	
	
	
	
	
	
	sem_unlink("sem");
	sem_unlink("sem1");
	sem_unlink("sem2");
	
	
	
	
	

		
		
		
		
	
	

	return 0;
}
