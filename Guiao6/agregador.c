#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define MAX 1024
#define SIZE_LINE 50

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

int main(int argc, char* argv[]){

	unlink("agrega.txt");
	int file = open("agrega.txt",O_CREAT | O_RDWR,0666);
	char buf[MAX];
	char buf1[MAX];
	int lidos,lidos1,ret;

	//printf("%ld\n",strlen(buf));

	while((lidos=readln(0,buf,MAX))>0){
		//write(1,buf,lidos); write(1,"\n",1);
		while((lidos1=readln(file,buf1,MAX))>0 && (ret=strcmp(buf,buf1))!=0){
			lseek(file,lidos1,SEEK_CUR);
		}
		if((ret=strcmp(buf,buf1))!=0){
			//write(1,buf,lidos);
			//write(1,"\n",1);
			//buf[lidos]='\n';
			write(file,buf,lidos);
			//write(1,buf,lidos);
			write(file,"\n",1);
		}
		lseek(file,0,SEEK_SET);
	}
	close(file);

	int file1 = open("agrega.txt",O_RDONLY,0666);

	while((lidos=readln(file1,buf,MAX))>0){
		write(1,buf,lidos);
		write(1,"\n",1);
	}
	close(file1);
	return 0;
}
