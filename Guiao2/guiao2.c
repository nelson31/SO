#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/wait.h>



int main(int argc, char* argv[]){
	// Exercicio 1
	
	pid_t pidp;
	pidp=getppid();
	char buf[25];
	sprintf(buf, "O pai do processo = %d\n", pidp);


	write(1,buf,sizeof(buf));
	//printf("Identificador processo programa: %d\n", getpid());

	
     

    pid_t pid;
    int status;
	// Exercicio 2  
	// Usar comando (ps -o pid,state)
    
	if((pid=fork())==0){
		//sleep(5);   // Para se tornar orfao
		printf("Identificador processo pai: %d\n",getppid() );
	    printf("Identificador processo programa: %d\n", getpid());	
	    _exit(0);	
	} else {
		sleep(5); // Para o filho ficar no estado Zombie
 		printf("Identificador processo pai: %d\n",getppid() );
	    printf("Identificador processo programa: %d\n", getpid());
	    printf("Pid do filho: %d\n", pid);
	    wait(&status);  // Nao posso por isto se quiser que dê 1
	}
	return 0;

}

