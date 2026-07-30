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
 int status, i,n, ttime;
 pid_t pid[100], retpid; 
 printf("Number of Child processes n=");
 scanf("%d", &n);
 printf("HELLO FROM PARENT, pid = %d\n", getpid());
 /* Parent creates N children */ 
for (i = 0; i < n; i++) 
 if ((pid[i]=Fork()) == 0) /* Child */ 
 { 
 ttime = 5 * (i+1);
 printf("HELLO FROM CHILD , My PID is %d, I am going to SLEEP for %d secs \n", getpid(),ttime);
 sleep(ttime);
 printf("CHILD %d : I JUST WOKE UP - I AM EXITING - BYE BYE \n", getpid());
 exit(100+i); /*CHILD*/
 }
/* Parent reaps N children in particular order */ 
printf("PARENT REAPING CHILD IN PARTICULAR ORDER \n");
i = 0; 
while ((retpid = waitpid(pid[i++], &status, 0)) > 0)
{ 
 if (WIFEXITED(status))
 {
 printf("PARENT %d : I AM NOW REAPING CHILD %d \n", getpid(), retpid);
 printf("CHILD %d terminated with exit status %d FROM PARENT pid = %d\n", retpid, WEXITSTATUS(status), getpid());
 }
 else 
printf("child %d terminated abnormally\n", retpid); 
} 
/* The only normal termination is if there are no more children */ 
if (errno != ECHILD) 
 unix_error("waitpid error"); 
exit(0); 
}

