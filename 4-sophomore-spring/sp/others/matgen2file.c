/****************************************************************************/
/* C PROGRAM TO GENERATE MATRIX OF NXN SIZE - PROGRAM NAME : matgen2file.c  */
/* THIS PROGRAM GENRATES MATRIX ELEMENTS OF TYPE FLOAT OF SIZE N X N        */
/* USING THE RANDOM GENERATOR FUNCTION rand() TO GENERATE REAL RANDOM       */
/*         NUMBERS BETWEEN 0 AND 100 USING THE  FOLLOWING EXPRESSION        */            
/*            ((float) rand() / (float) (RAND_MAX))*100.0;                  */
/*                                                                          */
/*           COMPILE THE PROGRAM USING THE FOLLOWING COMMAND                */
/*                                                                          */
/*                $ gcc -o matgen2file  matgen2file.c                       */
/*                                                                          */
/*   EXECUTE THE PROGRAM USING THE FOLLOWING COMMAND  WHICH REQUIRES        */
/*   THREE COMMAND LINE ARGUMENTS AS FOLLOWS :                              */
/*                                                                          */
/*              $ ./matgen2file matrixfilename N                            */
/*                                                                          */
/* FOR EXAMPLE: TO CREATE MATRIX A(FILE NAME: mata100x100) OF SIZE 100X100  */ 
/*      USE THE FOLLOWING COMMAND                                           */ 
/*                                                                          */
/*             $ ./matgen2file mata100x100 100                              */
/*                                                                          */
/*      THIS COMMAND NOT ONLY GENERATES  MATRIX A AND STORES IN FILE        */ 
/*        mata100x100   BUT ALSO OUTPUTS CPU TIME (IN SECS) TAKEN TO        */
/*      GENERATE THE FILE                                                   */   
/*                                                                          */
/****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <float.h>
#include <math.h>
#include <time.h>

clock_t clock(void);



int main(int argc, char *argv[]) 
{

   FILE *fp1;
   int i, n, nxn;
   float lr = 100.0, mel; 
    double total_t;
    clock_t start_t, end_t;
   

   start_t = clock();
   if (argc == 3)
   {
      printf("START TIME - TIME BEFORE THE START OF FILE CREATION = %lf clock cycles\n", (double)start_t);
   
      fp1 = fopen(argv[1], "w");
      n = atoi(argv[2]);
      nxn = n*n;
   
       /* Intializes random number generator */
       srand((unsigned int) time(NULL));

       /* Print nXn  random numbers  */
      printf(" START OF FILE %s CREATION :\n", argv[1]);
      printf("-------------------------------\n");

      for( i = 0; i < nxn; i++ ) 
        {
          mel= ((float) rand() / (float) (RAND_MAX))*lr;
          fprintf(fp1, "%f ",mel);
        }
     
      fclose(fp1);

      end_t = clock();
      printf(" END OF FILE %s CREATION :\n", argv[1]);
      printf("END TIME - TIME AFTER THE END OF FILE CREATION  = %lf clock cycles \n", (double)end_t);
      printf("CLOCKS_PER_SEC = %ld\n", CLOCKS_PER_SEC);
      total_t = (double)((double)end_t - (double)start_t) / (double)CLOCKS_PER_SEC;
      printf("TOTAL TIME TAKEN BY CPU FOR %s FILE CREATION: %lf secs\n", argv[1], total_t);
      printf("--------------------------------------------------\n");
      printf(" ELEMENTS OF %d x %d MATRIX %s  :\n", n, n, argv[1]);
      printf("--------------------------------------------------\n");
      fp1 = fopen(argv[1], "r");

      while( !feof(fp1))
     {
        fscanf(fp1, "%f ",&mel);
        printf("%f ", mel);
     }
      printf("\n\n");
      printf("--------------------------------------------------\n");
      fclose(fp1);
  }
   else
    {
     printf("wrong arguments - use the format \n $matgen2file filename  N\n");
    }
}
