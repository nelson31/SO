#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

// Exercicio 2



int main(int argc, char* argv[])
{
	int i;

	for(i=1;i<argc;i++){
		if(fork()==0){
			execlp(argv[i],argv[i],NULL);
		}
	}

	for(i=1;i<argc;i++)
		wait(NULL);
	return 0;	
}
