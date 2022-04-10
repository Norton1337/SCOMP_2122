#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>


struct ok{
	char str[3];
	int num; 
	};


int main(){
	struct ok jogo,resp;
	pid_t p;
	int p1[2];
	pipe(p1);
	int d,e,n;
	strcpy(jogo.str,"win");
	jogo.num=1;
	int parent=0;
	for(d=0;d<10;d=d+1){
		if (p=fork()==0){
			close(p1[1]);
			read(p1[0],&resp,sizeof(resp));
			printf("%s--%d\n",resp.str,resp.num);
			exit(resp.num);
			}
		}
		
	
	
	for(e=0;e<10;e=e+1){
		close(p1[0]);
		jogo.num=e+1;
		write(p1[1],&jogo,sizeof(jogo));
		//close(p1[1]);
		sleep(2);
		}
			
	close(p1[1]);
		
	//nao concluido
		
	
	
	return 0;
	
	
	
	
	
	
	
	
	}
