#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
void unix_error(char *msg) /* Unix-style error */
{ fprintf(stderr, "%s: %s\n", msg, strerror(errno));
 exit(0);}
pid_t Fork(void)
{ pid_t pid;
 if ((pid = fork()) < 0)
 unix_error("Fork error");
 return pid;}
int main()
{pid_t pid;
printf("hello F0 : CHILD PID = %d, PARENT PID = %d\n", getpid(), getppid());
if (Fork() == 0 )
 { printf("hello F1 : CHILD PID = %d, PARENT PID = %d\n", getpid(), getppid());
 if (Fork() != 0)
 { printf("hello F2 : CHILD PID = %d, PARENT PID = %d\n", getpid(), getppid());
 if (Fork() == 0)
 { printf("hello F3 : CHILD PID = %d, PARENT PID = %d\n", getpid(),
getppid()); }
 printf("hello F4 : CHILD PID = %d, PARENT PID = %d\n", getpid(), getppid()); }
 printf("hello F5 : CHILD PID = %d, PARENT PID = %d\n", getpid(), getppid());
 if (Fork() == 0)
 { printf("hello F6 : CHILD PID = %d, PARENT PID = %d\n", getpid(), getppid());
 if (Fork() != 0)
 { printf("hello F7 : CHILD PID = %d, PARENT PID = %d\n", getpid(), getppid());}
 printf("hello F8 : CHILD PID = %d, PARENT PID = %d\n", getpid(), getppid()); }
printf("hello F9 : CHILD PID = %d, PARENT PID = %d\n", getpid(), getppid());}
printf("BYE F10: CHILD PID = %d, PARENT PID = %d\n", getpid(), getppid());}
