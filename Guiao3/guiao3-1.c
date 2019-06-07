#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/wait.h>


// Exercicio 1

int main(int argc, char* argv[])
{
    char* exec_args[] = {"ls","-l",NULL};


    printf("Execucao do comando 'ls -l'\n" );

    //execl("/bin/ls","ls","-l",NULL);

    //execlp("bin","ls","-l",NULL);

    //execv("/bin/ls",exec_args);

    execvp("ls",exec_args);

	return 0;
}
