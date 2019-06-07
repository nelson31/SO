#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/wait.h>

// Exercicio 6

int mysystem(char* comando)
{
	char* str[20]; int i=0, status, res; pid_t pid;
	char* token;

	while((token = strsep(&comando, " ")) != NULL){
	str[i] = token;
	i++;
    }

    str[i]=NULL;

/*
	token = strtok(comando," ");
	for(i=0; token != NULL ;i++)
	{
		str[i] = token;
		token = strtok(NULL," ");
	}
	str[i]=NULL;
*/

	if((pid=fork())==0){
		execvp(str[0], str);

		_exit(1);
	} else {

	pid_t wait_ret = wait(&status);

	if(WIFEXITED(status)){
		res = WEXITSTATUS(status);
	}
	else res = -1;

    }

	return res;
	
}


int main(int argc, char* argv[])
{
    
    //system("ls -l");

    mysystem(strdup("ls -l"));
	
	return 0;
}

