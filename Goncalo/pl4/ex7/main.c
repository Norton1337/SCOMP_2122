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
	if ((sem[1] =sem_open("sem1", O_CREAT, 0644,0)) == SEM_FAILED) {
		perror("Error in sem_open()");
		exit(0);
	}	
	if ((sem[2] =sem_open("sem2", O_CREAT, 0644,0)) == SEM_FAILED) {
		perror("Error in sem_open()");
		exit(0);
	}	
	

	fflush(stdout);
	for(e=0;e<2;e=e+1){
		
		
		for (d=0;d<3;d=d+1){
			
			if (fork()==0){
				//process 1
				if (d==0){
					
					fflush(stdout);
					sem_wait(sem[0]);
					
					if (e==0){
						printf("sistemas ");
						fflush(stdout);
						}
					else{ 
						printf("a ");
						fflush(stdout);
						}
					
					
					
					
					sem_post(sem[d+1]);
					
					
					}
					
					
					
					
				//process 2				
				if (d==1){
					
					sem_wait(sem[d]);
					
					if (e==0){
						printf("de ");
						fflush(stdout);}
					else{ 
						printf("melhor ");
						fflush(stdout);}
					
					
					sem_post(sem[d+1]);
					
					}
					
					
					
					
					
				//process 3				
				if (d==2){
					
					sem_wait(sem[d]);
					
					if (e==0){
						printf("computacao ");
						fflush(stdout);
						}
					else{
						printf("disciplina! ");
						fflush(stdout);}
					
					
					sem_post(sem[0]);
					}
				
				
				
				
				
				exit(0);
				}
			}
			for (int b=0;b<3;b=b+1)wait(NULL);
			
		
		}
	
	
	
	
	
	
	sem_unlink("sem");
	sem_unlink("sem1");
	sem_unlink("sem2");
	
	
	
	
	

		
		
		
		
	
	

	return 0;
}
