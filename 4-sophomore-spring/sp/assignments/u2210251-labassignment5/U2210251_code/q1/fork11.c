#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

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

	printf("PARENT - PROGRAM:fork11.c LAB ASSIGNMENT5 Q1  SPRING 2024\n");
   	printf("********************************************************\n");

         printf("COVID 19 CORONA VIRUS ");

         if (Fork() == 0 )
             {   
                 printf("BE SAFE & HEALTHY");
	         if (Fork() != 0) 
                     printf("PANDEMIC DISEASE");
              }
         if (Fork() !=0) 
	 	printf("MAINTAIN DISTANCING");     
            
	  printf("STAY HOME \n");

	printf("ALL PROCESSES TERMINATED\n");
     	printf("************************\n");

}

