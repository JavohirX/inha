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

void handler1(int sig) /* SIGINT handler */ 
{ 
	printf("Caught SIGINT\n"); 
} 

void handler2(int sig) /* SIGQUIT handler */ 
{ 
	printf("Caught SIGQUIT\n"); 	
} 

void handler3(int sig) /* SIGSTP handler */ 
{ 
	printf("Caught SIGSTP\n");
} 


int main()
{
        printf("MAIN - PROGRAM:multisighandler.c LAB ASSIGNMENT5 Q4  SPRING 2024\n");
   	printf("*****************************************************************\n");

	   /* Install the SIGINT handler */ 
	   printf("Installed(Registered) SIGINT handler \n");
     	    if (signal(SIGINT, handler1) == SIG_ERR) 
         	 unix_error("signal error"); 

	   /* Install the SIGQUIT handler */ 
	   printf("Installed(Registered) SIGQUIT handler \n");
	    if (signal(SIGQUIT, handler2) == SIG_ERR) 
          	 unix_error("signal error"); 
	   
	   /* Install the SIGSTP handler */ 
	   printf("Installed(Registered) SIGSTP handler \n");	
 	    if (signal(SIGTSTP, handler3) == SIG_ERR) 
         	 unix_error("signal error"); 
	
	    printf("MAIN PROCESS NOW WAITING FOR signal (PRESS ^C  ^\\ OR ^Z ) \n");
	    pause(); /* Wait for the receipt of a signal */ 
	
	printf("*****************************************************************\n");
	    exit(0); 
}

