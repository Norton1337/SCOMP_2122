#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>


int array[1000];

typedef struct{
	int number;
	int index;
	}str;


void* search(void *arg){
	str *a=(str*) arg;
	int *resul;
	resul=(int*)malloc(sizeof(int));
	
	int d;
	
	for (d=(a->index*100);d<(a->index*100)+100;d=d+1){
		if (array[d]==a->number){
			*resul=a->index;
			//printf("encontrou:%d==%d por %d--%d\n\n",array[d],a->number,a->index);
			pthread_exit((void*) resul);	
			}
		}
	
	pthread_exit((void*)NULL);	

	
	}




int main(){
	void *value;
	
	str str1[10];
	int d,i,num;
	scanf("%d",&num);
	for (d=0;d<10;d=d+1){
		str1[d].index=d;
		str1[d].number=num;
		}
	
	for(d=0;d<1000;d=d+1){
		array[d]=1000-d;
		}//POPULAR O ARRAY
	
	
	
	pthread_t threads[10];
	for(d=0;d<10;d=d+1){
		pthread_create(&threads[d], NULL,search,(void*) &str1[d]);
		}
	
	for(i=0;i<10;i++){
		pthread_join(threads[i], (void*) &value);
		
		if (value!=0){
			int *resul;
			resul=value;
			printf("Valor encontrado pela thread %d\n",*(resul));
		}
		
	}
		free(value);
	
	
	}
