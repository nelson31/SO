#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_CLIENTS 5

int main()
{
	int i;
	//int dfichin[NUM_CLIENTS];
	int dfichin;
	/* Abertura de cada ficheiro para 
	ser lido por cada um dos clientes*/
	//for(i=0; i<NUM_CLIENTS; i++){
	//	dfichin[i] = open("SCRIPT.txt", O_RDONLY, 0777);
	//}
	/* Executar o servidor num 
	processo filho */
	if(fork()==0){
		execl("/home/utilizador/SO/Guiao6/Servidor","./Servidor",NULL);
	}
	else{
		/* Criar tantos processos filhos 
		quantos clientes quiser a comprar */
		for(i=0; i<NUM_CLIENTS; i++){
			if(fork()==0){
				dfichin = open("SCRIPT.txt", O_RDONLY, 0777);
				dup2(dfichin,0);
				close(dfichin);
				execl("/home/utilizador/SO/Guiao6/Cliente","./Cliente",NULL);
			}
		}
		for(i=0; i<NUM_CLIENTS; i++)
			wait(NULL);

		printf("Programa terminado...\nServidor em execução...");
		wait(NULL);
	}
	return 0;
}
