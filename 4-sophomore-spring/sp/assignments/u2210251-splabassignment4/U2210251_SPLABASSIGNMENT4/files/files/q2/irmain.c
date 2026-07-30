#include <stdio.h>
#include <stdlib.h>
#include "matrixLib.h"

int main() {
  int *a, *b, *c, n;

  printf("Please enter the size of your nxn matrices: \n");
  scanf("%d", &n);

  a = (int *) malloc(n * n * sizeof(int));
  b = (int *) malloc(n * n * sizeof(int));
  c = (int *) malloc(n * n * sizeof(int));

  printf("Please enter your first integer matrix: \n");
  imatfill(a, n);

  printf("Please enter your second integer matrix: \n");
  imatfill(b, n);

  printf("The addition of matrices is equal to: \n");
  imatadd(a, b, c, n);
  imatprint(c, n);

  printf("The subtraction of matrices is equal to: \n");
  imatsub(a, b, c, n);
  imatprint(c, n);

  printf("The multiplication of matrices is equal to: \n");
  imatmult(a, b, c, n);
  imatprint(c, n);

  printf("The transpose of matrix A is equal to: \n");
  imattrans(a, c, n);
  imatprint(c, n);

  printf("The transpose of matrix B is equal to: \n");
  imattrans(b, c, n);
  imatprint(c, n);

  free(a);
  free(b);
  free(c);
  
  double *x, *y, *z;

  x = (double *) malloc(n * n * sizeof(double));
  y = (double *) malloc(n * n * sizeof(double));
  z = (double *) malloc(n * n * sizeof(double));

  printf("Please enter your first real matrix: \n");
  rmatfill(x, n);

  printf("Please enter your second real matrix: \n");
  rmatfill(y, n);

  printf("The addition of matrices is equal to: \n");
  rmatadd(x, y, z, n);
  rmatprint(z, n);

  printf("The subtraction of matrices is equal to: \n");
  rmatsub(x, y, z, n);
  rmatprint(z, n);

  printf("The multiplication of matrices is equal to: \n");
  rmatmult(x, y, z, n);
  rmatprint(z, n);

  printf("The transpose of matrix A is equal to: \n");
  rmattrans(x, z, n);
  rmatprint(z, n);

  printf("The transpose of matrix B is equal to: \n");
  rmattrans(y, z, n);
  rmatprint(z, n);

  free(x);
  free(y);
  free(z);

  return 0;
}

