#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>


int main(int argc, char* argv[])
{
        
        int p[2];
        char* line = strdup("Ex2 do Guiao de SO");
        char buffer[1];
        int res=1;
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
                   
               while((res=read(p[0],buffer,1))>0){
        	       printf("[FILHO] : read %s from pipe\n", buffer);
               }
        	   close(p[0]);

        	   _exit(0);
        	default:
        	// pai
        	   // fechar descritor de leitura do pai
        	   close(p[0]);

        	   sleep(5);
               res=0;
               for(int i=0;i<strlen(line);i++){
        	       write(p[1],line+i,1);
        	   
                   printf("[PAI] : wrote line %c from pipe\n", line[i]);
               }
                   
        	   close(p[1]);

        	   wait(&status);

        }

        return 0;
}
