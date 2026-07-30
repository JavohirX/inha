/* When connecting to a remote host , it is necessary to have its IP address.
*/
/* Function gethostbyname is used for this purpose.
*/
/* It takes the domain name as the parameter and returns a structure of type hostent.
*/
/* This structure has the ip information.
*/
/* It is present in netdb.h. Lets have a look at this structure
*/
/* Description of data base entry for a single host.
*/
/*
struct hostent
*/
/*
{
*/
/*
char *h_name;
Official name of host.
*/
/*
char **h_aliases;
Alias list.
*/
/*
int h_addrtype;
Host address type.
*/
/*
int h_length;
Length of address.
*/
/*
char **h_addr_list;
List of addresses from name server.
*/
/*
};
*/
/*
The h_addr_list has the IP addresses.
*/
#include<stdio.h>
//printf
#include<string.h>
//strcpy
#include<sys/socket.h>
#include<netdb.h>
//hostent
#include<arpa/inet.h>
int main(int argc , char *argv[])
{
char *hostname;
char ip[100];
struct hostent *he;
struct in_addr **addr_list;
int i;
if(argc == 2 )
{
hostname = argv[1];
if ( (he = gethostbyname( hostname ) ) == NULL)
{
//gethostbyname failed
herror("gethostbyname");
return 1;
}
//Cast the h_addr_list to in_addr , since h_addr_list also has the ip address in long format only
addr_list = (struct in_addr **) he->h_addr_list;
for(i = 0; addr_list[i] != NULL; i++)
{
//Return the first one;
strcpy(ip , inet_ntoa(*addr_list[i]) );
printf("ip = %s \n", ip);
}
printf("%s resolved to : %s \n" , hostname , ip);
}
else
printf("Usage : ./gethostname domain_name \n");
return 0;
}
