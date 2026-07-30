#include<stdio.h>

void rdivk_vec(double *p, int j, double *r, int m) { 
    for ( int i=0 ; i<m ; i++ ){ 
        r[i] = p[i]/j; 
    }
}
