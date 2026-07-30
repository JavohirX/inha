#include<stdio.h>

void isort_vec(int *x, int s, int *z , int n ) { 
    for(int i = 0; i<n; i++) { 
        z[i] = x[i];
    }
    switch (s)
    {
    case 1:
        for ( int i=0; i<n; i++ ){ 
            for (int j=0; j<(n-1)-i ; j++){
                if(z[j]>z[j+1]){
                    int temp = z[j]; 
                    z[j] = z[j+1] ; 
                    z[j+1] = temp ; 
                }
            }
        }
        break;
    
    case 0:
        for ( int i=0; i<n; i++ ){ 
            for (int j=0; j<(n-1)-i ; j++){
                if(z[j]<z[j+1]){
                    int temp = z[j]; 
                    z[j] = z[j+1] ; 
                    z[j+1] = temp ; 
                    //free(temp);
                }
            }
        }
        break ; 
    
    default:
        break;
    }
}
