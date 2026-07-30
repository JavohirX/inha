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
{ 
pid_t pid;
 if ((pid = fork()) < 0)
 unix_error("Fork error");
 return pid;}
int main()
{ 
if (Fork() == 0)
 { /* Child */
 printf("RUNNING CHILD - CHILD PID = %d\n", getpid());
 printf("HELLO - I AM GOING TO SOON BECOME AN ORPHAN CHILD AS MY PARENT WILL GET TERMINATED SOON \n");
printf("OPEN ANOTHER TERMINAL AND SEE ME RUNNING WITHOUT THE PARENT BY EXECUTING THE COMMAND ps -la\n");
 printf("TO KILL ME USE THE COMMAND : kill -9 mypid \n");
 while (1)
 ; /* Infinite loop */
 }
 else
 { sleep(10);
 printf("PARENT NOW TERMINATING - PARENT PID = %d\n", getpid());
 exit(0); }}
