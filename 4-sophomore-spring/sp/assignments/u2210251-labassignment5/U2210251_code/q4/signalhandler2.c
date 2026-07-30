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

void handler(int sig) /* SIGQUIT handler */ 
{ 
	printf("Caught SIGQUIT\n"); 
	exit(0); 
} 

int main()
{
	printf("MAIN - PROGRAM:signalhandler2.c LAB ASSIGNMENT5 Q4  SPRING 2024\n");
   	printf("**************************************************************\n");

          /* Install the SIGQUIT handler */ 
	  printf("INSTALLED THE SIGQUIT HANDLER \n");
     	   if (signal(SIGQUIT, handler) == SIG_ERR) 
         	 unix_error("signal error"); 
  	  printf("WAITING FOR THE RECEIPT OF A SIGNAL SIGQUIT - PRESS ^\\ \n");
	  pause(); /* Wait for the receipt of a signal */ 
   	
	printf("**************************************************************\n");
	exit(0); 
}
