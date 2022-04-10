#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int c=0;
void handle_signal(){
	if (c=0){
		write(STDOUT_FILENO,"To slow, that is why the program will end!",42);
		exit(1);
		}

	}





int main(){
	struct sigaction act;
	memset(&act, 0, sizeof(struct sigaction));
	sigemptyset(&act.sa_mask);
	//sigdelset(&act.sa_mask,SIGUSR1);
	
	act.sa_sigaction = handle_signal;
	act.sa_flags = SA_SIGINFO;
	//act.sa_handler = SIG_IGN;
	sigaction(SIGALRM, &act, NULL);
	char a[100];
	alarm(10);
	gets(a);
	alarm(0);
	//act.sa_handler = SIG_IGN;
	//sigdelset(&act.sa_mask,SIGALRM);
	printf("%d\n",strlen(a));
	sleep(20);
	printf("Successful execution!");
	
	return 0;
	}
