#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define MAX 1000

// Exercicio 2(CLIENTE)


ssize_t readln(int fildes, void *buff, ssize_t tamanho){ 

	int count=0;
	char c;
	/* Enquanto não tivermos lido o nº de bytes 
	pedidos e enquanto houver bytes para ler */
	while(count<tamanho && read(fildes,&c,1)){
		/* Se o caracter lido for 
		um \n saimos do ciclo */
		if(c=='\n'){
			((char*)buff)[count]='\0';
			break;
		}
		/* Colocamos o caracter no 
		buffer passado como argumento */
		((char*)buff)[count]=c;
		/* Aumentamos à variável que 
		conta o número de bytes lidos */
		count++;
	}
	/* É retornado o número 
	de bytes lidos */
	return (ssize_t)count;
}



int main(int argc, char* argv[])
{
    int pipeC, pipeS; 
    char* buffer1 = (char*) malloc(MAX*sizeof(char));
    char buffer2[MAX], buffer3[MAX];
    int lidos;

    char nomePIPE[10];

    if((pipeS=open("fifoServ",O_WRONLY,0777))<0){
    	perror("open");
    }

    /* obter o pid do processo do 
	programa para receber a resposta do servidor */
	int pid=(int)getpid();
	/* Atribuir o nome ao pipe*/
	sprintf(nomePIPE,"fifo%d",pid);

    //printf("%s\n",nomePIPE );

    if(mkfifo(nomePIPE,0666)<0)
        perror("CREAT");

    //write(pipeS,nomePIPE,lidos);

    printf("Cliente com o pid: %s\n", nomePIPE);

    pipeC=open(nomePIPE,O_RDWR,0666);

	while(lidos=readln(0,buffer1,MAX)) {
		
		/* Juntar o nome do pipe para resposta */
		sprintf(buffer2,"%s %s\n",nomePIPE,buffer1);

		//printf("Mensagem: %s\n", buffer2);

		write(pipeS,buffer2,strlen(buffer2));	
	
		
		lidos=read(pipeC,buffer3,MAX);  // ler a resposta

		//sprintf(buffer3,"Resposta do Servidor recebida: %s\n",buffer4);
		
		//write(1,buffer3,lidos+sizeof("Resposta do Servidor recebida: \n"));
		write(1,buffer3,lidos);

		//sprintf(buffer3,"Resposta do Servidor recebida: %s\n",buffer4);

	}

	close(pipeC);

	close(pipeS);

	unlink(nomePIPE);

    return 0;
}
