#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

void unix_error(char *);
pid_t Fork(void);


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
    int x = 1;
     
    printf("PARENT - PROGRAM:fork1.c LAB ASSIGNMENT5 Q1  SPRING 2024\n");
    printf("********************************************************\n");
    pid = Fork(); 
    if (pid == 0) 
    {  /* Child */
        
	printf("CHILD PROCESS CREATED\n");
        printf("*************************\n");
	printf("child : x=%d\n", ++x); 
	
        printf("CHILD PROCESS TERMINATED\n");
        printf("*************************\n");
	exit(0);
    }
    /* Parent */
    printf("parent: x=%d\n", --x); 

    printf("PARENT PROCESS TERMINATED\n");
    printf("*************************\n");
    exit(0);
}

