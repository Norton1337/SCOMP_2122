#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

typedef struct {
	int productCode;
	char description[100];
	int price;
} product_type;

int main(int argc, char *argv[]) {
	shm_unlink("/ex2");
	int data_size = sizeof(product_type);
	int fd = shm_open("/ex2", O_CREAT|O_EXCL|O_RDWR,S_IRUSR|S_IWUSR);
	ftruncate(fd, data_size);
	product_type *product = (product_type*)mmap(NULL,data_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	printf("Insert product code: ");
	scanf("%d",&product->productCode);
	getchar();
	printf("\nInsert description: ");
	scanf("%s",product->description);
	getchar();
	printf("\nInsert price: ");
	scanf("%d",&product->price);
	getchar();
	getchar();


	
	int r = munmap(product, data_size); /* disconnects */
	if (r < 0) printf("ERROR"); /* Check error */
	r = shm_unlink("/ex2"); /* closes */
	if (r < 0) printf("ERROR"); /* Check error*/
	exit(0);
	return 0;
}

