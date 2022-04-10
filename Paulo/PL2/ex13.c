#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>
#include <ctype.h>
#include <time.h>



int main(void){


	int fd1[2];// M1 to M2
	int fd2[2];// M2 to M3
	int fd3[2];// M3 to M4
	int fd4[2];// M4 to A1
	
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

	int sleepTime = 0;
		
	if(fork()==0){
		//Machine M1
		close(fd1[0]);
		int piecePile = 1000;
		while(piecePile!=0){
			
			printf("Cutting 5 pieces!\n");
			piecePile-=5;
			int newPieces = 5;
			write(fd1[1],&newPieces,sizeof(int));
			sleep(sleepTime);
		}
		piecePile=-1;
		write(fd1[1],&piecePile,sizeof(int));
		close(fd1[1]);
		exit(1);
	}
	if(fork()==0){
		//Machine M2
		close(fd1[1]);
		close(fd2[0]);
		int pieces;

		while(pieces!=-1){
			
			read(fd1[0],&pieces,sizeof(int));
			if(pieces==-1){
				write(fd2[1],&pieces,sizeof(int));
				break;
			}
			printf("Folding 5 pieces!\n");
			write(fd2[1],&pieces,sizeof(int));
			sleep(sleepTime);
		}
		
		close(fd2[1]);
		close(fd1[0]);		
		exit(1);
	}
	if(fork()==0){
		//Machine M3
		close(fd2[1]);
		close(fd3[0]);
		
		int pieces;
		int piecesHere = 0;
		while(pieces!=-1){
			
			read(fd2[0],&pieces,sizeof(int));
			if(pieces==-1){
				write(fd3[1],&pieces,sizeof(int));
				break;
			}
			piecesHere+=pieces;
			if(piecesHere==10){
				printf("Welding 10 pieces!\n");
				
				write(fd3[1],&piecesHere,sizeof(int));
				piecesHere-=10;
				sleep(sleepTime);
			}
			
		}
		
		
		close(fd3[1]);
		close(fd2[0]);		
		exit(1);
	}
	if(fork()==0){
		//Machine M4
		close(fd3[1]);
		close(fd4[0]);
		
		int pieces;
		int piecesHere = 0;
		while(pieces!=-1){
			
			read(fd3[0],&pieces,sizeof(int));
			
			if(pieces==-1){
				write(fd4[1],&pieces,sizeof(int));
				break;
			}
			
			piecesHere+=pieces;
			if(piecesHere==100){
				printf("Packing 100 pieces!\n");
				
				write(fd4[1],&piecesHere,sizeof(int));
				piecesHere-=100;
				sleep(sleepTime);
			}
			
		}
		
		
		close(fd4[1]);
		close(fd3[0]);		
		exit(1);
	}


	// Storage A1
	
	close(fd4[1]);
	int pieces;

	int producedParts=0;
	
	while(pieces!=-1){
		read(fd4[0],&pieces,sizeof(int));
		
		if(pieces!=-1){
			producedParts+=pieces;	
		}
		
	}

	printf("\nProduced %d parts!!\n",producedParts);

	

	close(fd4[0]);
	

}
