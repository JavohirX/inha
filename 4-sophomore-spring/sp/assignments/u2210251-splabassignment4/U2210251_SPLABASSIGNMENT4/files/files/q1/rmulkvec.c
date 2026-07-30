#include<stdio.h>

void rmulk_vec(double *p, int j, double *r, int m) { 
    for ( int i=0 ; i<m ; i++ ){ 
        r[i] = p[i]*j; 
    }
}
