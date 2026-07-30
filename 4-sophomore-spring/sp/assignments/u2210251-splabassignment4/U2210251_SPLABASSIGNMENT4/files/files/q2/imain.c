#include <stdio.h>
#include <stdlib.h>
#include "matrixIntLib.h"

int main() {
  int *a, *b, *c, n;

  printf("Please enter the size of your nxn matrices: \n");
  scanf("%d", &n);

  a = (int *) malloc(n * n * sizeof(int));
  b = (int *) malloc(n * n * sizeof(int));
  c = (int *) malloc(n * n * sizeof(int));

  printf("Please enter your first matrix: \n");
  imatfill(a, n);

  printf("Please enter your second matrix: \n");
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

  return 0;
}

