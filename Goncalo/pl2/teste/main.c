#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>



int main(){
	int fd[2];
	pid_t pid;
	char input[80]="";
	char output[80]="";
	int a;
	int b;
	pipe (fd);
	
	
	pid=fork();
	
	if (pid>0){
		scanf("%d",&a);
		//sprintf(input,"%d",a);
		close(fd[0]);
	
		write(fd[1],&a,sizeof(a));
		
		close(fd[1]);
		

		}
	
	
	if (pid==0){
		
		close(fd[1]);
		
		write(STDOUT_FILENO,"1-",2);
		read(fd[0],&b,sizeof(b));

		write(STDOUT_FILENO,&b,sizeof(b));

		close(fd[0]);

		}
	return 1;
	
	}
