#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/wait.h>


// Exercicio 3

int main(int argc, char* argv[])
{
    int i = 0;
	printf("Numeros de argumentos = %d\n", argc);

	while(argv[i] != NULL){
		printf("O indice %d tem o argumento: %s\n", i, argv[i]);
		i++;
	} 


	return 0;
}