#include<stdio.h>

void imatprint(int *a, int n){
  for(int i = 0; i < n; i++){
    for(int g = 0; g < n; g++) {
    	if(*(a + i * n + g) >= 10 && *(a + i * n + g) < 100){
    		printf("%d     ", *(a + i * n + g));
    	}else if(*(a + i * n + g) >= 100 && *(a + i * n + g) < 1000){
     		printf("%d    ", *(a + i * n + g));   	
    	}else if(*(a + i * n + g) >= 1000 && *(a + i * n + g) < 10000){
     		printf("%d   ", *(a + i * n + g));   	
    	}else if(*(a + i * n + g) >= 10000){
     		printf("%d  ", *(a + i * n + g));   	
    	}else if(*(a + i * n + g) <= -10 && *(a + i * n + g) > -100){
     		printf("%d    ", *(a + i * n + g));   	
    	}else if(*(a + i * n + g) <= -100 && *(a + i * n + g) > -1000){
     		printf("%d   ", *(a + i * n + g));   	
    	}else if(*(a + i * n + g) <= -1000 && *(a + i * n + g) > -10000){
     		printf("%d  ", *(a + i * n + g));   	
    	}else if(*(a + i * n + g) <= -10000){
     		printf("%d ", *(a + i * n + g));   	
    	}else if(*(a + i * n + g) < 0 && *(a + i * n + g) > -10){
     		printf("%d     ", *(a + i * n + g));   	
    	}else if(*(a + i * n + g) < 10 && *(a + i * n + g) >= 0){
     		printf("%d      ", *(a + i * n + g));   	
    	}
    }
    printf("\n");
  }
}


