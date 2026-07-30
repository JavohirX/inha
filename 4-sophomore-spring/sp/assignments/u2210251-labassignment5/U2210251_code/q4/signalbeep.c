#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <string.h>

void handler(int sig) 
 {
     static int i, beeps = 0;

    
     printf("BEEP\n"); 
     if(++beeps <10)
       {
        printf("ALARM  FIRED IN SIGINT HANDLER \n Next SIGALRM will be delivered in 1s to Main\n");
	alarm(5); 
	/* Next SIGALRM will be delivered in 1 second */ 
       }
       else
       { 
           printf("BOOM!\n");
            exit(0); 
        } 
 } 

int main()
{
	printf("MAIN - PROGRAM:signalbeep.c LAB ASSIGNMENT5 Q4  SPRING 2024\n");
   	printf("**************************************************************\n");
	
	/* Install SIGALRM handler */ 
  	  signal(SIGALRM, handler); 
	  printf("HANDLER SIGALRM INSTALLED \n");
          printf("ALARM  FIRED IN MAIN \n Next SIGALRM will be delivered in 1s to Main \n");
          alarm(5); 
            /* Next SIGALRM will be delivered in 1s */ 
          
	 while (1) {

		
            ; 
          	/* Signal handler returns control here each time */ 
           } 
   	  printf("**************************************************************\n");
          exit(0);

}
