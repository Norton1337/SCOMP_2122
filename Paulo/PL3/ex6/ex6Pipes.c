#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#define AMOUNT 1000

typedef struct {
	int num;
} ex6_type;

int main(int argc, char *argv[]) {
	int fd[2];
	ex6_type array[AMOUNT];
	ex6_type *ex6Pipe;     
	

	
	
	for(int i=0;i<AMOUNT;i++){
		array[i].num=i;
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
		for(int i=0;i<AMOUNT;i++){
			ex6Pipe=&array[i];
			write(fd[1],&ex6Pipe,sizeof(ex6_type));
		}
		close(fd[1]);

		
	}else{
		ex6_type array2[AMOUNT];
		close(fd[1]);
		
		for(int i=0;i<AMOUNT;i++){
			read(fd[0],&ex6Pipe,sizeof(ex6_type));
			array2[i]=*ex6Pipe;
		}
		close(fd[0]);

		exit(1);
	}
	int status;
	wait(&status);

	t = clock() - t;
	double time_taken = ((double) t) / CLOCKS_PER_SEC;
	printf("\nit took %f seconds\n",time_taken);

	return 0;
}

