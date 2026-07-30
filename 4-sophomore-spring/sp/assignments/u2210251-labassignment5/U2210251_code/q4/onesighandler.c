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

void handler(int sig) /* SIG handler */ 
{ 
	if(sig == SIGINT)
	printf("Caught SIGINT\n"); 
	else
	if(sig == SIGQUIT)
	printf("Caught SIGQUIT\n"); 
	else
	if(sig == SIGCHLD)
	printf("Caught SIGCHLD\n");
	
} 

int main()
{
        printf("MAIN - PROGRAM:onesighandler.c LAB ASSIGNMENT5 Q4  SPRING 2024\n");
   	printf("*****************************************************************\n");


          /* Install the SIGINT handler */ 
	   printf("Installed(Registered) SIGINT handler \n");
     	    if (signal(SIGINT, handler) == SIG_ERR) 
         	 unix_error("signal error"); 

	   printf("Installed(Registered) SIGQUIT handler \n");
	    if (signal(SIGQUIT, handler) == SIG_ERR) 
          	 unix_error("signal error"); 

	   printf("Installed(Registered) SIGCHLD handler \n");	
 	    if (signal(SIGCHLD, handler) == SIG_ERR) 
         	 unix_error("signal error"); 
	
	    printf("MAIN PROCESS NOW WAITING FOR signal \n");
	    pause(); /* Wait for the receipt of a signal */ 

	  printf("*****************************************************************\n");
	  exit(0); 
}
