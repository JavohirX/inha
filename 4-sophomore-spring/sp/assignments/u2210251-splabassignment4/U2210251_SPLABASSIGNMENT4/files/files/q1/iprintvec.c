#include<stdio.h>

void iprint_vec(int *x, int n){
	for(int i = 0; i < n; i++){
		if(i == n - 1){
			printf("Array[%1d]=%2d\n", i, x[i]);
		}else{
			if( (i + 1) % 3 == 0 && i != 0){
				printf("Array[%1d]=%2d\n", i, x[i]);
			}else{
				printf("Array[%1d]=%2d   ", i, x[i]);
			}
		}
	}
}
