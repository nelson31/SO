#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define MAX 1000
#define SIZE_LINE 50

// Exercicio 2(SERVIDOR)

int numIteracoes=0;

void tratamentoPedido(char* buffer)
{
    //strcpy(buffer,strdup("E o Cri Cri!!!\0"));
    numIteracoes++;
    sprintf(buffer,"%s %d\n",strdup("[Resposta] E o Cri Cri!!!"),numIteracoes);
}


ssize_t readln(int fildes, void *buff, ssize_t tamanho){ // melhorar a versão do readln

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



int parsing(char *line, char *campo[]){

    /* String para a qual vão ser 
    lidos os caracteres ae encontra um 
    espaço */
    char *token;

    token=strsep(&line," ");
    /* Adicionamos ao array 
    de strings campo os "tokens" 
    lidos */
    campo[0]=strdup(token);
    //printf("Campo[0]: %s  %d\n",campo[0],sizeof(campo[0]) ); 
    token=strsep(&line,"");
    campo[1] = strdup(token);
    //free(token);
    //printf("Campo[1]: %s\n",campo[1] ); 
    return 2;
}


int main(int argc, char* argv[])
{
    int pipeC, pipeS, bloq, parsed; 
    char *buffer=(char*)malloc(MAX*sizeof(char));
    char buffer1[MAX];
    int lidos;
    char* campo[2];

    unlink("fifoServ");

    // Criar os fifos
    if(mkfifo("fifoServ",0666)<0)
       perror("CREAT");
    //if(mkfifo("fifoCli",0666)<0)
    //    perror("CREAT");

    /* Abrimos o pipe com nome para 
    receber "pedidos" do cliente */
    pipeS=open("fifoServ", O_RDONLY, 0666);
    /* Abrimos também o pipe para escrever 
    para o servidor ficar sempre a executar 
    em background */
    bloq=open("fifoServ", O_WRONLY, 0666);

   
    while(lidos=readln(pipeS,buffer,MAX))  // ler do Servidor informacao
    {
        parsed=parsing(buffer,campo);
        
        printf("Pedido recebido do Cliente %s: %s\n", campo[0],campo[1]);
    
        tratamentoPedido(buffer1);

        /* Abertura do pipe para dar.
        resposta ao cliente em questão */
        pipeC=open(campo[0],O_WRONLY,0666);
        
        write(pipeC,buffer1,strlen(buffer1));

        /* Fazer free de cada uma das 
        strings do array campo */
        for(int i=0; i<parsed; i++)
            free(campo[i]);

        /* Fechar descritor do pipe que recebe 
        a resposta do servidor */
        close(pipeC);
    }

    close(pipeS);
    close(bloq);


    return 0;
}