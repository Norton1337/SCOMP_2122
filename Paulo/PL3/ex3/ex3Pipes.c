#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#define ARRAYS_AMOUNT 100000

typedef struct {

	int number;
	char string[20];
} ex3_type;

int main(int argc, char *argv[]) {
	int fd[2];
	ex3_type array[ARRAYS_AMOUNT];
	ex3_type *ex3Pipe;     
	
	

	
	
	for(int i=0;i<ARRAYS_AMOUNT;i++){
		array[i].number=i;
		strcpy(array[i].string, "ISEP-SCOMP 2020"); 	
	}
	if(pipe(fd) == -1){
		perror("Pipe failed");
		return 1;
	}
	pid_t pid = fork();
	
	clock_t t;
    t = clock();
	
	if(pid>0){
		
		close(fd[0]);
		for(int i=0;i<ARRAYS_AMOUNT;i++){
			ex3Pipe=&array[i];
			write(fd[1],&ex3Pipe,sizeof(ex3_type)+1);
		}
		close(fd[1]);

		int status;
		wait(&status);
	}else{
		ex3_type array2[ARRAYS_AMOUNT];
		close(fd[1]);
		
		for(int i=0;i<ARRAYS_AMOUNT;i++){
			read(fd[0],&ex3Pipe,sizeof(ex3_type)+1);
			array2[i]=*ex3Pipe;
			//printf("[%d] - %s\n",array2[i].number,array2[i].string);
		}
		close(fd[0]);

		exit(1);
	}

	t = clock() - t;
	double time_taken = ((double) t) / CLOCKS_PER_SEC;
	printf("\nit took %f seconds\n",time_taken);

	return 0;
}

