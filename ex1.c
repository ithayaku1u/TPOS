#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
int ex1();

int main(){
	ex1();

}

int ex1(){
	for (int i = 0; i<10; i++){
		int pid = fork();
		if (pid == 0){
			//On est dans le fils
			for (int j = 0; j<10; j++){
				printf("%d", i);
				fflush(stdout);
			}
			exit(0);
		}
		else if (pid == -1){
			fprintf(stderr, "Error process creation");
		}
	}
	int status;
	waitpid(-1, &status, 0);
	exit(0);
	
}



