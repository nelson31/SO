#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

// Exercicio 1

#define BUFFER_SIZE 1024




int main(int argc, char* argv[])
{
        int fd1 = open("/etc/passwd",O_RDONLY,0777);
        int fd2 = open("saida.txt",O_CREAT | O_TRUNC | O_WRONLY, 0777);
        int fd3 = open("erros.txt",O_CREAT | O_TRUNC | O_WRONLY, 0777);

 
        /* Se quiser guardar os descritores originais
        int fdin = dup(0);
        int fdout = dup(1);
        int fderr = dup(2);
        */

        int nfd1 = dup2(fd1,0);
        int nfd2 = dup2(fd2,1);
        int nfd3 = dup2(fd3,2);

        close(fd1);
        close(fd2);
        close(fd3);

        //fflush(nfd2);

        char* byte;
        ssize_t res;

        while((res = read(nfd1,byte,4))>0){
   	        //fflush(nfd2);
   	        write(nfd2,byte,res);
        }

        fflush(nfd2);

        /* Se quiser voltar a ter os descritores originais

        dup2(fdin,0);
        dup2(fdout,1);
        dup2(fderr,2);
        close(fdin);
        close(fdout);
        close(fderr);
*/

        close(nfd1);
        close(nfd2);
        close(nfd3); 

        return 0;
}
