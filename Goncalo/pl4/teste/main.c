#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h> 
#include <semaphore.h>
#include <string.h>
#include <time.h>

typedef struct {
	//int index;
	int var1[100];
} shared_data_type;





int main(int argc, char *argv[]) {
	pid_t a;
	int pd[2];
	pipe(pd);
	int d,n,b,e,fim,idx,k;
	sem_t *sem[3];
	int fd1,fd2;
	
	
	shared_data_type *addr;
	fd1 = shm_open("/ok", O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);
	ftruncate (fd1, sizeof(shared_data_type)+5);
	addr = mmap(NULL, sizeof(shared_data_type)+5,PROT_READ|PROT_WRITE,MAP_SHARED, fd1, 0);
	srand((unsigned int) time (NULL));
	
	shared_data_type *addr2;
	fd2 = shm_open("/ok", O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);
	ftruncate (fd2, sizeof(shared_data_type)+5);
	addr2 = mmap(NULL, sizeof(shared_data_type)+5,PROT_READ|PROT_WRITE,MAP_SHARED, fd2, 0);
	
	

	if ((sem[0] = sem_open("/semEx1", O_CREAT, 0644,0)) == SEM_FAILED) {
        perror("Error in sem_open()");
		exit(1);
    }
    if ((sem[1]= sem_open("/semEx2", O_CREAT, 0644,0)) == SEM_FAILED) {
        perror("Error in sem_open()");
		exit(1);
    }
    if ((sem[2] = sem_open("/semEx3", O_CREAT, 0644,0)) == SEM_FAILED) {
        perror("Error in sem_open()");
		exit(1);
    }
    //addr->index=0;
    //addr2->index=0;
    
    
    for(d=0;d<3;d=d+1){
		k=sem_getvalue(sem[d],&k);
		//printf("%d--%d\n",d,k);
		}
  
    
    
    int array[100];
    
    
    
    
    for(d=0;d<3;d=d+1){
		
		if (fork()==0){
			
			if (d==0)sem_post(sem[0]);
			
			
			sem_wait(sem[d]);
			
			
			//processo 1
			if (d==0){
					
				//popular o array
					
					for (b=0;b<100;b=b+1){
						array[b]=(rand() % 100)+1;
						
					
					
					
					}
					//esperar um segundo e depois enviar para a memoria partilhada
					sleep(1);
					for (b=0;b<100;b=b+1){
						addr->var1[b]=array[b];
						
					
					}
					
					sleep(rand() % 3);
					
			}
			
		
				//processo 2
			if (d==1){
				
				sleep((rand() % 3)+1);//tempo aleatorio
				
				
				//array recebe todos os elementos do vetor com a soma feita(+10)
				for (b=0;b<100;b=b+1){
					array[b]=addr->var1[b] +10 ;
					
				
				}
				//A2 coloca array na memoria partilhada   
				for (b=0;b<100;b=b+1){
					addr2->var1[b]=array[b];
					
				
				}
				
				
				
				
			}
				
				
				
				//processo 3
			if (d==2){
				
				
				sleep(rand() % 3);//tempo aleatorio
				
				
				//array recebe todos os elementos do vetor com a soma feita(+100)
				for (b=0;b<100;b=b+1){
					array[b]=addr2->var1[b] +100 ;
					
				
				}
				//A2 coloca array na memoria partilhada   
				close(pd[0]);
				write(pd[1],&array,sizeof(array)*100);
				close(pd[1]);
				
				
				
				
				
				}
			
			
			
			sem_post(sem[d+1]);
			exit(0);
			
			}
		}
	
		
    
    for (fim=0;fim<3;fim=fim+1)wait(NULL);
    close(pd[1]);
    
    read(pd[0],&array,sizeof(array)*100);
    
    for(int t =0;t<100;t=t+1){
		printf("%d\n",array[t]);
		}
    
    
    
    
    
    
    
	
    return 0;
}
