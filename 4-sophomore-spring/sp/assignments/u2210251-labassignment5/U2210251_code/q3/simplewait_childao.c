#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

void unix_error(char *msg)

{

	
	fprintf(stderr, "%s : %s\n", msg, strerror(errno));


	exit(0);

}

pid_t Fork(void)

{

   pid_t  pid;

   if(( pid = fork()) < 0)

	unix_error("Fork error");

   return pid;

}

int main()

{

	
    pid_t wpid, pid[100];  
	
    int  child_status;
	
    int i, n;
	 
     printf("PARENT - PROGRAM:simpwait_childao.c LAB ASSIGNMENT5 Q3  SPRING 2024\n");
     printf("*********************************************************************\n");


    printf("Number of Child processes n=");
	
    scanf("%d", &n);
	

    printf("HELLO FROM PARENT, pid = %d\n", getpid());
	

    for(i=0; i < n; i++)
    if (Fork() == 0 )
    { 
	
          pid[i]= getpid();
	
          printf("HELLO FROM CHILD , pid[%d} = %d\n", i, pid[i]);

          exit(100+i);/*CHILD*/
	
    }
	

    for (i=0; i < n; i++) /*PARENT*/
    {
        wpid = wait(&child_status);

	if(WIFEXITED(child_status))

	  printf("CHILD %d terminated with exit status %d , PARENT PID  = %d\n", wpid, WEXITSTATUS(child_status), getpid());
 	else

	  printf("CHILD %d TERMINATED abnormally, pid = %d\n", wpid, getpid());
	
    }
   printf("*************************************************************************\n"); 

}

