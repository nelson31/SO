#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#define TAM 1000000

int main(int argc, char *argv[]){

	//Gerar ficheiro para inserir nos PIPES
	int fildes=open("SCRIPT.txt", O_CREAT | O_RDWR, 0777);

	int i=0;

	char buff[40];
	sprintf(buff,"Esta tudo bem?\n");
	while(i<TAM){
		
		write(fildes,buff,strlen(buff));

		i++;
	}
	close(fildes);
	return 0;
}
