#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>



struct outp{
	int num;
	char str[80];
	};



int main(){
	int fd[2];
	pid_t pid;
	char input[80]="";
	char output[80]="";
	int a;
	pipe (fd);
	
	
	pid=fork();
	
	if (pid>0){
		struct outp out;
		scanf("%d",&a);
		out.num=a;
		scanf("%s",input);
		strcpy(out.str,input);
		close(fd[0]);
		write(fd[1],&out,sizeof(out));
		close(fd[1]);

		}
		if (pid==0){
		struct outp in;
		close(fd[1]);
		read(fd[0],&in,sizeof(in));
		printf("%d",in.num);
		printf("%s",in.str);
		}

	return 0;
	}
	
