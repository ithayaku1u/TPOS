#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

/* 
 //Part 1
int main(int argc, char *argv[]){
	if (argc < 2){
		fprintf(stderr, "Not enough input");
		exit(1);
	}
	else{
		execvp(argv[1],argv+1);
		exit (0);
	}
}
*/

//Part 2
int main(int argc, char *argv[]){
	if (argc < 2){
		fprintf(stderr, "Not enough input");
		exit(1);
	}
	for (int i = 0; i < 5; i++){
		int pid = fork();
		if (pid == 0){
			execvp(argv[1], argv+1);

		}	
		else if (pid == -1){
			fprintf(stderr, "Error while forking");
			exit(1);
		}
		else {
			int statut;
			if (waitpid(-1, &statut, 0) > 0){// ON rentre si un des processus fils se termine ?
				if (WIFEXITED(statut)!= 0 && WEXITSTATUS(statut)!=0){
					printf("erreur, interruption prog");
					exit(1);
				}
		
			}
		}
	}
}
