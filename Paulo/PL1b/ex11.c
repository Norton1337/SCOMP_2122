#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>
#include <time.h>

typedef struct {
	char cmd[32];
	int tempo;
} comando; 

volatile sig_atomic_t tooLate =0;

void handle_ALARM(int signo) {
	tooLate = 1;
}

int main() {
	
	struct sigaction act;
	memset(&act, 0, sizeof(struct sigaction));
	sigemptyset(&act.sa_mask); 
	act.sa_handler = handle_ALARM;
	sigaction(SIGALRM, &act, NULL);
	
	
	comando commands[] = {
		{"command1",3},
		{"command2",6},
		{"command3",3},
    };
	for(int i=0;i<sizeof(commands)/sizeof(comando);i++){
		alarm(commands[i].tempo);
		
		printf("%s\n",commands[i].cmd);
		sleep(2);
		if(tooLate==1){
			printf("The command %s didn’t end in its allowed time\n",commands[i].cmd);
			exit(1);
		}
	}
	alarm(0);
	printf("Execution Ended!\n");
	return 1;
}
