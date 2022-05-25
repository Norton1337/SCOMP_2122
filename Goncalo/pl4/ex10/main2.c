#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>



typedef struct {
	int index;
	
	
	struct records{
		int number;
		char name[20];
		char address[80];
	}rec[100];
	
} shared_data_type;



//este exercicio ´e constituido pelo main.c(insert)/main2.c(consultar por numero)/main3.c(consultar tudo)


int main(){
	pid_t p;
	int fd;
	int d,e,a;
	sem_t *sem;
		
	sem_unlink("sem");
	
	shared_data_type *addr;
	fd = shm_open("/ok", O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);
	ftruncate (fd, sizeof(shared_data_type)+5);
	addr = mmap(NULL, sizeof(shared_data_type)+5,PROT_READ|PROT_WRITE,MAP_SHARED, fd, 0);
	
	if ((sem =sem_open("sem", O_CREAT, 0644,0)) == SEM_FAILED) {
		perror("Error in sem_open()");
		exit(0);
	}
	
	

		
	void list_all(){
		
	for (d=0;d<addr->index;d=d+1){
			printf("\n\nnumber:%d\nname:%s\naddress:%s\n\n",addr->rec[d].number,addr->rec[d].name,addr->rec[d].address);
			}
		}
	
	
	while(1){
		printf("\n\nnumero da pessoa:");
		scanf("%d",&a);
		for (d=0;d<addr->index;d=d+1){
			if (addr->rec[d].number==a){
				printf("\n\nnumber:%d\nname:%s\naddress:%s\n\n",addr->rec[d].number,addr->rec[d].name,addr->rec[d].address);
				}
			}
		
		
		
		
		
		
		
		}
	
	
	
	
	
	
	
	
	
	
	sem_unlink("sem");

	
	
	
	
	

		
		
		
		
	
	

	return 0;
}
