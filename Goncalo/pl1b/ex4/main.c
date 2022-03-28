#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
	
void ok(){
	write(STDOUT_FILENO,"don t press",15);
	return ;
	}

int main(){
	int a;
	struct sigaction act;
	memset(&act, 0, sizeof(struct sigaction));
	sigemptyset(&act.sa_mask); 
	
	act.sa_sigaction = ok;
	act.sa_flags = SA_SIGINFO;
	
	sigaction(SIGINT, &act, NULL);
	scanf("%d",&a);
	printf("aaa");
	
	return 0;
	}
