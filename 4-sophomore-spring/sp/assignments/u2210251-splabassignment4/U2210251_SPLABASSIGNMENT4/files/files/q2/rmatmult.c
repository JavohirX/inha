#include<stdio.h>

void rmatmult(double *a, double *b, double *c, int n){
  for (int i=0; i<n; i++) {
    for (int k=0; k<n; k++) {
      int r = *(a+i*n+k);
      for (int j=0; j<n; j++)
        *(c+i*n+j) += r * *(b+k*n+j);
    }
  }
}
