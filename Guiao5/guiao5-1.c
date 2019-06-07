#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>


int main(int argc, char* argv[])
{
        
        int p[2];
        char line[] = "Guiao 5 de SO";
        char buffer[20];
        int res;
        int status;

        if(pipe(p) ==-1){
        	perror("pipe");
        	return -1;
        }

        switch(fork()){
        	case -1:
        	  perror("fork");
        	  return -1;
        	case 0:
        	//FILHO
        	   // fechar descritor de escrita do filho
        	   close(p[1]);

        	   // o res é para saber quantos lemos 
        	   printf("waiting for data ...\n");

                   //close(p[0]); se colocassemos isto aqui havia um SIGPIPE

        	   res = read(p[0],&buffer,sizeof(buffer));

        	   printf("[FILHO] : read %s from pipe\n", buffer);

        	   close(p[0]);

        	   _exit(0);
        	default:
        	// pai
        	   // fechar descritor de leitura do pai
        	   close(p[0]);

        	   //sleep(5);

        	   write(p[1],&line,sizeof(line));

        	   printf("[PAI] : wrote line %s from pipe\n", line);

        	   close(p[1]);

        	   wait(&status);

        }

        return 0;
}