#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
	int a=0, b, c, d;
	b = (int) fork();
	c = (int) getpid(); 
	d = (int) getppid();
	a = a + 5;
	printf("\n a = %d, b = %d, c= %d, d=%d\n",a,b,c,d); 
}


/*
 * a) father's "b" and child's "c" and  both of their "a".
 * 
 */ 
