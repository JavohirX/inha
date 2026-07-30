#ifndef VECTOR_H
#define VECTOR_H

void iadd_vec(int *x, int *y, int *z, int n); 
void isub_vec(int *x, int *y, int *z, int n);
void imul_vec(int *x, int *y, int *z, int n);  
void idiv_vec(int *x, int *y, int *z, int n); 
void imulk_vec(int *x, int k, int *z, int n); 
void idivk_vec(int *x, int k, int *z, int n);  
void irev_vec(int *x, int *y, int n);  
void isort_vec(int *x, int s, int *z, int n); 
void ifill_vec(int *x, int n); 
void iprint_vec(int *x, int n); 

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

