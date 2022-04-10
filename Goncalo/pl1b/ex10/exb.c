#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int c=0;

volatile sig_atomic_t cont=0;



int main(){
	pid_t p;
	if (p=fork()==0){
		
		sleep(10);
		
		write(STDOUT_FILENO,"To slow, that is why the program will end!",42);
		kill(getppid(),SIGKILL);

		exit(1);
		
		}
	
	
	
	

	char a[100];
	//alarm(10);
	gets(a);
	kill(p,SIGKILL);
	//alarm(0);

	printf("%d\n",strlen(a));
	sleep(20);
	printf("Successful execution!");
	
	return 0;
	}
