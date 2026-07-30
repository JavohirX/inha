#include<stdio.h>

void imatmult(int *a, int *b, int *c, int n){
  for (int i=0; i<n; i++) {
    for (int k=0; k<n; k++) {
      int r = *(a+i*n+k);
      for (int j=0; j<n; j++)
        *(c+i*n+j) += r * *(b+k*n+j);
    }
  }
}
