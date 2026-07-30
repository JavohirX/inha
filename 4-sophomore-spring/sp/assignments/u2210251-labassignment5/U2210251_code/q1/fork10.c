#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
	pid_t pid;

	printf("PARENT - PROGRAM:fork10.c LAB ASSIGNMENT5 Q1  SPRING 2024\n");
   	printf("********************************************************\n");

        printf("HELLO!!!");
	if (Fork() == 0 )
             {
      	      printf(" SYSTEMS ");
	      if (Fork() != 0) 
                     {
	             printf("PROGRAMMING ");
	             if (Fork() == 0) 
                                 printf(" LAB ASSIGNMENT 5 ");
	              printf(" SUBMISSION  ");
                      }
	      printf(" DEADLINE ");
                  if (Fork() != 0) 
                     {
	               printf("1ST APRIL 2017 ---  ");
                           if (Fork() == 0) 
                                printf(" GOOD LUCK ");
      	        }
	}
        printf("BYE \n");
		
	printf("ALL PROCESSES TERMINATED\n");
     	printf("************************\n");
	
}

