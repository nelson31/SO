#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#include <sys/types.h>
#include <sys/stat.h>

// Exercicio 1b  (in)

// A abertura para escrita de um pipe com nome bloqueia até que um
// processo o abra para leitura, e vice-versa

int main(int argc, char* argv[])
{
    int pipe; char buffer[30];
    int lidos;
    if((pipe=open(argv[1],O_WRONLY, 0777))==-1){
    	perror("open");
    }
    else {
    	write(1,"opened fifo for writing\n",24);
    }
	while(lidos=read(0,buffer,30)){
		write(pipe,buffer,lidos);
	}

	close(pipe);


    return 0;
}

