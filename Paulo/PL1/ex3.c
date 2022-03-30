#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
/*
 * a)	 7 processes are created 
 * 
 * c) 	each child prints SCOMP 1 time and so does the father for a total
 * 		of 8 prints.
 * 
 * 
 * 
 * 
 */ 
int main(void) {

	fork(); fork(); fork();
	printf("SCOMP!\n");

}
