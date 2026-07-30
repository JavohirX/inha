#include <stdio.h>
#include <stdlib.h>
#include "matrixRealLib.h"

int main() {
  int n;
  double *a, *b, *c;
  
  printf("Please enter the size of your nxn matrices: \n");
  scanf("%d", &n);

  a = (double *) malloc(n * n * sizeof(double));
  b = (double *) malloc(n * n * sizeof(double));
  c = (double *) malloc(n * n * sizeof(double));

  printf("Please enter your first matrix: \n");
  rmatfill(a, n);

  printf("Please enter your second matrix: \n");
  rmatfill(b, n);

  printf("The addition of matrices is equal to: \n");
  rmatadd(a, b, c, n);
  rmatprint(c, n);

  printf("The subtraction of matrices is equal to: \n");
  rmatsub(a, b, c, n);
  rmatprint(c, n);

  printf("The multiplication of matrices is equal to: \n");
  rmatmult(a, b, c, n);
  rmatprint(c, n);

  printf("The transpose of matrix A is equal to: \n");
  rmattrans(a, c, n);
  rmatprint(c, n);

  printf("The transpose of matrix B is equal to: \n");
  rmattrans(b, c, n);
  rmatprint(c, n);

  free(a);
  free(b);
  free(c);

  return 0;
}

