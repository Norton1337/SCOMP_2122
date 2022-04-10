#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
	
int a=0;
void handle_signal(){
	a=a+1;
	printf("SIGUSR1 signal captured, USR1_COUNTER = %d",a);
	
	while(1){
		sleep(2);
		write(STDOUT_FILENO,"I'm working!\n",13);}

	return ;
	}

int main(){
	pid_t p;
	//printf("usr1-cont: ");

	//write(STDOUT_FILENO,"hey",3);

	int a=0;
	struct sigaction act;
	memset(&act, 0, sizeof(struct sigaction));
	sigemptyset(&act.sa_mask);
	sigdelset(&act.sa_mask,SIGUSR1);
	
	act.sa_sigaction = handle_signal;
	act.sa_flags = SA_SIGINFO;
	
	sigaction(SIGUSR1, &act, NULL);
	if (p=fork()==0){
		for (int d=12;d>1;d=d-1){
			sleep(0.01);
			kill(getppid(),d);
			}
		
		}
	
	sleep(200);
	
	
	return 1;
}
