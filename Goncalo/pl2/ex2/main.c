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
	pipe (fd);
	
	
	pid=fork();
	
	if (pid>0){
		scanf("%d",&a);
		close(fd[0]);
		
		write(fd[1],&a,sizeof(a));
		scanf("%s",input);
		write(fd[1],input,80);
		close(fd[1]);
		

		}
	
	
	if (pid==0){
		
		close(fd[1]);
		int b;
		write(STDOUT_FILENO,"1-",2);
		read(fd[0],&b,sizeof(b));
		printf("%d",b);
		
		write(STDOUT_FILENO,"2-",2);
		read(fd[0],output,80);
		printf("%s",output);
		close(fd[0]);

		}
	return 1;
	
	}
