#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define DEF_MODE S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IWGRP|S_IXGRP|S_IROTH

int main()
{
    int fd, fd1, len, i, fsize, nbytes;
    char ch=0, cf, buf[5120], fname[25], cname[25];
    
    printf("DELETING A FILE \n");
    printf("ENTER FILE NAME :");
    scanf("%s", fname);
    ch=getchar(); /* to remove the last newline character entered*/
    printf("PLEASE CONFIRM -SURE YOU WANT TO DELETE ....PRESS y/n :");
    scanf("%c", &cf);
    
    if (cf == 'y')
    {
        unlink(fname);
        printf("FILE %s deleted OK......\n", fname);
    }
    else
        printf("FILE %s not deleted OK......\n", fname);
}
