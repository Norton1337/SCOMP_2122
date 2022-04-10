#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

#include <ctype.h>


int main(){
	pid_t p;
	int fd[2];
	int fq[2];
	pipe(fd);
	pipe(fq);
	p=fork();
	char output[255]="";
	char input[255]="";
	char resp[255]="";
	
	if (p>0){
		close(fd[1]);
		read(fd[0],output,255);
		for (int d;d<sizeof(output);d=d+1){
			output[d]=toupper(output[d]);
			}
		//printf("2-");
		//printf("%s",output);
		close(fq[0]);
		write(fq[1],output,255);
		}
		
	if (p==0){
		//printf("1-");
		scanf("%s",input);
		close(fd[0]);
		write(fd[1],input,255);
		close(fq[1]);
		read(fq[0],resp,255);
		//printf("3-");
		printf("%s",resp);
		}
		
	return 0;
	
	
	
	
	}
