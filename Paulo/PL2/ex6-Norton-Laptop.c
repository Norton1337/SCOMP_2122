#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>
#include <ctype.h>
#include <time.h>
int main(void){

	int fd[2];

	
	if(pipe(fd) == -1){
		perror("Pipe failed");
		return 1;
	}
	srand(time(NULL));
	

	int vec1[1000];
	int vec2[1000];
	for (int i = 0; i < 2000; i++) {
		if(i<1000)
			vec1[i] = 1 + (rand() % 100);
		else
			vec2[i-1000] = 1 + (rand() % 100);
	}

	
	printf("vec1 : %d\n",vec1[1000]);
	printf("vec2 : %d\n",vec2[1000]);
	
	for(int i=0;i<5;i++){
		if(fork()==0){
			// Child
			close(fd[0]);

			close(fd[1]);

			exit(1);
		}			
	}
	
	
	int total=0;
	for(int i=0;i<5;i++){
		read(fd[0],&total,sizeof(total));
	}
	
	
	// Parent
	close(fd[1]);
	
	
	
	
	
	
	close(fd[0]);
}
