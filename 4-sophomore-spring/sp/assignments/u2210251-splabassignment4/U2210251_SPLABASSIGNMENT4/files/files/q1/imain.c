#include <stdio.h>
#include <stdlib.h>
#include "iLibVector.h"

int main(){
	int *x, *y, *z, n, s, k;

	printf("Please, enter contsant k: ");
	scanf("%d", &k);
	
	printf("Please, enter contsant s for sorting (0 or 1): ");
	scanf("%d", &s);

	printf("Please, enter size of arrays: ");
	scanf("%d", &n);
	
	x = (int *)malloc(n * sizeof(int));
	y = (int *)malloc(n * sizeof(int));
	z = (int *)malloc(n * sizeof(int));
	
	printf("Please, enter elements of the first vector: \n"); 
	ifill_vec(x, n);
	
	printf("Please, enter elements of the second vector\n");
	ifill_vec(y, n);
	
	printf("The addition is equal to:\n");
	iadd_vec(x, y, z, n);
	iprint_vec(z, n);
	
	printf("The subtraction is equal to:\n");
	isub_vec(x, y, z, n);
	iprint_vec(z, n);
	
	printf("The multiplication is equal to:\n");
	imul_vec(x, y, z, n);
	iprint_vec(z, n);
	
	printf("The division is equal to:\n");
	idiv_vec(x, y, z, n);
	iprint_vec(z, n);
	
	printf("The division of vector x on constant is equal to:\n");
	idivk_vec(x, k, z, n);
	iprint_vec(z, n);

	printf("The multiplication of vector x on constant is equal to:\n"); 
	imulk_vec(x, k, z, n);
	iprint_vec(z, n);

	printf("The sorted vector:\n");
	isort_vec(x, s, z, n);
	iprint_vec(x, n);

	free(x);
	free(y);
	free(z);

	return 0;
}
