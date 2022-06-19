#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
//PS ERRO DE interpretação neste exercicio ´e suposto que os comboios com a mesma direçao possam precorrer a mesma estrada ao mesmo tempo, no entanto esta resoluçao est´a feita para apenas um comboio andar numa estrada de cada vez 

pthread_mutex_t mut[3];

typedef struct{
	int numero_comboio;
	int local_atual; 
	int origem;
	int destino;
	}comboios;
	
	
	
//ESTRADAS DE ACESSO PARA CADA CIDADE
               //A   B    C     D 
int mapa[4][4]={
			   {-1,   1,   0,    0},//A
			   {1,   -1,   1,    1},//B
			   {0,   1,   -1,    0},//C
			   {0,   1,   0,    -1},//D
			   };
			   
//SEMAFORO DA ESTRADA 
int semaf[4][4]={
			   {-1,   1,   0,    0},//A
			   {1,   -1,   2,    3},//B
			   {0,   2,   -1,    0},//C
			   {0,   3,   0,    -1},//D
			   };




void* func(void *arg){
	comboios *comb=(comboios*) arg;
	int atual,d;
	int tempo=0;
	
	
	while(1){
		printf("comboio %d,cidade atual %d,cidade origem-%d,cidade destino-%d\n",comb->numero_comboio,comb->local_atual,comb->origem,comb->destino);
		//TENTAR IR PARA CIDADE DE DESTINO CASO CONTRARIO IR PARA A CIDADE B
		
		if (mapa[comb->local_atual][comb->destino]==1){
			//printf("aqui1\n");
			
			pthread_mutex_lock(&mut[semaf[comb->local_atual][comb->destino]]);
			//pthread_sleep(10);
			sleep(5);
			atual=comb->local_atual;
			comb->local_atual=comb->destino;
			pthread_mutex_unlock(&mut[semaf[atual][comb->destino]]);
			}
		else{
			if(mapa[comb->local_atual][comb->destino]== -1){
				
				break;
				}
			else{
				//printf("aqui2\n");
				
					//printf("aqui3\n");
				pthread_mutex_lock(&mut[semaf[comb->local_atual][1]]);
				//pthread_sleep(10);
				sleep(5);
				atual=comb->local_atual;
				comb->local_atual=1;
				pthread_mutex_unlock(&mut[semaf[atual][1]]);
			}
			
			
			}
			
		tempo=tempo+5;//cada estrada demora 5s a ser precorrida
		}
	printf("comboio %d chegou ao destino,tempo->%d\n",comb->numero_comboio,tempo);
		
	
	
	
	
	pthread_exit((void*)NULL);
	
	
	
	}




int main(){
	pthread_t threads[2];
	int d;
	comboios comboio[2];
	
	for (d=0;d<3;d=d+1)pthread_mutex_init(&mut[d],NULL);
	
	comboio[0].numero_comboio=0;
	comboio[1].numero_comboio=1;
	
	//CIDADES A-0  B-1 C-2 D-3
	comboio[0].origem=3;
	comboio[0].local_atual=3;
	comboio[0].destino=0;
	
	comboio[1].origem=0;
	comboio[1].local_atual=0;
	comboio[1].destino=1;
	
	for (d=0;d<2;d=d+1)pthread_create(&threads[d], NULL,func,(void*) &comboio[d]);
	
	
	
	for (d=0;d<2;d=d+1)pthread_join(threads[d], NULL);
	
	
	}

