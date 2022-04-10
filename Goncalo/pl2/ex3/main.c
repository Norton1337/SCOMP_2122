#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>



int main(){
	pid_t p;
	int fd[2];
	pipe(fd);
	int saida;
	p=fork();
	if(p>0){
		close(fd[0]);
		write(fd[1],"Hello World",11);
		write(fd[1],"Goodbye",7);
		close(fd[1]);
		wait(&saida);
		printf("\n%d,,%d",p,saida);
		
		}
		
	if(p==0){
		char out[20]="";
		close(fd[1]);
		read(fd[0],out,18);
		printf("%s",out);
		exit(2);
	}
	return 0;
	
	
	
	
	
	}
