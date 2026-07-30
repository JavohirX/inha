#include <stdio.h>
#include <time.h>
#include <float.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

clock_t clock(void);
void matTranspose(double **, int);
void mmult(double **, double **, double **, int);
void passCPUTime(clock_t, clock_t, char *, int);

int main(int arguments, char *inputArgs[]) {
	FILE *fA = NULL, *fB = NULL, *fC = NULL;
	int i, j, n, nxn;
	clock_t startTime, endTime;

	if (arguments == 5) {
		fA = fopen(inputArgs[1], "r");
		fB = fopen(inputArgs[2], "r");
		
		n = atoi(inputArgs[4]);
		nxn = n*n;

		double **A = malloc(n*sizeof(double*));
		double **B=malloc(n*sizeof(double*));
		double **C = malloc(n*sizeof(double*));
		double **BTranspose = malloc(n*sizeof(double*));

		for( i = 0; i < n; i++ ) {
			C[i] = malloc(n*sizeof(double));
			B[i] = malloc(n*sizeof(double));
			A[i] = malloc(n*sizeof(double));
			BTranspose[i] = malloc(n*sizeof(double));
		}

		for( i = 0; i < n; i++ ) {
			for(j = 0; j<n; j++) {
				fscanf(fA, "%lf", &A[i][j]);
				fscanf(fB, "%lf", &B[i][j]);			
				C[i][j] = 0;			
				BTranspose[i][j] = 0;		
			}
		}

		fclose(fA);
		fclose(fB);

		fC = fopen(inputArgs[3], "w");
		for( i = 0; i < n; i++ ) {
			for(j = 0; j<n; j++) {
				fprintf(fC, "%lf\t", B[i][j]);			
			}
			fprintf(fC, "\n");
		}
		fclose(fC);
		
		for( i = 0; i < n; i++ ) {
			for(j = 0; j<n; j++) 
				BTranspose[i][j] = B[j][i];
		}

		startTime = clock();
		mmult(&A[0], &BTranspose[0], &C[0], n);
		endTime = clock();

		passCPUTime(startTime, endTime, "TransposedMatrix", n);
		
		fC = fopen(inputArgs[3], "w");
		for( i = 0; i < n; i++ ) {
			for(j = 0; j<n; j++) {
				fprintf(fC, "%lf\t", C[i][j]);			
			}
			fprintf(fC, "\n");
		}
		fclose(fC);	
	

		for(int d = 0; d < n; d++ ) 
			free(C[i]);
		free(C);

	}else {
		printf("Incorrect format: \n");
		printf("$./task6 [A_MATRIX_Name] [B_MATRIX_Name] [C_MATRIX_Name] [SIZE_N]\n");
	}
}

void passCPUTime(clock_t startTime, clock_t endTime, char *method, int n) {
  FILE *fileTiming = fopen("CPU_time", "a");
  double total_t = (double) ((double)endTime - (double)startTime)/(double) CLOCKS_PER_SEC;
	printf(" %lf s. time taken by %s method\n", total_t, method);
	fprintf(fileTiming," %lf time taken by %s method to compute %dx%d\n", total_t, method, n, n);
	fclose(fileTiming);
}

void matTranspose(double **B, int n) {
	int i, j;
	double **tmp = B;
	for(i = 0; i< n; i++)
		for(j = 0; j< n; j++)
			B[j][i] = tmp[i][j];
}

void mmult(double **A, double **B, double **C, int n) {
double sum;
    for (int i = 0; i < n; ++i){    
	    for (int j = 0; j < n; ++j)    {
	      sum = 0.0;
    	  for (int k = 0; k < n; ++k) {
	        sum += A[i][k] * B[j][k];
    		}
		    C[i][j] = sum;
    	}
  	}
}

