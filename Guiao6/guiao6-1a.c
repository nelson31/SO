#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#include <sys/types.h>
#include <sys/stat.h>

// Exercicio 1


// Experimentar fazer num terminal cat > fifo(escrever aqui) e noutro cat fifo

int main(){
	if((mkfifo("fifo", 0666))==-1){
        	perror("pipe");
        }

    return 0;
}

