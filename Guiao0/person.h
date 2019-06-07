#ifndef ___PERSON_H___
#define ___PERSON_H___

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct person {
	char nome[200];
	int idade;
} Person;

//API
Person new_person(char* nome, int idade);
Person clone_person(Person* p);
void destroy_person(Person* p);
int person_age(Person* p);
void person_change_age(Person* p, int idade);

#endif
