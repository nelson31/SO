#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "person.h"


#define FILENAME "person.txt"

// Função que cria uma pessoa 
// char=1 byte
// int = 4 bytes
// long = 8 bytes
// char* = 8 bytes (64 bits), 4 bytes(32 bits)
// int* = 8 bytes(64 bits), 4 bytes(32 bits)

Person new_person (char *nome, int idade)
{
	Person new;
	size_t n = strlen(nome) + 1;
	//new.nome = malloc(sizeof(char[n]));
	memcpy(new.nome,nome,n);
	new.idade = idade;
	return new;
}

Person clone_person (Person* p)
{
	Person clone;
	memcpy(clone.nome,p->nome,n);
	//clone.nome = strdup(p->nome);
	clone.idade = p->idade;
	return clone;
}


void destroy_person(Person* p)
{
	free(p->nome);
        //free(p); nao posso fazer isto pk nao fiz malloc(quando se faz isto e alocado espaço na heap)
        // Como nao se alocou espaço na heap e o Person existe na stack da main Se se fizer este free da Asneira!!!!!
}

int person_age(Person* p)
{
	return p->idade;
}


void person_change_age(Person* p, int idade)
{
	p->idade = idade;
}

// Guiao 1  ?????

void save_person(Person*p){
    int fd = open(FILENAME, O_RDWR, 0600);

    write(fd,p->name,sizeof(p->name));
    write(fd,p->age,sizeof(p->age));
}

void update_age_and_persist(Person*p, int age){
	int fd = open(FILENAME, O_RDWR, 0600);

	lseek(fd,-sizeof(Person),SEEK_END);

	read(fd,p,sizeof(Person));

	printf("Read Person name %s age- %d\n",p->name,p->age);


}



