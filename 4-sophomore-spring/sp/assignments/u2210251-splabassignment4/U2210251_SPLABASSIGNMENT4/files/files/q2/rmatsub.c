#include<stdio.h>

void rmatsub(double *a, double *b, double *c, int n){
  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
      *(c+i*n+j) = *(a+i*n+j) - *(b+i*n+j);
    }
  }
}
