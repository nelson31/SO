#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>


int main(int argc, char* argv[])
{
				
		int p[2];
		char* line=(char*) malloc(1024*sizeof(char));
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

				dup2(p[0],0);

				close(p[0]);

				printf("Execucao do wc\n");

        	    execlp(strdup("wc"),strdup("wc"),NULL);

			default:
				// pai
				// fechar descritor de leitura do pai
				close(p[0]);

				int res;
				while((res=read(0,line,sizeof(line)))!=0){

					write(p[1],line,res);
				}

				close(p[1]);

				wait(&status);


			}

		return 0;
}

