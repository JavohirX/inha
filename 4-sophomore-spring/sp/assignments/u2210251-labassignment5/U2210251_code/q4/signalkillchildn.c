
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <string.h>

#define N 30

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
    int i;
    int child_status;

    printf("MAIN - PROGRAM:signalkillchildn.c LAB ASSIGNMENT5 Q4  SPRING 2024\n");
    printf("***********************************************************\n");
    for (i = 0; i < N; i++)
        if ((pid[i] = Fork()) == 0) 
        {
            printf("Child %d created  with pid = %d\n", i, getpid());
            /* Child: Infinite Loop */
            while(1)
                ;
        }
    
    for (i = 0; i < N; i++) 
    {
        printf("Killing Child process %d with pid =  %d\n", i, pid[i]);
        sleep(1);
        kill(pid[i], SIGINT);
    }

    for (i = 0; i < N; i++) 
    {
        pid_t wpid = wait(&child_status);
        if (WIFEXITED(child_status))
            printf("Child %d terminated with exit status %d\n", wpid, WEXITSTATUS(child_status));
        else
            printf("Child %d terminated abnormally\n", wpid);
    }
	printf("***********************************************************\n");

}
