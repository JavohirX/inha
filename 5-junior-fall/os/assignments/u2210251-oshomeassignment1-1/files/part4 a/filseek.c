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
    int fd, i, fsize, nbytes, count;
    long int offset;
    char ch=0, buf[5120], fname[25];
    
    printf("OPENING AN EXISTING FILE\n");
    printf("ENTER FILE NAME : ");
    scanf("%s", fname);
    
    fd = open(fname, O_RDWR|O_APPEND, DEF_MODE);
    if (fd < 0)
        printf("cannot open FILE %s - does not exist \n", fname);
    else
    {
        printf("ENTER THE OFFSET BYTES TO BE SKIPPED FROM BEGINNING OF FILE\n");
        scanf("%ld", &offset);
        lseek(fd, offset, 0);
        printf("ENTER NUMBER OF CHARACTERS TO BE READ FROM OFFSET %ld POSITION\n", offset);
        scanf("%d", &count);
        
        printf(" READING FROM YOUR FILE %d bytes AT OFFSET %ld \n", count, offset);
        nbytes=read(fd, buf, count);
        buf[nbytes-1]='\0';
        printf("CONTENTS OF YOUR FILE %s - size= %d\n", fname, nbytes);
        puts(buf);
        close(fd);
    }
}
