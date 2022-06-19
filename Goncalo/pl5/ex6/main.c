#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>



void* men(void *arg){
	
	int a=*((int*) arg);
	
	float d,it,e,k;
	float fl;
	int b;
	//printf("A---->%d\n",a);
	for(d=2;d<=a;d=d+1){
		k=0;
		for(e=2;e<d;e=e+1){
			it=d/e;
			
			fl=d/e;
			//printf("d--%f   e-->%f   it---%f,fl--%f\n",d,e,it,fl);
			b=(int) it;
			if (b==fl){
				//printf("si\n");
				k=1;
				break;
				}
			}
		if(k==0){
			b=(int)d;
			printf("%d\n",b);
			}
		
		
		
		
	}	
	pthread_exit((void*)NULL);
	
}






int main(){
	int array[1000];
	int d;
	scanf("%d",&d);
	pthread_t threads[1];
	pthread_create(&threads[0], NULL,men,(void*) &d);
	

	pthread_join(threads[0], NULL);
	

	
	
	return 0;
	
	
	
	
	}
