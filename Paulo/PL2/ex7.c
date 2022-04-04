#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>
#include <ctype.h>
#include <time.h>
int main(void){

	int fd1[2];
	int fd2[2];
	int fd3[2];
	int fd4[2];
	int fd5[2];

	
	if(pipe(fd1) == -1){
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
	
	srand(time(NULL));

	int vec1[1000];
	int vec2[1000];
	for (int i = 0; i < 2000; i++) {
		if(i<1000)
			vec1[i] = 1 + (rand() % 100);
		else
			vec2[i-1000] = 1 + (rand() % 100);
	}


	
	for(int i=0;i<5;i++){
		if(fork()==0){
			// Child
			close(fd1[0]);
			close(fd2[0]);
			close(fd3[0]);
			close(fd4[0]);
			close(fd5[0]);
			int tmp=0;
			for(int k=i*200;k<i*200+200;k++)
				tmp +=vec1[k]+vec2[k];

			
			switch(i){
				case 0:
					write(fd1[1],&tmp,sizeof(tmp));
					break;
				case 1:
					write(fd2[1],&tmp,sizeof(tmp));
					break;
				case 2:
					write(fd3[1],&tmp,sizeof(tmp));
					break;
				case 3:
					write(fd4[1],&tmp,sizeof(tmp));
					break;
				case 4:
					write(fd5[1],&tmp,sizeof(tmp));
					break;	
			}


			close(fd1[1]);
			close(fd2[1]);
			close(fd3[1]);
			close(fd4[1]);
			close(fd5[1]);

			exit(1);
		}			
	}

	// Parent
	close(fd1[1]);
	close(fd2[1]);
	close(fd3[1]);
	close(fd4[1]);
	close(fd5[1]);
	
	int result[5];
	for(int i=0;i<5;i++){
		int tmp;
		switch(i){
			case 0:
				read(fd1[0],&tmp,sizeof(tmp));
				break;
			case 1:
				read(fd2[0],&tmp,sizeof(tmp));
				break;
			case 2:
				read(fd3[0],&tmp,sizeof(tmp));
				break;
			case 3:
				read(fd4[0],&tmp,sizeof(tmp));
				break;
			case 4:
				read(fd5[0],&tmp,sizeof(tmp));
				break;
				
		}
		result[i]=tmp;
		printf("result[%d] = %d\n",i,result[i]);
	}
	
	
	close(fd1[0]);
	close(fd2[0]);
	close(fd3[0]);
	close(fd4[0]);
	close(fd5[0]);
}
