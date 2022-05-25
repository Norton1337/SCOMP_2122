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


int main(int argc, char *argv[]) {
	sem_t *sem;
	pid_t a;
	

	if ((sem = sem_open("/semEx1", O_CREAT, 0644,1)) == SEM_FAILED) {
        perror("Error in sem_open()");
		exit(1);
    }
	//reset file
	FILE *outputFile2 = fopen("Output.txt", "w");
	fclose(outputFile2);
			
	
    for (int i=0;i<8;i++){
		
		a = fork();
		if (a < 0){
			perror("Error creating process\n");
			exit(1);
		}
		if (a == 0){
			
			if(sem_wait(sem)==-1){
				perror("Error in sem_wait()\n");
				exit(1);
			}  
			FILE *numbersFile = fopen("Numbers.txt", "r");
			outputFile2 = fopen("Output.txt", "a");
			
			if (numbersFile == NULL || outputFile2 == NULL){
				printf("Couldn't open the file\n");
				exit(1);
			}     
			
			int num;
			for(int k=0;k<200;k++){
                fscanf(numbersFile, "%d\n", &num);
                fprintf(outputFile2, "[%d] %d\n", getpid(),num);
            }
			
			
            fclose(outputFile2);
            fclose(numbersFile);
			
            if(sem_post(sem)==-1){
				perror("Error in sem_post()\n");
				exit(1);
			}
            exit(0);
        }
    }
	
	
	for (int i=0;i<8;i++){
        wait(NULL);            
    }
    
    FILE *outputFile = fopen("Output.txt", "r");
	
	pid_t pid;
	int number;
    while(!feof(outputFile)){
        fscanf(outputFile, "[%d] %d\n",&pid, &number);
        printf("[%d] %d\n",pid,number);
    }
	
    fclose(outputFile);

	if(sem_unlink("/semEx1")==-1){
		perror("Error in sem_unlink().\n");
		exit(1);
	}
    return 0;
}
