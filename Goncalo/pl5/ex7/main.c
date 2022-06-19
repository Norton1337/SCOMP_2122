#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>




typedef struct{
	int numeros[5];
	}str;

int keys[8000][5];
int resul[5];
int index;
pthread_mutex_t mut;

void* func(void *arg){
	str *jogo=(str*) arg;
	
	pthread_mutex_lock(&mut);
	int a=index;
	index++;
	pthread_mutex_unlock(&mut);
	
	int d,e,f;
	
	
	for(d=500*a;d<(500*a)+500;d=d+1){
	
		for(e=0;e<5;e=e+1){
		
			for(f=0;f<5;f=f+1){
				//printf("%d and %d\n",keys[d][e],jogo->numeros[f]);
				if (keys[d][e]==jogo->numeros[f]){
					pthread_mutex_lock(&mut);
					resul[f]++;
					
					pthread_mutex_unlock(&mut);
					}
				
		
				
				}
		
			} 
		
		}
	
	
	pthread_exit((void*)NULL);
	
	}




int main(){

	str jogo;
	int d,e;
	int array[16];
	pthread_t threads[16];
	

	for(d=0;d<5;d=d+1)resul[d]=0;
	
	for (d=0;d<8000;d=d+1){
		for (e=0;e<5;e=e+1)keys[d][e]=(rand() % 48)+1;//POPULAR ARRAY ENTRE 1 A 49
	}
	
	for (d=0;d<16;d=d+1)array[d]=d;
	
	for(d=0;d<5;d=d+1)scanf("%d",&(jogo.numeros[d]));
	

	if((pthread_mutex_init(&mut,NULL))!=0){
		printf("erro na inicializaçao do mutex");
		};
	for(d=0;d<16;d=d+1)pthread_create(&threads[d], NULL,func,(void*) &jogo);
	
	
	
	for(d=0;d<16;d=d+1)pthread_join(threads[d], NULL);
	
	
	for (d=0;d<5;d=d+1)printf("%d-foi encontrado %d\n",jogo.numeros[d],resul[d]);
	return 0;
	
	
	
}
