#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

void unix_error(char *msg) /* Unix-style error */
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}

pid_t Fork(void)
{
    pid_t pid;

    if ((pid = fork()) < 0)
        unix_error("Fork error");
    return pid;
}


int main()
{
   pid_t pid[100];  

   int i, n;
	 
	
   printf("PARENT - PROGRAM:zombie_childpause.c LAB ASSIGNMENT5 Q2  SPRING 2024\n");
   printf("****************************************************************\n");
   
   printf("Number of Child processes n=");
   scanf("%d", &n);
	
    printf("HELLO FROM PARENT, PARENT PID  = %d\n", getpid());
    
    for(i=0; i < n; i++)
     {
       printf("PARENT : NOW I AM CREATING CHILD NO-%d \n",i);
       if (Fork() == 0 )
        { 
	
          pid[i]= getpid();
	  printf("*******************************************************************************************************************************\n");
	  printf("* HELLO FROM CHILD , My pid is %d, I HAVE BEEN PAUSED                                                                      *\n", pid[i]);
	  printf("* OPEN ANOTHER TERMINAL KILL ME BY GETTING MY PID using ps -l AND THEN EXECUTE THE COMMAND kill -9 mypid                      *\n");
	  printf("* NOW I HAVE BECOME A ZOMBIE(DEFUNCT)  PROCESS - CHECK MY STATUS BY USING THE COMMAND ps -la                                  *\n");
	  printf("* IF  YOU WANT TO  KILL ALL ZOMBIE PROCESSES  THEN KILL THE PARENT PROCESS BY USING kill -9 parentpid AND CHECK USING ps -la  *\n");
	  printf("*******************************************************************************************************************************\n");
          pause();
	  exit(0);/*CHILD*/
	
        }

       }
     printf("PARENT : I AM STILL RUNNING Running - PARENT PID = %d\n", getpid());
     printf("*******************************************************\n");
     while (1)
        ; /* Infinite loop */
    	
}
