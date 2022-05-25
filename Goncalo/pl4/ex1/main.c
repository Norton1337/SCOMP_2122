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
	FILE *ok1;
	FILE *ok2;
	int d,e,a;
	sem_t *sem;
	int array[200];
	
	
	if ((sem =sem_open("sem", O_CREAT, 0644,1)) == SEM_FAILED) {
		perror("Error in sem_open()");
		exit(0);
	}
	
	for (int d=0;d<8;d=d+1){
		if (fork()==0){
			
			sem_wait(sem);
			
			
			ok1=fopen("numbers.txt","r");
			for(e=0;e<200;e=e+1){
				fscanf(ok1,"%d", &array[e]);
				}
			fclose(ok1);
			ok2=fopen("Output.txt","a");
			
			
			for(e=0;e<200;e=e+1){
				fprintf(ok2,"[%d] %d\n",getpid(),array[e]);
				}
			
			fclose(ok2);
			
			
			sem_post(sem);
			exit(0);
		}
	}
	ok2=fopen("Output.txt","w");
			
			
			
	
	
	for (int d=0;d<8;d=d+1)wait(NULL);
	
	
	
	

	return 0;
}
