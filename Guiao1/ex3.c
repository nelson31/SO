#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024
#define DEZMEGA 1024*1024*10

// Ex.3 myCat

int main (int argc, char* argv[])
{
   int nbytes = atoi(argv[1]);
   char* byte = malloc(nbytes);
   ssize_t res;

   while((res = read(0,byte,nbytes))>0){
   	      write(1,byte,res);
   }


	return 0;
}


