#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024
#define DEZMEGA 1024*1024*10


struct read
{
   char* string;
   int inicio;
   int tamanho;
};


struct read* init(int tam)
{
   struct read* r = malloc(sizeof(struct read));
   r->inicio = 0; r->tamanho=0;
   r->string = malloc(tam*(sizeof (char)));
   return r;
}


int create_buffer(int fildes, struct read *buf, size_t nbyte)
{
   ssize_t res;
   
   res = read(fildes,buf->string,nbyte);

   buf->inicio = 0;

   buf->tamanho = res;

   return (int) res;
}

int destroy_buffer(struct read *buf)
{
   free(buf->string);
   free(buf);
   return 0;
}

ssize_t readln(struct read *buf, void *result, size_t nbyte)
{
   int j=0,i;

   for(i=buf->inicio;i<buf->tamanho;i++,j++){
      if(buf->string[i]=='\n'){
         ((char*)result)[j++]='\0';
         //((char*)result)[j++]=buf->string[i];
         //((char*)result)[j++]='\0'; 
         //buf->inicio++;
         break;
      }
      ((char*)result)[j]=buf->string[i];
   }

   if(buf->inicio==buf->tamanho && buf->string[j]=='\0') {
      i=-1; /*((char*)result)[++j]='\0';*/ /*buf->inicio++;*/
   }
   else { buf->inicio+=j; /*((char*)result)[j]='\0';*/}

   return (ssize_t) j;
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

   char* byte=malloc(nbytes);
   ssize_t res;

   struct read* buf=init(nbytes);

   buf->tamanho = create_buffer(fd,buf,nbytes);

   while((res = readln(buf,byte,buf->tamanho))>0){
   	      write(1,byte,res);
            if(buf->inicio!=buf->tamanho || byte[res-1]=='\0') write(1,"\n",1);
            if(buf->inicio==buf->tamanho){
               destroy_buffer(buf); buf=init(nbytes);
               buf->tamanho = create_buffer(fd,buf,nbytes);
            }
            //printf("%d\n",buf->tamanho);
            //printf("%d\n",buf->inicio);
   }

   if(fd!=0) close(fd);

   return 0;
}