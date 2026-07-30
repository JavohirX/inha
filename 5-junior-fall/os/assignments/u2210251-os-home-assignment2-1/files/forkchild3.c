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
 return pid;}
int main()
{ printf("L0 : CHILD PID = %d, PARENT PID = %d\n", getpid(), getppid());
 if (Fork() == 0)
 { printf("L1 : CHILD PID = %d, PARENT PID = %d\n", getpid(), getppid());
 if (Fork() == 0)
 { printf("L2 : CHILD PID = %d, PARENT PID = %d\n", getpid(), getppid());
 if (Fork() == 0)
 { printf("L3 : CHILD PID = %d, PARENT PID = %d\n", getpid(), getppid());
 }
 printf("L4 : CHILD PID = %d, PARENT PID = %d\n", getpid(), getppid());
 }
 printf("L5 : CHILD PID = %d, PARENT PID = %d\n", getpid(), getppid());
 }
 printf("Bye\n");
}
