#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <string.h>


void unix_error(char *msg) /* Unix-style error */
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}

void handler(int sig) /* SIGINT handler */ 
{ 
	printf("Caught SIGINT\n"); 
	exit(0); 
} 

int main()
{
        printf("MAIN - PROGRAM:signalhandler1.c LAB ASSIGNMENT5 Q4  SPRING 2024\n");
   	printf("**************************************************************\n");

	   /* Install the SIGINT handler */ 
	   printf("INSTALLED THE SIGNIT HANDLER \n");
     	   if (signal(SIGINT, handler) == SIG_ERR) 
         	 unix_error("signal error"); 
	   printf("WAITING FOR THE RECEIPT OF A SIGNAL SIGINT - PRESS ^C \n");
	   pause(); /* Wait for the receipt of a signal */ 

	printf("**************************************************************\n");
	exit(0); 
}
