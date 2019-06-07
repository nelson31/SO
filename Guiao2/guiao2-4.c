#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/wait.h>


// Exercicio 4

int main(int argc, char* argv[]){
    pid_t pid;
    int status;

	for(int i=1;i<=10;i++)
		if((pid=fork())==0){
			printf("[proc #%d] pid: %d\n", i, getpid());
			_exit(i);
		} 

	for(int i=1;i<=10;i++){
			pid_t terminated_pid = wait(&status);
			
			if(WIFEXITED(status)){
				printf("[pai] process(filho) %d exited. exit code: %d\n", terminated_pid , WEXITSTATUS(status));
			}
			else {
			    printf("[pai] process(filho) %d exited.\n", terminated_pid);	
			}
		}

	return 0;
}
