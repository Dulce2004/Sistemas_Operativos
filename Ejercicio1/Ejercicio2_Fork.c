#include <stdio.h>
#include <unistd.h>

int main(){
	int f;

	f = fork();

	if(f == 0) {
		execl("./Ejercicio1_Hello", "Ejercicio1_Hello", (char*)NULL);
		
	} else{
		printf("%d\n", (int)getpid());
		execl("./Ejercicio1_Hello", "Ejercicio1_Hello", (char*)NULL);
	}
	
	return 0;
}