#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>
#include <time.h>


volatile sig_atomic_t continueCounting=1;


int main() {
	
	
	if(fork()==0){
		
		for(time_t start2 = time(NULL);time(NULL)-start2 < 10;){}
		if(continueCounting){
			printf("Too slow, that is why the program will end!\n");
			kill(getppid(),9);
		}
		exit(1);
		
	}
	char sentence[200];
	fgets(sentence,200,stdin);
	
	int amount=0;
	for(int i = 0;sentence[i]!='\n';i++){
		
		printf("sentence[i]: %c\n",sentence[i]);
		amount++;
	}
	printf("%d\n",amount);
	
	sleep(20);
	printf("Successful execution!\n");
}
