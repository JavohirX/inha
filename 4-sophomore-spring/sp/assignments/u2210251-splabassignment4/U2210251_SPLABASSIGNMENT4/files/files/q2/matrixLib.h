#ifndef matrixLib_H
#define matrixLib_H

void imatadd(int *a, int *b, int *c, int n);
void imatsub(int *a, int *b, int *c, int n);
void imatmult(int *a, int *b, int *c, int n);
void imattrans(int *a, int *c, int n);
void imatfill(int *a, int n);
void imatprint(int *a, int n);

void rmatadd(double *a, double *b, double *c, int n);
void rmatsub(double *a, double *b, double *c, int n);
void rmatmult(double *a, double *b, double *c, int n);
void rmattrans(double *a, double *c, int n);
void rmatfill(double *a, int n);
void rmatprint(double *a, int n);

#endif
