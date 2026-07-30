#include <stdio.h>
#include <time.h>
#include <float.h>
#include <math.h>
#include <stdlib.h> 
#include <string.h>

clock_t clock(void);
void mmatkji (double **, double **, double **, int); 
void mmatijk (double **, double **, double **, int);
void mmatjik (double **, double **, double **, int); 
void mmatkij (double **, double **, double **, int); 
void mmatikj (double **, double **, double **, int); 
void mmatjki(double **, double **, double **, int); 

void resultSaving(double **, char*, char*, int); 
void timeTaken(clock_t, clock_t, char *, int); 

int main(int arguments, char *inputArgs[]) {
	char *saveFileName;
	clock_t startTime, endTime;
	int i; 
	int j; 
	int n;
	int nxn;

	FILE *fA = NULL; 
	FILE *fB = NULL;

	if (arguments == 5) {
		saveFileName = inputArgs[3];
		fA = fopen(inputArgs[1], "r"), fB = fopen(inputArgs[2], "r");
		n = atoi(inputArgs[4]);
		nxn = n*n;

		double **A = malloc(n*sizeof(double*));
		double **B= malloc(n*sizeof(double*)); 
		double **C = malloc(n* sizeof(double*));
		for (i = 0; i < n; i++ ) {
			C[i] = malloc(n* sizeof(double));
			B[i] = malloc(n* sizeof(double)); 
			A[i] = malloc(n* sizeof(double));
		}
		for(i = 0; i < n; i++ ) {
			for(j = 0; j<n; j++) {
				C[i][j] = 0;
				fscanf(fA, "%lf", &A[i][j]); 
				fscanf(fB, "%lf", &B[i][j]); 
			}
		}

		fclose(fB);	
		fclose(fA);	

		char *CPUaddToNaming[3], *saveAddToNaming[4];
		for(int func = 0; func < 6; func ++){
			for(i = 0; i < n; i++ ) {
				for(j = 0; j<n; j++) {
					C[i][j] = 0;
				}
			}
			startTime = clock();

			switch (func) {
				case 0:
					mmatijk (&A[0],&B[0],&C[0], n);
					*CPUaddToNaming = "IJK";
					*saveAddToNaming = "_ijk";
				break;
				case 1:
					mmatjik (&A[0],&B[0],&C[0], n);
					*CPUaddToNaming = "JIK";
					*saveAddToNaming = "_jik";
				break;
				case 2:
					mmatjki (&A[0],&B[0],&C[0], n);
					*CPUaddToNaming = "JKI";
					*saveAddToNaming = "_jki";
				break;
				case 3:
					mmatkji (&A[0],&B[0],&C[0], n);
					*CPUaddToNaming = "KJI";
					*saveAddToNaming = "_kji";
				break;
				case 4:
					mmatkij (&A[0],&B[0],&C[0], n);
					*CPUaddToNaming = "KIJ";
					*saveAddToNaming = "_kij";
				break;
				case 5:
					mmatikj(&A[0],&B[0],&C[0], n);
					*CPUaddToNaming = "IKJ";
					*saveAddToNaming = "_ikj";
				break;
			}

			endTime = clock();
			timeTaken(startTime, endTime, *CPUaddToNaming, n);
			resultSaving(&C[0], saveFileName, *saveAddToNaming, n);
		}

		for(int d = 0; d < n; d++)
			free(C[d]);
		free(C);
		
	}
	else {
		printf("Incorrect format: \n");
		printf("$./task5 [A_MATRIX_Name] [B_MATRIX_Name] [C_MATRIX_Name] [SIZE_N]\n");
	}
}

void resultSaving(double **C, char *fileName, char *type, int n) {
	int i,j;

	strcat(fileName, type);
	FILE *fC = fopen(fileName, "w"); 

	for(i = 0; i < n; i++) {
		for(j = 0; j < n; j++) {
			fprintf(fC, "%lf\t", C[i][j]);
		}
		fprintf(fC, "\n");
	}

	fclose(fC);
	fileName[strlen(fileName)-4] = '\0';
}

void timeTaken(clock_t startTime, clock_t endTime, char *method, int n) { 
	FILE *fileTiming = fopen("TIME_TAKEN_CPU", "a"); 
	double total_t = (double) ((double) endTime -(double)startTime)/(double) CLOCKS_PER_SEC;
	printf("%lf time is taken by %s method\n", total_t, method);
	fprintf(fileTiming," %lf time is taken by %s method to display %dx%d\n", total_t, method, n, n); 
	fclose(fileTiming);
}

void mmatijk (double **A, double **B, double **C, int n) {
	int i, j, k;
	double sum;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			sum = 0.0;
			for (k = 0; k < n; k++) {
				sum += A[i][k]*B[k][j]; 
			}
			C[i][j] = sum;
		}
	}
}

void mmatjik (double **A, double **B, double **C, int n) {
	int i, j, k;
	double sum;

	for (j = 0; j < n; j++) {
		for (i = 0; i < n; i++) {
			sum = 0.0;
			for (k = 0; k < n; k++) {
				sum += A[j][k]*B[k][i]; 
			}
			C[j][i] = sum;
		}
	}
}

void mmatjki (double **A, double **B, double **C, int n) {
	int i, j, k;
	double sum;

	for (j = 0; j < n; j++) {
		for (k = 0; k < n; k++) {
			sum = 0.0;
			for (i = 0; i < n; i++) {
				sum += A[j][i]*B[i][k];
			}
			C[j][k] = sum;
		}
	}
}

void mmatkji (double **A, double **B, double **C, int n) {
	int i, j, k;
	double r;

	for (k = 0; k < n; k++) {
		for (j = 0; j < n; j++) {
			r = B[k][j];
			for (i = 0; i < n; i++) {
				C[i][j] += A[i][k]*r;
			}
		}
	}
}

void mmatkij (double **A, double **B, double **C, int n) {
	int i, j, k;
	double r;

	for (k = 0; k < n; k++) {
		for (i = 0; i < n; i++) {
			r = A[i][k];
			for (j = 0; j < n; j++) {
				C[i][j] += r * B[k][j];
			}
		}
	}
}

void mmatikj (double **A, double **B, double **C, int n) {
	int i, j, k;
	double r;
	for (i = 0; i < n; i++) {
		for (k = 0; k < n; k++) {
			r = A[i][k];
			for (j = 0; j < n; j++) {
				C[i][j] += r * B[k][j];
			}
		}
	}
}




