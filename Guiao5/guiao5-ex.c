#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>

// Sistema de encadeamento de pipeline
// Inserir: > <nomeExecutavel> <Args Programa 1> | <Args Programa 2> | ...  | <Args Programa n>

int main (int argc , char**argv){
 
	int **pipes; int i;

	//PARSING
	int contacomandos = 1; // variavel que me conta o numero de comandos a executar
	int iniciocomandos[argc]; // variavel que me marca o inicio de um comando(indice)
	int marcadorPipe = 1; // variavel que me diz se encontrei um | ou não

	for(i = 0; i<argc ; i++){
		if(marcadorPipe){
			// Indica um inicio de uma instrução
			iniciocomandos[contacomandos-1] = i;
			marcadorPipe = 0;
		}else if(!strcmp(argv[i],"|")){
			// indica que encontrei um fim de comando
			contacomandos++;
			argv[i] = NULL;
			marcadorPipe = 1;
		}
	}

	//VERIFICA SE SO TEM 1 COMANDO PARA EXECUTAR
	if(contacomandos-1 == 0){
		if(!fork()){
			execvp(argv[1],argv+1);
			exit(EXIT_FAILURE);
		} 
		wait(0);
		exit(EXIT_SUCCESS);
	}


	//CRIAR PIPES
	pipes = malloc((contacomandos-1)*sizeof(int*));
	for(i=0;i<(contacomandos-1);i++){
		pipes[i] = malloc (2*sizeof(int));
		pipe(pipes[i]);
	}


	//EXECUTA O PRIMEIRO COMANDO
	if(!fork()){
		dup2(pipes[0][1],1);
		close(pipes[0][0]);
		close(pipes[0][1]);
		execvp(argv[1],argv+1);
		exit(EXIT_FAILURE);
	}
	close(pipes[0][1]);
	//EXECUTA OS INTERMEDIOS
	for(i = 1;i<contacomandos-1;i++){
		if(!fork()){
			dup2(pipes[i-1][0],0);
			dup2(pipes[i][1],1);
			close(pipes[i-1][1]);
			close(pipes[i][0]);
			close(pipes[i-1][0]);
			close(pipes[i][1]);
			execvp(argv[iniciocomandos[i]],argv+iniciocomandos[i]);
			exit(EXIT_FAILURE);
		}
		close(pipes[i-1][0]);
		close(pipes[i][1]);
	}

	//EXECUTA O ULTIMO
	if(!fork()){
			dup2(pipes[i-1][0],0);
			close(pipes[i-1][1]);
			close(pipes[i-1][0]);
			execvp(argv[iniciocomandos[i]],argv+iniciocomandos[i]);
			exit(EXIT_FAILURE);
	}

	for(i=0;i<contacomandos;i++){
		wait(0);
	}

	return 0;
}
