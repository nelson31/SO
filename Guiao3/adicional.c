#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/wait.h>


// Exercicio adicional

int main(int argc, char* argv[])
{
    
    printf("Execucao do comando './guiao3-1 atraves de um exec'\n" );

    execl("/home/utilizador/SO/Guiao3/guiao3-1","./guiao3-1",NULL);
    
    // O programa ja nao executa esta parte do programa
    printf("reached return");

	return 0;
}

// Podia ter feito -> export PATH=$PATH ... -> e depois usar execp
