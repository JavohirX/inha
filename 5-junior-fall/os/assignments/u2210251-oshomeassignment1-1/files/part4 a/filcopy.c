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
    
    printf("COPYING A FILE \n");
    printf("ENTER NAME OF CURRENT FILE TO BE COPIED FROM :");
    scanf("%s", fname);
    printf("ENTER NAME OF NEW FILE NAME TO BE COPIED TO ");
    scanf("%s", cname);
    
    fd = open(fname, O_RDONLY, DEF_MODE);
    if (fd < 0)
        printf("cannot open FILE %s - does not exist \n", fname);
    else
    {
        if((nbytes=read(fd, buf, sizeof(buf))) < 0)
            printf("FILE READ ERROR\n");
        else
        {
            fd1 = open(cname, O_CREAT|O_TRUNC|O_WRONLY, DEF_MODE);
            if (fd1 < 0)
                printf("Cannot create New file %s\n", cname);
            else
            {
                len=strlen(buf);
                if((nbytes=write(fd1, buf, len)) < 0)
                    printf("FILE WRITE ERROR\n");
                else
                    printf("FILE %s has been copied to %s successfully OK ......\n", fname, cname);
                close(fd1);
            }
            close(fd);
        }
    }
}
