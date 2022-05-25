#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define N1 1
#define N2 1
#define N3 1

typedef struct {
	int newInt;
	char newString[256];
} newStruct; 


int main(void){

	int fd[2];
	pid_t pid;
	if(pipe(fd) == -1){
		perror("Pipe failed");
		return 1;
	}
	pid_t pid = fork();
	if(pid > 0){
		// Parent:
		close(fd[0]);
		newStruct ns;

		printf("Insira um int: ");
		scanf("%d",&ns.newInt);
		while(getchar()!='\n');
		printf("Insira uma string: ");
		fgets(ns.newString,256,stdin);
		/*
		int newInt;
		int newString[256];
		write(fd[1],&newInt, sizeof(int));
		write(fd[1], &newString, sizeof(char[256]));
		*/
		write(fd[1], &ns, sizeof(newStruct));
		
		close(fd[1]);
	} else{
		// Child:
		close(fd[1]);
		/*
		int parentInt;
		char parentString[256];
		read(fd[0], &parentInt, sizeof(int));
		read(fd[0], parentString, sizeof(int));
		*/
		newStruct parentStruct;
		read(fd[0], &parentStruct, sizeof(newStruct));
		
		printf("Parent int = %d\n",parentStruct.newInt);
		printf("Parent String = %s\n",parentStruct.newString); 
		close(fd[0]);
		}
	
}
