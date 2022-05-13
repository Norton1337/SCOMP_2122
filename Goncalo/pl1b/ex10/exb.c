#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

static int c=0;

void handle_signal(){
	c=1;
	}



int main(){
	pid_t p;
	p=fork();
	if (p==0){
		signal(SIGUSR1,handle_signal);
		sleep(10);
		if (!c){
			write(STDOUT_FILENO,"To slow, that is why the program will end!",42);
			kill(getppid(),SIGKILL);
			
			}
		

		exit(0);
		
		}
	
	
	
	

	char a[100];
	//alarm(10);
	gets(a);
	//printf("%d",p);
	kill(p,SIGUSR1);
	//alarm(0);
	write(STDOUT_FILENO,"cont!",5);

	sleep(20);
	printf("Successful execution!");
	
	return 0;
	}
