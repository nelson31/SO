#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


// Exercicio 3

int main(int argc, char* argv[])
{
	pid_t pid = 1;
	int i, j, c, valor, status, lin=10, col=50, conta = 0;

	pid_t pids[10];

	for(i=0;i<10;i++) pids[i]=0;
    
    // Buscar o valor que se pretende procurar
	if (argc == 4) {
		valor = atoi(argv[1]);
		lin= atoi(argv[1]);
		col= atoi(argv[2]);
		if (!((valor > 0) && (valor <= 500))) {
			perror("O valor é maior do que 500");
			return -1;
		}
	} else if (argc == 2){
		valor = atoi(argv[1]);
		if (!((valor > 0) && (valor <= 500))) {
			perror("O valor é maior do que 500");
			return -1;
		}
	} else {
			perror("I/O ERROR");
		    return -1;
	}

    int matriz[lin][col];

	srand(time(NULL));
	for (i = 0; i < lin; i++) 
		for (j = 0; j < col; j++) 
			matriz[i][j] = rand() % 500 + 1;  // 500 - nº maximo que os valores da matriz podem ter
		
	
    // Podia ter criado tantos processos filhos quanto linhas
    printf("Criei 10 processos filhos\n");

    for (c = 0; c < 10; c++)  // pid>0 para que so o pai itere
        if ((pids[c]=fork()) == 0) {
			//pids[c]=getpid();
			for (i = c; i < lin; i += 10) 
				for (j = 0; j < col; j++) 
					if (matriz[i][j] == valor) {
						_exit(1);
					}
		    _exit(0);
		} 

    // Processo pai vai esperando por todos os processos filhos
	for (i = 0; i < 10; i++){
		pid_t terminated_pid = wait(&status);
	    
	    if(WIFEXITED(status) && WEXITSTATUS(status)==1){
                printf("[pai] process(filho) %d exited. exit code: %d\n", terminated_pid , WEXITSTATUS(status));
                printf("Processo %d encontrou o valor %d !\n",terminated_pid,valor);
                for(int l=0;l<10;l++){
					if(pids[l]!=0) kill(pids[l],SIGKILL);
				}
				//break;
			   }
			   else {
			    printf("[pai] process(filho) %d exited.\n", terminated_pid);
			    for(int l=0;l<10;l++){
					if(pids[l]==terminated_pid) {
						pids[l]=0;
						break;
				}
			   }
			   
    }
}

    sleep(15);

	return 0;
}
