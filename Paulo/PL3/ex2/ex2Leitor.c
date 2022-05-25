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
	int data_size = sizeof(product_type);
	int fd = shm_open("/ex2", O_RDWR,S_IRUSR|S_IWUSR);
	ftruncate(fd, data_size);
	product_type *product = (product_type*)mmap(NULL,data_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	printf("%d\n", product->productCode);
	printf("%s\n", product->description);
	printf("%d\n", product->price);
	int r = munmap(product, data_size); /* disconnects */
	if (r < 0) printf("ERROR"); /* Check error */
	r = close(fd); /* closes */
	if (r < 0) printf("ERROR"); /* Check error*/
	exit(0);
	return 0;
}

