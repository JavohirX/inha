#include <stdio.h>
#include <string.h>
int main()
{
int i, j, k, l, len;
char ch, name[255], rname[255], uname[255], lname[255];
printf("\n Ener your name : ");
fgets(name, sizeof(name), stdin);
len = strlen(name);
printf("\n Length of your name : %d\n", --len);
name[len]='\0';
// Converting Lowercase characters to Uppercase
strcpy(uname, name);
for(i=0; i<len; i++)
{
if((uname[i] >= 'a') && (uname[i] <= 'z'))
uname[i]=uname[i] - 32;
}
printf("\nThe given name in UPPERCASE : %s \n", uname);
}
