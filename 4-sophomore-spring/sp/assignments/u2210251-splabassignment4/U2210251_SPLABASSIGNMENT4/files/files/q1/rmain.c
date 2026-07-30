#include <stdio.h>
#include <stdlib.h>
#include "rLibVector.h"

int main(){
	double *x, *y, *z;
	int n, s, k;

	printf("Please, enter contsant k: ");
	scanf("%d", &k);
	
	printf("Please, enter contsant s for sorting (0 or 1): ");
	scanf("%d", &s);

	printf("Please, enter size of arrays: ");
	scanf("%d", &n);
	
	x = (double *)malloc(n * sizeof(double));
	y = (double *)malloc(n * sizeof(double));
	z = (double *)malloc(n * sizeof(double));

	
	printf("Please, enter elements of the first vector: \n"); 
	rfill_vec(x, n);
	
	printf("Please, enter elements of the second vector\n");
	rfill_vec(y, n);
	
	printf("The addition is equal to: \n");
	radd_vec(x, y, z, n);
	rprint_vec(z, n);
	
	printf("The subtraction is equal to: \n");
	rsub_vec(x, y, z, n);
	rprint_vec(z, n);
	
	printf("The multiplication is equal to:\n");
	rmul_vec(x, y, z, n);
	rprint_vec(z, n);
	
	printf("The multiplication of vector x on constant is equal to: \n"); 
	rmulk_vec(x, k, z, n);
	rprint_vec(z, n);
	
	printf("The division is equal to: \n");
	rdiv_vec(x, y, z, n);
	rprint_vec(z, n);
	
	printf("The division of vector x on constant is equal to: \n");
	rdivk_vec(x, k, z, n);
	rprint_vec(z, n);

	printf("The sorted vectors: \n");
	rsort_vec(x, s, z, n);
	rprint_vec(z, n);

	free(x);
	free(y);
	free(z);

	return 0;
}
