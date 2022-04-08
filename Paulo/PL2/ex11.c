#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>
#include <ctype.h>
#include <time.h>


int main(void){

	int fd[2]; //parent - child1
	int fd2[2];//child1 - child2
	int fd3[2];//child2 - child3
	int fd4[2];//child3 - child4
	int fd5[2];//child4 - child5
	int fd6[2];//child5 - parent


	
	if(pipe(fd) == -1){
		perror("Pipe failed");
		return 1;
	}

	if(pipe(fd2) == -1){
		perror("Pipe failed");
		return 1;
	}
	if(pipe(fd3) == -1){
		perror("Pipe failed");
		return 1;
	}

	if(pipe(fd4) == -1){
		perror("Pipe failed");
		return 1;
	}
	if(pipe(fd5) == -1){
		perror("Pipe failed");
		return 1;
	}

	if(pipe(fd6) == -1){
		perror("Pipe failed");
		return 1;
	}

	
	for(int i=0;i<5;i++){
		
		if(fork()==0){
			srand((int)time(NULL) % getpid()); 
			int randomNum = 1 + (rand() % 500);
			printf("child[%d] randomNum: %d\n",i,randomNum);
			int parentRandomNum;
			switch(i){
				
				case 0:
					read(fd[0],&parentRandomNum,sizeof(int));
					break;
				case 1:
					read(fd2[0],&parentRandomNum,sizeof(int));
					break;
				case 2:
					read(fd3[0],&parentRandomNum,sizeof(int));
					break;
				case 3:
					read(fd4[0],&parentRandomNum,sizeof(int));
					break;
				case 4:
					read(fd5[0],&parentRandomNum,sizeof(int));
					break;
			}
			if(parentRandomNum>randomNum)
				randomNum=parentRandomNum;
			switch(i){
				
				case 0:
					write(fd2[1],&randomNum,sizeof(int));
					break;
				case 1:
					write(fd3[1],&randomNum,sizeof(int));
					break;
				case 2:
					write(fd4[1],&randomNum,sizeof(int));
					break;
				case 3:
					write(fd5[1],&randomNum,sizeof(int));
					break;
				case 4:
					write(fd6[1],&randomNum,sizeof(int));
					break;

			}
			exit(1);
		}
		
	}
	
	// Parent
	close(fd[0]);
	close(fd6[1]);
	srand((int)time(NULL) % getpid()); 
	int randomNum = 1 + (rand() % 500);
	printf("parent randomNum: %d\n",randomNum);
	write(fd[1],&randomNum,sizeof(int));
	read(fd6[0],&randomNum,sizeof(int));
	printf("Largest Random Number is: %d\n",randomNum);
	close(fd[1]);
	close(fd6[0]);
}
