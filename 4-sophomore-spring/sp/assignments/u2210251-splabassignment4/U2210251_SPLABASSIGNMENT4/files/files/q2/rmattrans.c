#include<stdio.h>

void rmattrans(double *a, double *c, int n){
  for(int i = 0; i < n; i++){
    for(int j = i; j < n; j++){
      if(i == j){
        *(c+i*n+j) = *(a+i*n+j);
        continue;
      }
      
      *(c+j*n+i) = *(a+i*n+j);
      *(c+i*n+j) = *(a+j*n+i);
    }
  }
}
