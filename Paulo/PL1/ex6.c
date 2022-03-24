#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	int status=0;
	int i;
	//int status;
	pid_t child;
	for (i = 0; i < 4; i++) {
		child = fork();
		if (child == 0) {
			printf("im a child %d\n",i);
			sleep(1); /*sleep(): unistd.h*/
			exit(i);
		}

	}
	
	 for(int k=0;k<4;k++){
		if(child%2==0)
			wait(&status);
		printf("Estado do filho: %d\n",WEXITSTATUS(status));
		
	}
} 

/*
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 */
