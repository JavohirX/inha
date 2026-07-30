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
   
    printf("PARENT - PROGRAM:fork3.c LAB ASSIGNMENT5 Q1  SPRING 2024\n");
    printf("********************************************************\n");

    printf("L0\n");
    printf("CHILD PROCESS CREATED\n");
    printf("*************************\n");
    Fork();

    printf("L1\n");
    printf("CHILD PROCESS CREATED\n");
    printf("*************************\n");
    Fork();

    printf("L2\n");
    printf("CHILD PROCESS CREATED\n");
    printf("*************************\n");
    Fork();

    printf("L3\n");
    printf("CHILD PROCESS CREATED\n");
    printf("*************************\n");
    Fork();

    printf("Bye\n");
    printf("ALL PROCESSES TERMINATED\n");
    printf("**********************\n");


}
