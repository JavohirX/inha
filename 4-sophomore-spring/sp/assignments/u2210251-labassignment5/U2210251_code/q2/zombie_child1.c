#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
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
   
	printf("PARENT - PROGRAM:zombie_child1.c LAB ASSIGNMENT5 Q2  SPRING 2024\n");
   	printf("****************************************************************\n");
        if (Fork() == 0) 
	{
           /* Child */
            printf("RUNNING CHILD -  CHILD PID = %d\n", getpid());
            printf("HELLO - I AM GOING TO SOON BECOME AN ORPHAN CHILD AS MY PARENT WILL GET TERMINATED SOON \n");
	    printf("Open another terminal and see me running without the Parent by executing the command ps -la\n");
            printf("To kill me use the command : kill -9 put my pid here in the command  \n");
            while (1)
            ;   /* Infinite loop */
        } 
        else 
        {
            
             sleep(30);
	     printf("PARENT NOW TERMINATING - PARENT PID = %d\n", getpid());
             exit(0);
        }

     	printf("************************\n");
}
