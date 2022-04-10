#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>


int main(){
	int p1[2],p2[2];
	pipe(p1);
	pipe(p2);
	pid_t p;
	p=fork();
	int credito=20,fim=0;
	int input,output,num1,num2,bet,dinheiro;
	
	if (p>0){
		close(p1[0]);
		close(p2[1]);
		}
	if (p==0){
		close(p1[1]);
		close(p2[0]);
		}
	
	
	
	while(!fim){
		//sleep(2);
		if (p>0){
			
			num1=rand() % 6;
			
			if (credito>=5){
				printf("si\n");
				input=1;
				}
			else{
				printf("no\n");
				input=0;
				fim=1;
			}
			
			write(p1[1],&input,sizeof(int));
			//close()
			
		
			//credito=credito-5;

			
			
			
			if((read(p2[0],&num2,sizeof(int)))!=NULL){
				
				credito=credito-5;
				printf("num1:%d num1:%d\n",num1,num2);
				if(num1==num2){
					printf("ganhou\n");
					credito=credito+10;
					}
				write(p1[1],&credito,sizeof(int));

			}
			
			
			
			}




		if (p==0){
			read(p1[0],&output,sizeof(int));
			
			
			
			if(output==1){
				
				bet=rand() % 5;
				
				write(p2[1],&bet,sizeof(int));
				read(p1[0],&dinheiro,sizeof(int));
				printf("%d\n",dinheiro);

				
				}
			else{
				printf("sair de jogo\n");
				exit(0);
				}
				
			}
		
		
		
		

		
		}
	return 0;
	}
