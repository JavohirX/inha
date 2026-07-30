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
   
   pid_t pid[100];  

   int i, n;
	 
	printf("PARENT - PROGRAM:zombie_childn.c LAB ASSIGNMENT5 Q2  SPRING 2024\n");
   	printf("****************************************************************\n");
    
	printf("Number of Child processes n=");
 	scanf("%d", &n);
	
    	printf("HELLO FROM PARENT, pid = %d\n", getpid());

    	for(i=0; i < n; i++)
    	{
      	  printf("PARENT : I AM NOW CREATING CHILD NO. %d \n",i);
     	  if (Fork() == 0) 
	   {
           /* Child */
            printf("HELLO FROM RUNNING CHILD, PID[%d] = %d\n", i, getpid());
            while (1)
            ;   /* Infinite loop */
           } 
     	}
     	sleep(5);
     	printf("PARENT : I AM NOW TERMINATING - ALL MY CHILDREN BECOME ORPHAN SOON \n");
     	printf("BYE FROM TERMINATING PARENT, PID = %d\n", getpid());
	printf("************************\n");
     	exit(0);
}
