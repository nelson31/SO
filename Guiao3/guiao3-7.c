#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/wait.h>

// Exercicio 7


int size(char* str)
{
    int i;
	for(i=0;str[i]!='\0';i++);
	return i;
}

char** tokenize(char* comando, int* flag){
	char** str = (char**) malloc(20*sizeof(char*)); 
	int i=0;
	char* token;

	while((token = strsep(&comando, " ")) != NULL){
		if(token[0]!='&'){
			str[i] = token;
			i++;
	    } else *flag=1;
    }

    str[i]=NULL;
    return str;
}


int mysystem(char* comando)
{
	char** str; 
	int i=0, status, res, flag=0; pid_t pid;

	str=tokenize(comando,&flag);

	//printf("%d\n",flag );

	if(flag==0 && (pid=fork())==0){
		execvp(str[0], str);

		_exit(1);
	} else if(flag==1 && (pid=fork())==0){

			if((pid=fork())==0){
				execvp(str[0], str);
				_exit(1);
			}
 
			//write(1,"Execução do programa em pano de fundo\n",size("Execução do programa em pano de fundo\n"));
			
			if((res = read(0,comando,20))>0)
    		{
         		strtok(comando,"\n\r");
         		str=tokenize(comando,&flag);

		     	execvp(str[0], str);

				_exit(1);
            }
        }

		waitpid(pid,NULL,0);


		if(WIFEXITED(status)){
			res = WEXITSTATUS(status);
	   	}
	   	else res = -1;


	return res;
	
}



//Falta fazer a parte do |

int main(int argc, char* argv[])
{
	char str[20];
	ssize_t res; int i,status;
	pid_t pid;

    write(1,"Bem vindo ao interpretador de comandos\n",size("Bem vindo ao interpretador de comandos\n"));
    write(1,">",size(">"));
    
    while((res = read(0,str,20))>0)
    {
         strtok(str,"\n\r");
         if((i=strcmp(str,strdup("exit")))==0) break;
         if((pid=fork())==0)
          {
		     //write(1,"Execução do programa inserido\n",size("Execução do programa inserido\n"));
		     mysystem(str);
		     _exit(1);
	      } else 
	      {

	      pid_t wait_ret = wait(&status);

	      write(1,"Pressione 'exit' ou 'CONTROL-D' se quiser sair!\n",size("Pressione 'exit' ou 'CONTROL-D' se quiser sair!\n"));
          write(1,">",size(">"));
          }
         
	}

	write(1,"Adeus!\n",size("Adeus!\n"));
	return 0;
}

