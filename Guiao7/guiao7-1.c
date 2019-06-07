#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

// Exercicio 1

int contador = 0;
int flag=1;
unsigned int segundos=0;

void handler_alarm(int signum)
{
	printf("[SIGALRM] ACORDA!!!!\n");
	alarm(1);
	segundos++;
}

void handler_int(int signum)
{
	printf("[SIGINT] Numero de segundos até ao momento: %d\n",segundos);
	contador++;
}

void handler_quit(int signum)
{
	printf("[SIGQUIT] Numero de CTRL+C feitos: %d\n",contador);
	flag=0;
}

int main()
{
	signal(SIGALRM,handler_alarm);
	signal(SIGINT,handler_int);
	signal(SIGQUIT,handler_quit);
	
	alarm(1);
	//pause();
    printf("Estou a dormir ...\n");
	while(flag){
		pause();
    }

	return 0;	
}
