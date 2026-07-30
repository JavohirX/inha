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
            
	printf("PARENT - PROGRAM:fork12.c LAB ASSIGNMENT5 Q1  SPRING 2024\n");
   	printf("********************************************************\n");

	printf("SYSTEMS PROGRAMMING FINAL EXAM ");
        if (Fork() == 0 )
           printf("IN 15TH WEEK .......STUDY HARD ....TRY TO GET BEST GRADE");
        if (Fork() != 0) 
                   printf("WISH YOU ALL THE BEST ...............GOOD LUCK");
	
	printf("BYE \n");
	
	printf("ALL PROCESSES TERMINATED\n");
     	printf("************************\n");
	

}
