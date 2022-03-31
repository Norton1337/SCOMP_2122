#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>
#include <time.h>


void handle_ALARM(int signo) {
	write(STDOUT_FILENO, "Too slow, that is why the program will end!\n", 46);
	exit(1);
}



int main() {
	
	struct sigaction act;
	memset(&act, 0, sizeof(struct sigaction));
	sigemptyset(&act.sa_mask); 
	act.sa_handler = handle_ALARM;
	sigaction(SIGALRM, &act, NULL);
	alarm(10);
	char sentence[200];
	fgets(sentence,200,stdin);
	alarm(0);
	int amount=0;
	for(int i = 0;sentence[i]!='\n';i++){
		
		printf("sentence[i]: %c\n",sentence[i]);
		amount++;
	}
	printf("%d\n",amount);
	
	sleep(20);
	printf("Successful execution!\n");
}
