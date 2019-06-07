#include <stdio.h>
#include <signal.h>

void handler_alarm()
{
	printf("Wake Up !!! 7am in the morning !!!!\n");
	fflush(stdout);
}

int main()
{
	signal(SIGALRM,handler_alarm);
	alarm(5);
	printf("Nao incomode, estou a dormir num colchao Molaflex ...\n");
	pause();
	printf("... vou ficar na sorna mais 5 minutos ...\n");
	sleep(5);
	exit(1);	
}





