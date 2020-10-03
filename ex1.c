#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
int ex1q1();
int ex1q2(int n);
int ex1q2Arbre(int n);
void arbre(int);

int main(int argc, char *argv[]){
	//ex1q1();
	
	//Début Q2
	if (argc < 2){
		printf("Missing arguments");
		exit(1);
	}	
	else {
		//printf("%d", atoi(argv[1]));
		//fflush(stdout);
		//ex1q2(atoi (argv[1]));
		//arbre(atoi(argv[1]));
			
		ex1q2Arbre(atoi(argv[1]));
	}

	//Fin Q2
}

int ex1q1(){
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
			exit(1);
		}
	}
	//int status;
	//waitpid(-1, &status, 0);
	exit(0);
	
}

int ex1q2(int n){
	for (int i =0; i<n; i++){
		int pid = fork();
		if (pid == 0){
			printf("Mon PID est %d et mon père est %d \n", getpid(), getppid());
			exit(0);
		}
		else{	
			printf("%d \n", i); 
			int status;
			waitpid(pid, &status, 0);
		}
	}
	exit(0);

}
/*
// Je pense que le code ci dessous ne fonctionne pas car le père ne peut être zombie ?
// DOnc si il quitte avant le fils, il ne laisse pas de signal (ou du moins le signal est perdu ?)
int ex1q2Arbre(int n){
	for (int i = 0; i<10; i++){
		int pid = fork();
		if (pid == 0){
			int status;
			printf("PID %d et mon père est %d \n", getpid(), getppid());
			waitpid(getppid(), &status, 0);
		}
		else {
			
			exit(0);
		}
	}
	exit(0);
}
*/ 

int ex1q2Arbre(int n){
	printf("ex1q2Arbre");
	fflush(stdout);
	for (int i = 0; i<n; i++){
		int pid = fork();
		if (pid == 0){
			printf("PID %d et mon père est %d \n", getpid(), getpid());
		}
		else if (pid == -1){
			fprintf(stderr, "Bug ex1q2Arbre");
			exit(1);
		}
		else {
		//Comme on ne met pas de wait, le père peut quitter avant le fils
		//Mais ça doit créer des zombies non ?	
			exit(0);
		}
	}
	exit(0);
}

void arbre(int n) {
	int i;
	printf("Lance %d processus en arbre\n\n",n);
	printf("proc %d fils de %d (shell)\n",getpid(),getppid());
	for (i=0; i<n; i++) {
		if (fork() == 0) { 
			/* fils */
			printf("proc %d fils de %d\n",getpid(),getppid());
		} else {// wait(NULL); pas de wait, ou les p`eres quitent pas assez vite
			exit(0);
		}
	}
}
