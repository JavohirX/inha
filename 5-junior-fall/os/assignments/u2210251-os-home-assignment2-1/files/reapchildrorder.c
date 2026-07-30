#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
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
 int status, i,n;
 pid_t pid[100], retpid; 
 printf("Number of Child processes n=");
 scanf("%d", &n);
 printf("HELLO FROM PARENT, PARENT PID = %d\n", getpid());
 /* Parent creates N children */ 
for (i = 0; i < n; i++) 
 if ((pid[i]= Fork()) == 0) /* Child */ 
 { 
 printf("HELLO FROM CHILD , CHILD[%d] PID = %d\n", i, getpid());
 sleep(1*(i+1));
 exit(100+i); /*CHILD*/
 }
/* Parent reaps N children in particular order */ 
printf("PARENT REAPING CHILD IN REVERSE ORDER \n");
i = n-1; 
while ((retpid = waitpid(pid[i--], &status, 0)) > 0)
{ 
 if (WIFEXITED(status))
printf("CHILD %d terminated with exit status %d , Its PARENT PID = %d\n", retpid, WEXITSTATUS(status), getpid());
 else 
 printf("child %d terminated abnormally\n", retpid); 
} 
/* The only normal termination is if there are no more children */ 
if (errno != ECHILD) 
 unix_error("waitpid error"); 
exit(0); 
}
