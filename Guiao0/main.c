#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "person.h"


int main(){
	Person nelson = new_person("Nelson",19);

	printf(" A primeira idade é : %d\n", person_age(&nelson));

	Person new_nelson = clone_person(&nelson);
	person_change_age(&new_nelson,23);
	printf("A idade do clone é : %d\n", new_nelson.idade);

	destroy_person(&nelson);
	//destroy_person(&new_nelson);

	return 0;
}



