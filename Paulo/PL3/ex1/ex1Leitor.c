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
	int number;
	char name[100];
} student_type;

int main(int argc, char *argv[]) {
	int data_size = sizeof(student_type);
	int fd = shm_open("/ex1", O_RDWR,S_IRUSR|S_IWUSR);
	ftruncate(fd, data_size);
	student_type *student = (student_type*)mmap(NULL,data_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	printf("%d\n", student->number);
	printf("%s\n", student->name);
	int r = munmap(student, data_size); /* disconnects */
	if (r < 0) printf("ERROR"); /* Check error */
	r = close(fd); /* closes */
	if (r < 0) printf("ERROR"); /* Check error*/
	exit(0);
	return 0;
}

