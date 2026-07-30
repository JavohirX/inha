#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
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
    pid_t wpid, pid[100];  
	
    int  child_status;
	
    int i, n;
	 

    printf("PARENT - PROGRAM:waitpid_childao.c LAB ASSIGNMENT5 Q3  SPRING 2024\n");
    printf("*********************************************************************\n");
	
    printf("Number of Child processes n=");
	
    scanf("%d", &n);
	

    printf("HELLO FROM PARENT, pid = %d\n", getpid());
	

     	/* Parent creates N children */ 

     for (i = 0; i < n; i++) 
	 if ((Fork()) == 0) /* Child */ 
	  { 
	
            pid[i]= getpid();
	
            printf("HELLO FROM CHILD , pid[%d] = %d\n", i, pid[i]);

            exit(100+i);/*CHILD*/
	
         }
	 

	/* Parent reaps N children in no particular order */ 
        printf("PARENT REAPING CHILD IN NO PARTICULAR ORDER \n");
	while ((wpid = waitpid(-1, &child_status, 0)) > 0) 
	{ 
	     if(WIFEXITED(child_status))

	       printf("CHILD %d terminated with exit status %d , PARENT PID = %d\n", wpid, WEXITSTATUS(child_status), getpid());

 	     else

	       printf("CHILD %d TERMINATED abnormally \n", wpid);
	
	} 
   printf("*************************************************************************\n");

	 /* The only normal termination is if there are no more children */ 
	 if (errno != ECHILD) 
	     unix_error("waitpid error"); 
	  exit(0); 

}
