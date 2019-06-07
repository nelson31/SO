#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024
#define DEZMEGA 1024*1024*10

// Ex.5 ?????????

ssize_t readln(int fildes, void *buf, size_t nbyte)
{
   
   ssize_t res;
   char t;

   int i=0;
   res = read(fildes,&t,1);

   while(t!='\n' && ((ssize_t) i)<nbyte && res>0){
   	      ((char*)buf)[i]=t;
   	      i+=res;
   	      res = read(fildes,&t,1);
   }

   return (ssize_t) i;
}



int main (int argc, char* argv[])
{
   int nbytes = atoi(argv[1]);
   char* byte = malloc(nbytes);
   ssize_t res;

   while((res = readln1(0,byte,nbytes))>0){
   	      write(1,"\t",1);
   	      write(1,byte,res);
   	      write(1,"\n",1);											
   }


	return 0;
}

