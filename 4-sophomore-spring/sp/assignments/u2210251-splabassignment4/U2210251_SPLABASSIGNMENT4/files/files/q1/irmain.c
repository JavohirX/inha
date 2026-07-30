#include <stdio.h>
#include <stdlib.h>
#include "irLibVector.h"

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

	printf("Please, enter elements of the first integer vector: \n"); 
	ifill_vec(x, n);
	
	printf("Please, enter elements of the second integer vector\n");
	ifill_vec(y, n);
	
	printf("The addition is equal to:  ");
	iadd_vec(x, y, z, n);
	iprint_vec(z, n);
	
	printf("The subtraction is equal to:  ");
	isub_vec(x, y, z, n);
	iprint_vec(z, n);
	
	printf("The multiplication is equal to:  ");
	imul_vec(x, y, z, n);
	iprint_vec(z, n);
	
	printf("The division is equal to:  ");
	idiv_vec(x, y, z, n);
	iprint_vec(z, n);
	
	printf("The division of vector x on constant is equal to:  ");
	idivk_vec(x, k, z, n);
	iprint_vec(z, n);

	printf("The multiplication of vector x on constant is equal to:  "); 
	imulk_vec(x, k, z, n);
	iprint_vec(z, n);

	printf("The sorted vectors:  ");
	isort_vec(x, s, z, n);
	iprint_vec(x, n);
	
	free(x);
	free(y);
	free(z);
	
	double *a, *b, *c;
	
	a = (double *)malloc(n * sizeof(double));
	b = (double *)malloc(n * sizeof(double));
	c = (double *)malloc(n * sizeof(double));
	
	printf("Please, enter elements of the first real vector: \n"); 
	rfill_vec(a, n);
	
	printf("Please, enter elements of the second real vector\n");
	rfill_vec(b, n);
	
	printf("The addition is equal to:  ");
	radd_vec(a, b, c, n);
	rprint_vec(c, n);
	
	printf("The subtraction is equal to:  ");
	rsub_vec(a, b, c, n);
	rprint_vec(c, n);
	
	printf("The multiplication is equal to:  ");
	rmul_vec(a, b, c, n);
	rprint_vec(c, n);
	
	printf("The division is equal to:  ");
	rdiv_vec(a, b, c, n);
	rprint_vec(c, n);
	
	printf("The division of vector x on constant is equal to:  ");
	rdivk_vec(a, k, c, n);
	rprint_vec(c, n);

	printf("The multiplication of vector x on constant is equal to:  "); 
	rmulk_vec(a, k, c, n);
	rprint_vec(c, n);

	printf("The sorted vectors:  ");
	rsort_vec(a, s, c, n);
	rprint_vec(c, n);
	
	free(a);
	free(b);
	free(c);
	
	return 0;
}
