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
    int fd, i, fsize, nbytes;
    char ch=0, buf[5120], fname[25];
    
    printf("CREATING A NEW FILE WITH ALL ACCESS RIGHTS TO USER AND GROUP AND NO EXECUTE ACCESS TO OTHERS\n");
    printf("ENTER FILE NAME : ");
    scanf("%s", fname);
    
    fd = open(fname, O_CREAT|O_TRUNC|O_WRONLY|O_APPEND, DEF_MODE);
    if (fd < 0)
        printf("cannot create FILE %s \n", fname);
    else
    {
        printf("NOW ENTER YOUR PROGRAM OR TEXT LINE BY LINE- ONCE YOU FINISH PRESS KEYS Ctrl D together\n");
        i=0;
        ch=getchar(); /* to remove the last newline character entered*/
        while((ch=getchar()) != EOF)
            buf[i++]=ch;
        fsize=i;
        buf[fsize]='\0';
        printf("Total characters stored in your file = %d\n", fsize);
        write(fd, buf, fsize);
        close(fd);
    }
}
