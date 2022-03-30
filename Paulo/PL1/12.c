#include <stdio.h>


int spawn_childs(int n){
	
	for(int i=1;i<=n;i++){
		
		if(fork()==0){
			
			
			exit(i*2);
		}
		
	}
	
	
}

int main(){

	spawn_childs(6);

}
