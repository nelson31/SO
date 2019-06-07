#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>



// Exercicio 4

int main(int argc, char* argv[])
{
        
        if(argc>3){
        int fdin = open(argv[1],O_RDONLY,0777);
        int fdout = open(argv[2],O_CREAT | O_TRUNC | O_WRONLY, 0777);
        } else {printf("%s\n", ERROR ); return -1;}
 

        int nfdin = dup2(fdin,0);
        int nfdout = dup2(fdout,1);
        
        close(fdin);
        close(fdout);
        

        char* byte;
        ssize_t res;
        pid_t pid;
        int status;

        if((pid=fork())==0){

        execlp(argv[3], argv[3], NULL);

        _exit(1);
        } else {

        pid_t wait_ret = wait(&status);

        if(WIFEXITED(status)){
            res = WEXITSTATUS(status);
        }
        else res = -1;

        }
 

        close(nfdin);
        close(nfdout);

        return 0;
}