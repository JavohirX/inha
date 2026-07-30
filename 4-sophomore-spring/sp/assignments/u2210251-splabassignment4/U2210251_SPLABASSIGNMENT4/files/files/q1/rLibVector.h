#ifndef VECTOR_H
#define VECTOR_H

void radd_vec(double *x, double *y, double *z, int n); 
void rsub_vec(double *x, double *y, double *z, int n); 
void rmul_vec(double *x, double *y, double *z, int n); 
void rdiv_vec(double *x, double *y, double *z, int n); 
void rmulk_vec(double *p, int j, double *r, int m); 
void rdivk_vec(double *p, int j, double *r, int m); 
void rrev_vec(double *p, double *r, int m); 
void rsort_vec(double *p, int s, double *r, int m); 
void rfill_vec(double *p, int m); 
void rprint_vec(double *p, int m); 

#endif

