#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024
#define DEZMEGA 1024*1024*10

/**
Função que lê uma linha de um dado ficheiro
*/
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
   /* É retornado o número de bytes lidos */
   return (ssize_t)count;
}


// myCat

int main (int argc, char* argv[])
{
   int nbytes,fd;
   if((atoi(argv[1]))>0){ 
   nbytes = atoi(argv[1]);
   fd = 0;}
   else {
   	   nbytes = 8;
   	   fd = open(argv[1],O_RDONLY,0777);
   }

   char *byte=(char*)malloc(nbytes*sizeof(char));;
   ssize_t res;

   while((res = readln(fd,byte,nbytes))>0){
   	      write(1,byte,res);
            //write(1,"\n",1);
   }

   if(fd!=0) close(fd);

   return 0;
}
