#include<stdio.h>

void rfill_vec(double *x, int n) { 
    for (int i = 0; i < n; i++) { 
	printf("Array[%d]=", i);
	scanf("%le", &x[i]);
    }
}
