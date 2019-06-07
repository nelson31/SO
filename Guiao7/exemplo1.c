#include <stdio.h>
#include <signal.h>
#include <sys/types.h>

int ctrl_c_counter = 0;

void ctrl_c_handler(int signum)
{
	printf("CTRL+C\n");
	ctrl_c_counter++;
}

int main(int argc, char* argv[])
{
	if(signal(SIGINT,ctrl_c_handler)==SIG_ERR){
        perror("SIGINT failed");
    }
    
    while(ctrl_c_counter < 3){
         printf("Working...\n");
         sleep(1);
    }

	return 0;	
}
