#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
void unix_error(char *msg) /* Unix-style error */
{ fprintf(stderr, "%s: %s\n", msg, strerror(errno));
 exit(0);
}
pid_t Fork(void)
{ pid_t pid;
 if ((pid = fork()) < 0)
 unix_error("Fork error");
 return pid;
}
int main()
{
 printf("L0\n");
 Fork();
 printf("L1 : CHILD PID = %d, PARENT PID = %d\n", getpid(), getppid());
 Fork();
 printf("L2 : CHILD PID = %d, PARENT PID = %d\n", getpid(), getppid());
 Fork();
 printf("L3 : CHILD PID = %d, PARENT PID = %d\n", getpid(), getppid());
 Fork();
 printf("Bye : CHILD PID = %d, PARENT PID = %d\n", getpid(), getppid());
}
