#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <sys/wait.h>

#define N 20

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
   
    pid_t pid[N], wpid;
    int i, child_status;


     printf("PARENT - PROGRAM:waitclkchild.c LAB ASSIGNMENT5 Q3  SPRING 2024\n");
     printf("*********************************************************************\n");

    for (i = 0; i < N; i++)
        if ((pid[i] = Fork()) == 0) 
        {
	    
	    printf("CHILD[%d] IS GOING TO SLEEP FOR 50 SECS \n", getpid());
	    printf("CHILD[%d] : Time before exit in CLK cycles = %ld\n", getpid(), (long int)clock());
	    sleep(50);
            exit(100+i); /* Child */
        }

    for (i = 0; i < N; i++) 
     { 
        /* Parent */
	printf("PARENT REAPING CHILD NOT IN ANY SPECIFIC ORDER \n");
        pid_t wpid = wait(&child_status);
	if (WIFEXITED(child_status))
        {   
	printf("PARENT :  Time after wait for Termination of CHILD[%d] in CLK cycles = %ld\n", wpid, (long int)clock());
 clock();
            
            printf("Child %d terminated with exit status %d\n", wpid, WEXITSTATUS(child_status));
        }
        else
         printf("Child %d terminate abnormally\n", wpid);
       

      }
   printf("*************************************************************************\n");
}
