#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>



int main(){
	int fd[2];
	pid_t pid;
	char frase[80]="";
	
	pipe (fd);
	
	pid=fork();
	printf("%d\n",pid);
	
	if (pid>0){
		
		sprintf(frase,"%d",pid);
		close(fd[0]);
		write(fd[1],frase,80);
		close(fd[1]);
		}
	
	
	if (pid==0){
		
		close(fd[1]);
		read(fd[0],frase,80);
		close(fd[0]);
		write(STDOUT_FILENO,frase,80);
		}
	return 1;
	
	}
