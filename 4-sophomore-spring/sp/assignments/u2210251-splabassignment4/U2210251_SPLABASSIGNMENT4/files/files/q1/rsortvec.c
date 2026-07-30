#include<stdio.h>

void rsort_vec(double *p, int s, double *r, int m) { 
    for (int i = 0; i < m; i++) { 
        r[i] = p[i];
    }
    
    switch (s) {
        case 1:
            for (int i = 0; i < m; i++) { 
                for (int j = 0; j < (m - 1) - i; j++) {
                    if (r[j] > r[j + 1]) {
                        double temp = r[j]; 
                        r[j] = r[j + 1]; 
                        r[j + 1] = temp; 
                    }
                }
            }
            break;
        
        case 0:
            for (int i = 0; i < m; i++) { 
                for (int j = 0; j < (m - 1) - i; j++) {
                    if (r[j] < r[j + 1]) {
                        double temp = r[j]; 
                        r[j] = r[j + 1]; 
                        r[j + 1] = temp; 
                    }
                }
            }
            break; 
    
        default:
            break;
    }
}
