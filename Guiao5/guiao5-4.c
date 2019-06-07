#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>


int main(int argc, char* argv[])
{
        
        int p[2];
        int res=1;
        int status;

        if(pipe(p) ==-1){
        	perror("pipe");
        	return -1;
        }

        if(fork()==0){
            close(p[0]);
            dup2(p[1],1);
            close(p[1]);
            execlp("ls","ls","/etc",NULL);
        }
        if(fork()==0){
            close(p[1]);
            dup2(p[0],0);
            close(p[0]);
            execlp("wc","wc","-l",NULL);
        }
        
        close(p[0]);
        close(p[1]);
        // Necessario fechar os descritores antes do wait
        for(int i=0;i<2;i++)
            wait(&status);

        return 0;
}
