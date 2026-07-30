#include<stdio.h>

void imatfill(int *a, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j+=5){
        if(n - j == 4){
            printf("Element[%d][%d] & [%d][%d] & [%d][%d] & [%d][%d] = ", i, j, i, j+1, i, j+2, i, j+3);
	    scanf("%d %d %d %d", (a+i*n+j), (a+i*n+(j+1)), (a+i*n+(j+2)), (a+i*n+(j+3)));
        }else if(n - j == 3){
            printf("Element[%d][%d] & [%d][%d] & [%d][%d] = ", i, j, i, j+1, i, j+2);
	    scanf("%d %d %d", (a+i*n+j), (a+i*n+(j+1)), (a+i*n+(j+2)));
        }else if(n - j == 2){
            printf("Element[%d][%d] & [%d][%d] = ", i, j, i, j+1);
	    scanf("%d %d", (a+i*n+j), (a+i*n+(j+1)));
        }else if(n - j == 1){
            printf("Element[%d][%d] = ", i, j);
	    scanf("%d", (a+i*n+j));
        }else{
	    printf("Element[%d][%d] & [%d][%d] & [%d][%d] & [%d][%d] & [%d][%d]= ", i, j, i, j+1, i, j+2, i, j+3, i, j+4);
	    scanf("%d %d %d %d %d", (a+i*n+j), (a+i*n+(j+1)), (a+i*n+(j+2)), (a+i*n+(j+3)), (a+i*n+(j+4)));
        }	
        }
    }
}
