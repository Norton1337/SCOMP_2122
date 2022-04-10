#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>


void handle_USR1(int signo){
	write(STDOUT_FILENO, "\nCatch USR1!\n", 13);
}
int main(int argc, char *argv[]){
	struct sigaction act;
	int a;
	memset(&act, 0, sizeof(struct sigaction));
	sigemptyset(&act.sa_mask); /* No signals blocked */
	//signal(SIGUSR1,handle_USR1);
	act.sa_handler = handle_USR1;
	sigaction(SIGUSR1, &act, NULL);
	sleep(50);
	/* SIGUSR1 will now be captured and handled (ANSI C). */
	/* (...) */
	printf("hehe");
	scanf("%d",&a);
	
	return 1;
}
