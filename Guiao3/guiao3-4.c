#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char* argv[])
{
	pid_t pid;

	if ((pid = fork()) == 0) {
	
		execvp("./guiao3-3", argv);
		
		_exit(-1); 		
	} else {
	
	wait(NULL);
    
    }
	
	return 0;
}
