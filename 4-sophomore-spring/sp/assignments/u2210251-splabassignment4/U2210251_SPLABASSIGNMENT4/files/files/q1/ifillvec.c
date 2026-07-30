#include<stdio.h>

void ifill_vec(int *x, int n) { 
    for (int i = 0; i < n; i++) { 
	printf("Array[%d]=", i);
	scanf("%d", &x[i]);
    }
}
