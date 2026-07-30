#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
void unix_error(char *msg)
{
 fprintf(stderr, "%s : %s\n", msg, strerror(errno));
 exit(0);
}
pid_t Fork(void)
{
 pid_t pid;
 if(( pid = fork()) < 0)
unix_error("Fork error");
return pid;
}
int main()
{
pid_t pid;
int val=1;
printf("start of parent process : val=%d, pid=%d \n", val, getpid());
if ((pid = Fork()) == 0)
 {
 printf("created process child : val=%d, pid=%d \n", ++val, getpid());
 exit(0);
}
 printf("now in parent : val=%d, pid=%d \n", --val, getpid());
exit(0);
}
