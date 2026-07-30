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

#endif

