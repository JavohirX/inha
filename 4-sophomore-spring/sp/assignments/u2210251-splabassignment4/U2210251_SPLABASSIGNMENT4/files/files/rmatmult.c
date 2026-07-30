void rmatmult(double p[][100], double q[][100], double r[][100], int m) 
{
    int i, j, k;
    for (i = 0; i < m; i++) 
    {
        for (j = 0; j < m; j++) 
        {
            r[i][j] = 0;
            for (k = 0; k < m; k++) 
            {
                r[i][j] += p[i][k] * q[k][j];
            }
        }
    }
}
