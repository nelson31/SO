#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>


// Exercicio 5

int main(int argc, char* argv[])
{
        
        int p[3][2];
        int status;
        int i=0;

        while(i<3){
            if(pipe(p[i]) ==-1){
                 perror("pipe");
                 return -1;
            }
            i++;
        }

        //grep -v ˆ# /etc/passwd | cut -f7 -d: | uniq | wc -l.

        if(fork()==0){
            close(p[0][0]);
            close(p[1][0]);
            close(p[1][1]);
            close(p[2][0]);
            close(p[2][1]);

            dup2(p[0][1],1);
            close(p[0][1]);
            execlp("grep","grep","-v","ˆ#","/etc/passwd",NULL);
        }

        if(fork()==0){
            close(p[0][1]);
            dup2(p[0][0],0);
            close(p[0][0]);
            close(p[1][0]);
            dup2(p[1][1],1);
            close(p[1][1]);
            close(p[2][0]);
            close(p[2][1]);
            execlp("cut","cut","-f7","-d:",NULL);
        }

        if(fork()==0){
            close(p[0][0]);
            close(p[0][1]);
            dup2(p[1][0],0);
            close(p[1][0]);
            close(p[1][1]);
            close(p[2][0]);
            dup2(p[2][1],1);
            close(p[2][1]);
            execlp("uniq","uniq",NULL);
        }

        if(fork()==0){
            close(p[0][0]);
            close(p[0][1]);
            close(p[1][0]);
            close(p[1][1]);
            dup2(p[2][0],0);
            close(p[2][0]);
            close(p[2][1]);
            execlp("wc","wc","-l",NULL);
        }
        
        close(p[0][0]);
        close(p[0][1]);
        close(p[1][0]);
        close(p[1][1]);
        close(p[2][0]);
        close(p[2][1]);

        // Necessario fechar os descritores antes do wait
        for(i=0;i<4;i++)
            wait(&status);
               

        return 0;
}
