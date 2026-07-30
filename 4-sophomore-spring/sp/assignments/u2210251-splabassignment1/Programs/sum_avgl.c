#include <stdio.h>
int main()
{
int i, n, sum, list[100];
float avg;
// Read the value of n
printf("\n Ener the size of the list : ");
scanf("%d", &n);
// Read the list of ‘n’ numbers from the keyboard
printf("\n Enter %d Elements of the list : \n", n);
for(i=0; i<n; i++)
{
printf("\n list[%d]=",i);
scanf("%d",&list[i]);
}
//Compute the sum of the list
sum=0;
for(i=0; i<n; i++)
sum += list[i];
//Compute the average of the list
avg=(float)sum/n;
printf("\nsum of %d elements in the list= %d and average = %f\n",n,sum,avg);
}
