#include<stdio.h>

void rprint_vec(double *x, int n){
	for(int i = 0; i < n; i++){
		if(i == n - 1){
			printf("Array[%1d]=%2f\n", i, x[i]);
		}else{
			if( (i + 1) % 3 == 0 && i != 0){
				printf("Array[%1d]=%2f\n", i, x[i]);
			}else{
				printf("Array[%1d]=%2f   ", i, x[i]);
			}
		}
	}
}
