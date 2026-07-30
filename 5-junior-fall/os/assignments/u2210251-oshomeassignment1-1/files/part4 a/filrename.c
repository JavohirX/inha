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
    
    printf("RENAMING A FILE \n");
    printf("ENTER CURRENT FILE NAME:");
    scanf("%s", fname);
    printf("ENTER NEW FILE NAME :");
    scanf("%s", cname);
    
    printf("FILE %s has been renamed to %s OK......\n", fname, cname);
    rename(fname, cname);
}
