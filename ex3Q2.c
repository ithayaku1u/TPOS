#include <signal.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int pid1, pid2; 

void handler2to1 (int n){
	printf("I am going to quit - SIGUSR2");
	exit(0);
}

void handler1to2(int n){
	printf("1 send SIGUSR2");
	fflush(stdout);
	kill(pid1, SIGUSR2);
	exit(0);
}

int main(int argc, char *argv[]){
	pid1 = fork();
	if (pid1 == 0){
		struct sigaction sig1n;
		struct sigaction sig1o;
		memset(&sig1n, 0, sizeof(sig1n));
		sig1n.sa_handler = handler2to1;
		sigaction(SIGUSR2, &sig1n, &sig1o);	
	
		pause();
	}

	pid2 = fork();
	if (pid2 == 0){
		struct sigaction sig2n;
		struct sigaction sig2o;
		memset(&sig2n, 0, sizeof(sig2n));
		sig2n.sa_handler = handler1to2;
		sigaction(SIGUSR1, &sig2n, &sig2o);	
	
		pause();
	}
	sleep(1);
	printf("test");	
	kill(pid2, SIGUSR1);
	sleep(2);
	return 0;

}
