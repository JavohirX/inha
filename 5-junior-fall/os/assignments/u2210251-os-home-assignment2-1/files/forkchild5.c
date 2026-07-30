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
 printf("HELLO!!!");
if (Fork() == 0 )
 { printf(" OPERATING SYSTEMS ");
 if (Fork() != 0)
 { printf("HOME ASSIGNMENT 2 ");
 if (Fork() == 0)
 printf(" SUBMISSION ");
 printf(" DEADLINE "); }
 printf(" AFTER 2 WEEKS");
 if (Fork() != 0)
 { printf("SUNDAY 13TH OCTOBER 2024 --- ");
 if (Fork() == 0)
 printf(" GOOD LUCK ");} }
 printf("BYE \n"); }
