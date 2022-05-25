#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


#define STR_SIZE 50
#define NR_DISC 10



typedef struct{
	int numero;
	char nome[STR_SIZE];
	int disciplinas[NR_DISC];
	int ok;
} shared_data_type;



int main(){
	int a;
	pid_t p;
	int fd;
	shared_data_type *addr;
	fd = shm_open("/ok", O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);
	ftruncate (fd, sizeof(shared_data_type)+5);
	addr = mmap(NULL, sizeof(shared_data_type)+5,PROT_READ|PROT_WRITE,MAP_SHARED, fd, 0);
	addr->ok=0;
	
	int maior=0,menor=100;
	float media;
	
	if (fork()!=0){
		printf("numero:");
		scanf("%d",&addr->numero);
		printf("nome:");
		scanf("%s",&addr->nome);
		for (int d=0;d<NR_DISC;d=d+1){
			printf("nota:");
			scanf("%d",&addr->disciplinas[d]);
		}
		addr->ok=1;
		
		
	}
	else{
		
		while(!addr->ok);
		for (int d=0;d<NR_DISC;d=d+1){
			media=media+addr->disciplinas[d];
			if (maior<addr->disciplinas[d]){
				maior=addr->disciplinas[d];
				}
			if (menor>addr->disciplinas[d]){
				menor=addr->disciplinas[d];
				}
			}
		media=media/NR_DISC;
		printf("\nmaior--%d,menor--%d,media--%f",maior,menor,media);
		exit(0);
		
	}
	wait(NULL);
	
	
	
	
	
	

	return 0;
//	ps. a funçao rand() produz sempre os mesmos numeros..apenas ´e usada por uma questao de simplificaçao 
}
