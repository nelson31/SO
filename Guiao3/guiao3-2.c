#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/wait.h>


// Exercicio 2

int main(int argc, char* argv[])
{
    pid_t pid;
    int status;

	if((pid=fork())==0){
		printf("[filho] pid: %d\n", getpid());
		execl("/bin/ls","ls","-l",NULL);
		_exit(0);
	} else {
		pid_t terminated_pid = wait(&status);
		printf("[pai] process(filho) %d exited. exit code: %d\n", terminated_pid , WEXITSTATUS(status));
	}

	return 0;
}