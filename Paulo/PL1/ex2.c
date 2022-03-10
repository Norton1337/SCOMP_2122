#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
	printf("I'm..\n");
	pid_t p1 = fork(); 
	if (p1 == 0) {
		printf("I'll never join you!\n");
	} else {
		printf("the..\n");
		pid_t p2 = fork();
		if (p2 == 0) {
			printf("I'll never join you!\n");
		} else {
			printf("father!\n");
			pid_t p3 = fork();
			if (p3 == 0) {
				printf("I'll never join you!\n");
			}
		}
		
	}
}
