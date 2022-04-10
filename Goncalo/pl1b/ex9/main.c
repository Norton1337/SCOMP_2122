#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int cont=0;
void handle_signal(){
	cont=1;
	return ;
	}
	
int main(){
	
	pid_t p;
	
	p=fork();
	
	if (p>0){
		sleep(3);
		//task A
		write(STDOUT_FILENO,"3",1);
		kill(p,SIGUSR1);
		}
	if (p==0){
		struct sigaction act;
		memset(&act, 0, sizeof(struct sigaction));
		sigemptyset(&act.sa_mask);
		//sigdelset(&act.sa_mask,SIGUSR1);
	
		act.sa_sigaction = handle_signal;
		act.sa_flags = SA_SIGINFO;
		sigaction(SIGUSR1, &act, NULL);
		//write(STDOUT_FILENO,"filho ",6);
		int a=(rand() % 5);
		//printf("%d",a);
		sleep(a);
		write(STDOUT_FILENO,"task b",6);
		//task b
		while(!cont){
			
			}
		write(STDOUT_FILENO,"task C",6);
	}
	
	return 0;
	
	
	
	}
