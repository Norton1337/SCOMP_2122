//VERSÃO 1
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

#define N1 2
#define N2 1
#define N3 1



typedef struct {
	int currentNumber;
	int numeros[100];
} vetor_type;

int main(int argc, char *argv[]) {

	
	
	
	int fd[2];
	pid_t pid, pid2,pid3;
	if(pipe(fd) == -1){
		perror("Pipe failed");
		return 1;
	}
	
	pid = fork();
	if(pid > 0){
		//produtor
		close(fd[0]);
		int vetorNumeros[100];
		srand((unsigned int) time(NULL));
	
		//60 iterações a simular 1 min
		for(int k=0;k<60;k++){
	
			for(int i=0;i<100;i++){
				vetorNumeros[i] = rand() % 100;
			}
			
			write(fd[1], &vetorNumeros, sizeof(int[100]));
		
			sleep(1);
		
		}

		
		
		
		close(fd[1]);
		exit(0);
	} else{
		pid2 = fork();
		if(pid2>0){ 
			//processos A1
			close(fd[1]);
	
			//inicializar memoria partilhada
			int data_size = sizeof(vetor_type);
			int fdA1 = shm_open("/A1",  O_CREAT|O_EXCL|O_RDWR,S_IRUSR|S_IWUSR);
			int fdA1A2 = shm_open("/A1A2",  O_CREAT|O_EXCL|O_RDWR,S_IRUSR|S_IWUSR);
			ftruncate(fdA1, data_size);
			ftruncate(fdA1A2, data_size);
			vetor_type *sharedMemoryA1 = (vetor_type*)mmap(NULL,data_size,PROT_READ|PROT_WRITE,MAP_SHARED,fdA1,0);
			vetor_type *sharedMemoryA1A2 = (vetor_type*)mmap(NULL,data_size,PROT_READ|PROT_WRITE,MAP_SHARED,fdA1A2,0);
			
			//criar semafros
			sem_t *semA1;
			sem_t *semA1A2;
			semA1 = sem_open("/semA1", O_CREAT, 0644,1);
			semA1A2 = sem_open("/semA1A2", O_CREAT, 0644,1);
		
			
			for(int i=0;i<N1;i++){
				int a = fork();
				if(a>0){
					while(1){
						
						//receber vetor de int pelo pipe
						read(fd[0], &sharedMemoryA1->numeros, sizeof(int[100]));
						srand((unsigned int) time(NULL));
						sleep(rand() % 2);
						sem_wait(semA1);
						
						while(sharedMemoryA1->currentNumber<100){
							

							sharedMemoryA1->numeros[sharedMemoryA1->currentNumber]++;
							sharedMemoryA1->currentNumber++;
							
						}
						
						//enviar novos dados para A2
						sem_wait(semA1A2);
						sharedMemoryA1A2=sharedMemoryA1;
						sem_post(semA1A2);
						
						
						sharedMemoryA1->currentNumber=0;	
						sem_post(semA1);
						

						
						
					}
					exit(0);
				}
			}
			close(fd[0]);
			exit(0);
		}else{
			pid3 = fork();
			if(pid3>0){ 
				//processos A2
				
				
				//inicializar memoria partilhada
				int data_size = sizeof(vetor_type);
				int fdA2 = shm_open("/A2",  O_CREAT|O_EXCL|O_RDWR,S_IRUSR|S_IWUSR);
				int fdA1A2 = shm_open("/A1A2",  O_CREAT|O_EXCL|O_RDWR,S_IRUSR|S_IWUSR);
				int fdA2A3 = shm_open("/A2A3",  O_CREAT|O_EXCL|O_RDWR,S_IRUSR|S_IWUSR);
				ftruncate(fdA2, data_size);
				ftruncate(fdA1A2, data_size);
				ftruncate(fdA2A3, data_size);
				vetor_type *sharedMemoryA2 = (vetor_type*)mmap(NULL,data_size,PROT_READ|PROT_WRITE,MAP_SHARED,fdA2,0);
				vetor_type *sharedMemoryA1A2 = (vetor_type*)mmap(NULL,data_size,PROT_READ|PROT_WRITE,MAP_SHARED,fdA1A2,0);
				vetor_type *sharedMemoryA2A3 = (vetor_type*)mmap(NULL,data_size,PROT_READ|PROT_WRITE,MAP_SHARED,fdA2A3,0);
				//criar semaforos
				sem_t *semA2;
				sem_t *semA1A2;
				sem_t *semA2A3;
				semA1A2 = sem_open("/semA1A2", 0644,0);
				semA2 = sem_open("/semA2", O_CREAT, 0644,1);
				semA2A3 = sem_open("/semA2A3", O_CREAT, 0644,1);

				
				for(int i2=0;i2<N2;i2++){
					int b = fork();

					if(b>0){
						
						while(1){
														
							sem_wait(semA1A2);
							sharedMemoryA2=sharedMemoryA1A2;
							sem_post(semA1A2);
							
							srand((unsigned int) time(NULL));
							sleep((rand() % 3)+1);
							sem_wait(semA2);
							while(sharedMemoryA2->currentNumber<100){
								

								sharedMemoryA2->numeros[sharedMemoryA2->currentNumber]+=10;
								sharedMemoryA2->currentNumber++;
								
							}
							//enviar novos dados para A3
							sem_wait(semA2A3);
							sharedMemoryA2A3=sharedMemoryA2;
							sem_post(semA2A3);
							
							sharedMemoryA2->currentNumber=0;	
							sem_post(semA2);

						}
						exit(0);
					}
				}
			}else{
				//processos A3
				
				
				
				//inicializar memoria partilhada
				int data_size = sizeof(vetor_type);
				int fdA3 = shm_open("/A3",  O_CREAT|O_EXCL|O_RDWR,S_IRUSR|S_IWUSR);
				int fdA2A3 = shm_open("/A2A3",  O_CREAT|O_EXCL|O_RDWR,S_IRUSR|S_IWUSR);
				ftruncate(fdA3, data_size);
				ftruncate(fdA2A3, data_size);
				vetor_type *sharedMemoryA3 = (vetor_type*)mmap(NULL,data_size,PROT_READ|PROT_WRITE,MAP_SHARED,fdA3,0);
				vetor_type *sharedMemoryA2A3 = (vetor_type*)mmap(NULL,data_size,PROT_READ|PROT_WRITE,MAP_SHARED,fdA2A3,0);
				
				//criar semaforos
				sem_t *semA3;
				sem_t *semA2A3;
				semA3 = sem_open("/semA2", O_CREAT, 0644,1);
				semA2A3 = sem_open("/semA2A3", O_CREAT, 0644,0);

				for(int i3=0;i3<N3;i3++){
					int c = fork();

					if(c>0){

						while(1){

							sem_wait(semA2A3);
							sharedMemoryA3=sharedMemoryA2A3;
							sem_post(semA2A3);
							
							srand((unsigned int) time(NULL));
							sleep(rand() % 2);
							sem_wait(semA3);
							while(sharedMemoryA3->currentNumber<100){

								sharedMemoryA3->numeros[sharedMemoryA3->currentNumber]+=100;
								printf("A3 PID %d - [%d] = %d\n",getpid(),sharedMemoryA3->currentNumber,sharedMemoryA3->numeros[sharedMemoryA3->currentNumber]);
								sharedMemoryA3->currentNumber++;
								
							}
							sharedMemoryA3->currentNumber=0;
							sem_post(semA3);
							
						}
						exit(0);
					}
				}
				
			}
			
		}
		
		
		
	}
	
	int status=0;
	for(int parent=0;parent<N1+N2+N3;parent++){
		wait(&status);
	}
	shm_unlink("/A1");
	shm_unlink("/A1A2");
	shm_unlink("/A2A3");
	shm_unlink("/A2");
	sem_unlink("/semA1");
	sem_unlink("/semA2");
	sem_unlink("/semA1A2");
	sem_unlink("/semA2A3");
    return 0;
}
