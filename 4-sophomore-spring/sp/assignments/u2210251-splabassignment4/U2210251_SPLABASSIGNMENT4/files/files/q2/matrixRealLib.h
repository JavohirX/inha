#ifndef matrixRealLib_H
#define matrixRealLib_H

void rmatadd(double *a, double *b, double *c, int n);
void rmatsub(double *a, double *b, double *c, int n);
void rmatmult(double *a, double *b, double *c, int n);
void rmattrans(double *a, double *c, int n);
void rmatfill(double *a, int n);
void rmatprint(double *a, int n);

#endif
