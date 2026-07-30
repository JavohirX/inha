#include <stdio.h>
int main()
{
int i, n, key, count=0, list[100];
float avg;
// Read the value of n
printf("\n Ener the size of the list : ");
scanf("%d", &n);
// Read the list of ‘n’ numbers from the keyboard
printf("\n Enter %d Elements of the list : \n", n);
for(i=0; i<n; i++)
{
printf("\nlist[%d]=",i);
scanf("%d",&list[i]);
}
// To search for a key in the above list
printf("\nEnter the search key :");
scanf("%d", &key);
for(i=0; i<n; i++)
{
if(list[i]==key)
{printf("\nkey %d is found at location %d in the list\n",key,i);
count++;
}
}
if(count==0)
printf("\nKey %d not found in the list \n", key);
else
printf("\nKey %d occurs %d times in the list\n", key, count);
}
