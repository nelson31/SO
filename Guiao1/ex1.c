#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024
#define DEZMEGA 1024*1024*10

/*   Minha versao ex.1
void dezmb(const char* arg)
{
	FILE *arq; int i; 
    arq = fopen(arg,"rw");

	for(i=0;i<DEZMEGA;i++)
	{
		fprintf(arq, "%c", 'a');
	}
	
	fclose(arq);
}
*/

/*  Minha Versao
void mycat()
{
	char buf[50]; int i=0;
	char l=getchar();
	while(l != EOF){
		while(l!='\n')
		{
            buf[i]=l;
            l=getchar();
            i++;
        }
     
        buf[i]='\0';
        //putchar('\n');
        i=0;
	    while(buf[i]!='\0')
		{
            printf("%c", buf[i]);
            i++;
        }
        putchar('\n');
        i=0;
        l=getchar();
	}

}

*/

int main (int argc, char* argv[])
{

	//dezmb(argv[1]);

	//mycat();

    //Podia ter um buffer que me colocava la "a"
    // char buffer[BUFFER_SIZE];

    // Ou: char *buffer = malloc(sizeof(char)*BUFFER_SIZE);
	//populate_buffer(buffer, BUFFER_SIZE);   -> Coloca "a" no buffer


	
	/*
    printf("%d\n",argc );
    for( int i = 0; i < argc; i++ )
	   {
		   printf( "arg %d: %s\n", i, argv[i] );
	   }

    */
	
	int fd;
	int i;


    
	fd = open(argv[1],O_CREAT | O_TRUNC | O_WRONLY, 0777);

	for(i=0;i<DEZMEGA;i++){
		write(fd,"a",1);
	}
/*
	for(i=0;i<DEZMEGA/BUFFER_SIZE;i++)
		res = write(fd,buffer,BUFFER_SIZE);
*/




	return 0;
}



