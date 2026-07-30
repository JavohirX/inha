#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
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
	pid_t pid;

	int  x=1;

	
	 printf("PARENT - PROGRAM:fork2.c LAB ASSIGNMENT5 Q1  SPRING 2024\n");
         printf("********************************************************\n");

	 printf("start of  parent process  : x=%d, pid=%d \n", x, getpid());

	pid = Fork();

	if (pid == 0) 
        {
	  printf("CHILD PROCESS CREATED\n");
          printf("*************************\n");
	  printf("created process child : x=%d, pid=%d \n", ++x, getpid());
	  
	  printf("CHILD PROCESS TERMINATED\n");
          printf("*************************\n");
   	  exit(0);
        }
	
        printf("now in  parent : x=%d, pid=%d \n", --x, getpid());

	printf("PARENT PROCESS TERMINATED\n");
    	printf("*************************\n");
	exit(0);


}


