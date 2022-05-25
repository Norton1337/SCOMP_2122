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
	sem_t *sem[4];
	int array[200];
	
	//FORAM USADOS SO 4 SEMAFOROS POR UMA QUESTAO DE SIMPLIFICAÇAO
	ok1 = fopen("Output.txt", "w");
	fclose(ok1);
	
	if ((sem[0] =sem_open("sem", O_CREAT, 0644,0)) == SEM_FAILED) {
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
	if ((sem[3] =sem_open("sem3", O_CREAT, 0644,0)) == SEM_FAILED) {
		perror("Error in sem_open()");
		exit(0);
	}
	
	
	
	
	
	
	
	
	for (d=0;d<4;d=d+1){
		if (fork()==0){
			if(d==0){sem_post(sem[d]);}
			sem_wait(sem[d]);
				
				
			
			
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
			
			
			sem_post(sem[d+1]);
			exit(0);
		}
	}
	
			
			
			
	
	
	for (int d=0;d<4;d=d+1)wait(NULL);
	
	
	
	

	return 0;
}
