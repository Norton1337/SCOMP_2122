#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>
#include <ctype.h>
#include <time.h>


typedef struct {
	int id;
	int readerID;
}request;

typedef struct {
	char name[256];
	double price;
}product;


int main(void){

	int fd[2];	//shared pipe
	int fd1[2];
	int fd2[2];
	int fd3[2];
	int fd4[2];
	int fd5[2];

	
	if(pipe(fd) == -1){
		perror("Pipe failed");
		return 1;
	}

	if(pipe(fd1) == -1){
		perror("Pipe failed");
		return 1;
	}
	if(pipe(fd2) == -1){
		perror("Pipe failed");
		return 1;
	}

	if(pipe(fd3) == -1){
		perror("Pipe failed");
		return 1;
	}
	if(pipe(fd4) == -1){
		perror("Pipe failed");
		return 1;
	}

	if(pipe(fd5) == -1){
		perror("Pipe failed");
		return 1;
	}

	
		

	for(int i=0;i<5;i++){
		if(fork()==0){
			
			close(fd[0]);
			srand(time(NULL));
			sleep(1 + (rand() % 5));
			int productID = 1 + (rand() % 10);
			
			request newProduct;
			newProduct.id=productID;
			newProduct.readerID=i;
			
			write(fd[1],&newProduct,sizeof(request));
			product products;
			switch(i){
				
				case 0:
					read(fd1[0],&products,sizeof(product));
					break;
				case 1:
					read(fd2[0],&products,sizeof(product));
					break;
				case 2:
					read(fd3[0],&products,sizeof(product));
					break;
				case 3:
					read(fd4[0],&products,sizeof(product));
					break;
				case 4:
					read(fd5[0],&products,sizeof(product));
					break;
			}
			printf("product name: %s, price: %f\n",products.name,products.price);
			close(fd[1]);
			exit(1);
		}
		
	}	

	// Parent
	
	close(fd[1]);
	product products[10] = {{"product1", 10},{"product2", 20},{"product3", 30},{"product4", 40},
		{"product5", 50},{"product6", 60},{"product7", 70},{"product8", 80},{"product9", 90},{"product10", 100}};
	request childRequest;
	
	read(fd[0],&childRequest,sizeof(request));
	printf("id: %d\nreaderID: %d\n",childRequest.id,childRequest.readerID);
	
	switch(childRequest.readerID){
				
		case 0:
			write(fd1[1],&products[0],sizeof(product));
			break;
		case 1:
			write(fd2[1],&products[1],sizeof(product));
			break;
		case 2:
			write(fd3[1],&products[2],sizeof(product));
			break;
		case 3:
			write(fd4[1],&products[3],sizeof(product));
			break;
		case 4:
			write(fd5[1],&products[4],sizeof(product));
			break;
	}
	close(fd[0]);
	

}
