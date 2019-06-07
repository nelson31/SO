#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/wait.h>


// Exercicio 5

int main(int argc, char* argv[]){
    pid_t pid;
    int status;

    // Cria primeiro os filhos e depois é que passa para a outra parte
	for(int i=1;i<=10;i++){
			
			if((pid=fork())==0){
				
			printf("[proc #%d] pid: %d\n", i, getpid());

		    } else {
		       pid_t terminated_pid = wait(&status);
			   
			   if(WIFEXITED(status)){
				printf("[pai] process(filho) %d exited. exit code: %d\n", terminated_pid , WEXITSTATUS(status));
			   }
			   else {
			    printf("[pai] process(filho) %d exited.\n", terminated_pid);	
			   }

			   _exit(0);
		    }
		}

	return 0;
}
