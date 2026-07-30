#include<stdio.h>

void rmul_vec(double *x, double *y, double *z , int n ) { 
    for (int i=0; i<n ; i++ ) { 
        z[i] = x[i]*y[i];
    }
}

