#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>



int main(){
	int fd[2];
	FILE *fp;
	pid_t pid;
	char input[80]="";
	char output[80]="";
	int a;
	pipe (fd);
	
	pid=fork();
	if (pid>0){
		close(fd[0]);
		fp=fopen("file.txt","r");
		while(fgets(input,80,fp)!=NULL){
			//output=fgets(fp);
			write(fd[1],input,80);
			}
		fclose(fp);
		}
	if (pid==0){
		close(fd[1]);
		while(read(fd[0],output,80)!=NULL){
			printf("%s",output);
			}
		
		
		
		
		
		}
	

	return 0;
	}
