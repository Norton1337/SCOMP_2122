#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
int main(void) {
	pid_t child;
	int i, status;
	
	for(i=0;i<2;i++){
		
		child = fork();
		if(child==0){
			sleep(i+1);
			exit(i+1);
		}
		
	}
	for(i=0;i<2;i++){
		wait(&status);
		printf("Estado do filho: %d\n",WEXITSTATUS(status));
		
	}
	
	
	
}
