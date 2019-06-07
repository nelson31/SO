#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/wait.h>

// Exercicio 5

int main(int argc, char* argv[])
{
	pid_t pid;
    int i=1;
        
    for(i=1;i<argc;i++)
	    if ((pid = fork()) == 0) {
	
		    execlp(argv[i], argv[i], NULL);
		
		    _exit(-1); 		
	    }
        
    for(i=1;i<argc;i++)
               wait(NULL);
        
	
	return 0;
}
